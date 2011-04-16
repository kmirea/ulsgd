#include "NetworkManager.h"
#include "GameManager.h"
#include <enet/enet.h>
#include <list>

#define MAX_NETWORK_DOWN 1048576/8
#define MAX_NETWORK_UP 262144/8
#define NETWORK_PORT 25000

NetworkManager::NetworkManager( GameManager* game, E_MANAGER_MODE mode ) : ReferenceCountedObject(),
		Game(game), Mode(mode), isConnected(false)
{
	if( enet_initialize() != 0 )
	{
		cerr << "Error initializing networking service, exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	server_name = new ENetAddress();

	server_name->port = NETWORK_PORT;

	switch( Mode )
	{
	case EMM_CLIENT:
		server_name->host = NULL;
		netinterface = enet_host_create( NULL, 1, MAX_NETWORK_DOWN, MAX_NETWORK_UP );
		FirstConnect = false;
		break;
	case EMM_SERVER:
		server_name->host = ENET_HOST_ANY;
		netinterface = enet_host_create( server_name, 10, 0, 0 );
		isConnected = true;
		break;
	default:
		cerr << "Invalid network service state, exiting..." << endl;
	}
}

NetworkManager::~NetworkManager()
{
	ENetEvent event;

	for( u32 i=0; i<PeerList.size(); i++ )
	{
		enet_peer_disconnect( PeerList[i], 0 );
		bool disconnect = false;
		while( enet_host_service( netinterface, &event, 3000) > 0 )
		{
			switch( event.type )
			{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "Disconnection suceeded." << endl;
				disconnect = true;
				break;
			}

			if( disconnect )
			{
				disconnect = false;
				break;
			}

			enet_peer_reset( PeerList[i] );
		}

	}
	enet_host_destroy( netinterface );
	enet_deinitialize();
	delete server_name;
}

bool NetworkManager::run()
{
	return isConnected;
}

void NetworkManager::update()
{
	ENetEvent event;

	u32 curr_time = Game->getTimer()->getTime();
	u32 target_time = curr_time + 10;
	while( enet_host_service( netinterface, &event, target_time - curr_time ) > 0 )
	{
		switch( event.type )
		{
		case ENET_EVENT_TYPE_CONNECT:
			cout << "Added peer" << endl;
			PeerList.push_back( event.peer );
			if( Mode == EMM_SERVER )
			{
				{	// make the client's object and send it first before anything
					Game->createSceneObject( Game->getClientPOCS() );
					Game->getEntityList().back()->syncCreate();

					deque<u8> clientcreate = makeCreateMessage( Game->getEntityList().back()->getNetworkObject()->getOutStream() );
					u32 StreamSize = clientcreate.size();
					u8 Buffer[StreamSize];
					for( u32 i=0; i<StreamSize; i++ )
					{
						Buffer[i] = clientcreate.front();
						clientcreate.pop_front();
					}
					ENetPacket* packet = enet_packet_create( (void*)Buffer, StreamSize, ENET_PACKET_FLAG_RELIABLE );
					for( u32 i=0; i<PeerList.size(); i++ )
						enet_peer_send( PeerList[i], 0, packet );
					enet_host_flush( netinterface );
				}

				deque<u8> syncdata;
				deque<u8> tempdata;
				for( u32 i=0; i<Game->getEntityList().size()-1; i++ )
				{
					Game->getEntityList()[i]->syncCreate();
					tempdata = makeCreateMessage( Game->getEntityList()[i]->getNetworkObject()->getOutStream() );
					while( tempdata.size() > 0 )
					{
						syncdata.push_back( tempdata.front() );
						tempdata.pop_front();
					}
				}
				u8 Buffer [syncdata.size()];
				for( u32 i=0; i<syncdata.size(); i++ )
				{
					Buffer[i] = syncdata[i];
				}
				ENetPacket* packet = enet_packet_create( (void*)Buffer, syncdata.size(), ENET_PACKET_FLAG_RELIABLE );

				enet_peer_send( PeerList.back(), 0, packet );

				enet_host_flush( netinterface );
			}
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			for( u32 i=0; i<event.packet->dataLength; i++ )
			{
				IncomingData.push_back( event.packet->data[i] );
			}
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			cout << "Peer disconnected" << endl;
			for( vector<ENetPeer*>::iterator itr = PeerList.begin(); itr!=PeerList.end();
					itr++)
			{
				if( *itr == event.peer )
				{
					PeerList.erase( itr );
					break;
				}
			}
			break;
		case ENET_EVENT_TYPE_NONE:
			cout << "No Event\r";
			break;
		}
		curr_time = Game->getTimer()->getTime();
	}

	if( PeerList.size() == 0 && Mode == EMM_CLIENT )
		isConnected = false;
	
	NetData* data = NULL;
	while( (data = getMessage( IncomingData )) != NULL )
	{
		if( data->MsgType == ENMT_PING )
			continue;

		MessageList[data->net_id].push_back( data );

		if( data->MsgType == ENMT_CREATE )
		{
			if( Mode == EMM_CLIENT && FirstConnect )
			{
				Game->getTimer()->setTime( data->MsgTime );
				Game->createClientObject( data->net_id );
				FirstConnect = false;
				continue;
			}
			Game->createObject( data->net_id );
		}
	}

	for( map< NETID, list<NetData*> >::iterator itr = MessageList.begin(); itr != MessageList.end(); itr++ )
	{
		itr->second.sort();
	}
}

void NetworkManager::sendLocalData()
{
	deque<u8> OutgoingData;
	
	for( u32 i=0; i<Game->getEntityList().size(); i++ )
	{
		if( Game->getEntityList()[i]->getNetworkObject()->isMessageAvailable() )
		{
			NetData* OutData = Game->getEntityList()[i]->getNetworkObject()->getOutStream();
			deque<u8> streambuffer;
			if( OutData->MsgType == ENMT_SYNC )
				streambuffer = makeSyncMessage( OutData );
			else if( OutData->MsgType == ENMT_APPLY_FORCE )
				streambuffer = makeApplyMessage( OutData );
			while( streambuffer.size() > 0 )
			{
				OutgoingData.push_back( streambuffer.front() );
				streambuffer.pop_front();
			}
		}
	}

	if( Mode == EMM_CLIENT && Game->getClientObject()->getNetworkObject()->isMessageAvailable() )
	{
		NetData* OutData = Game->getClientObject()->getNetworkObject()->getOutStream();
		deque<u8> streambuffer = makeSyncMessage( OutData );
		while( streambuffer.size() > 0 )
		{
			OutgoingData.push_back( streambuffer.front() );
			streambuffer.pop_back();
		}
	}

	u32 StreamSize = OutgoingData.size();
	u8 Buffer[StreamSize];
	for( u32 i=0; i<StreamSize; i++ )
	{
		Buffer[i] = OutgoingData.front();
		OutgoingData.pop_front();
	}

	ENetPacket* packet = enet_packet_create( (void*)Buffer, StreamSize, ENET_PACKET_FLAG_RELIABLE );

	for( u32 i=0; i<PeerList.size(); i++ )
		enet_peer_send( PeerList[i], 0, packet );

	enet_host_flush( netinterface );
}

bool NetworkManager::setConnectionAddress( ENetAddress& Address )
{
	server_name->host = Address.host;

	PeerList.push_back( enet_host_connect( netinterface, server_name, 0 ) );

	if( PeerList.back() == NULL )
	{
		cerr << "No available peers left to connect with." << endl;
		return false;
	}

	ENetEvent event;

	if( enet_host_service( netinterface, &event, 5000 ) > 0 && event.type == ENET_EVENT_TYPE_CONNECT )
	{
		cerr << "Connection was succesful. Syncing with peer..." << endl;
		isConnected = true;
		FirstConnect = true;
	}
	else
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection was unsuccesful..." << endl;
	}

	enet_host_flush(netinterface);
	return isConnected;
}

NetData* NetworkManager::getUpdateData( NETID NetObject )
{
	NetData* UpdateData = NULL;

	if( MessageList[NetObject].size() > 0 )
	{
		UpdateData = MessageList[NetObject].front();
		MessageList[NetObject].pop();
	}

	return UpdateData;
}

NETID NetworkManager::getNextNETID()
{
	return next_id_counter++;
}

string NetworkManager::getDebugInfo() const
{
	return string("NetworkManager");
}
