#include "NetworkManager.h"
#include "GameManager.h"
#include <enet/enet.h>

NetworkManager::NetworkManager( GameManager* game, E_MANAGER_MODE mode ) : ReferenceCountedObject(),
		Game(game), Mode(mode), isConnected(false)
{
	if( enet_initialize() != 0 )
	{
		cerr << "Error initializing networking service, exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	server_name = new ENetAddress();

	server_name->port = 12345;

	switch( Mode )
	{
	case EMM_CLIENT:
		server_name->host = NULL;
		netinterface = enet_host_create( NULL, 1, 0, 0 );
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

	while( enet_host_service( netinterface, &event, 500 ) > 0 )
	{
		switch( event.type )
		{
		case ENET_EVENT_TYPE_CONNECT:
			// TODO : entity creation syncing to new peers
			cout << "Added peer" << endl;
			PeerList.push_back( event.peer );
			if( Mode == EMM_SERVER )
			{
				deque<u8> syncdata;
				deque<u8> tempdata;
				for( u32 i=0; i<Game->getEntityList().size(); i++ )
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
//			cout << "Got new data" << endl;
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
	}

	if( PeerList.size() == 0 && Mode == EMM_CLIENT )
		isConnected = false;
	
	NetData* data = NULL;
	while( (data = getMessage( IncomingData )) != NULL )
	{
		if( data->MsgType == ENMT_PING )
			continue;
		cout << "Decoded a message..." << endl;

		MessageList[data->net_id].push( data );

		if( data->MsgType == ENMT_CREATE )
		{
			Game->createObject( data->net_id );
		}
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
			deque<u8> streambuffer = makeSyncMessage( OutData );
			while( streambuffer.size() > 0 )
			{
				OutgoingData.push_back( streambuffer.front() );
				streambuffer.pop_front();
			}
			OutData->drop();
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
	}
	else if( event.type != ENET_EVENT_TYPE_CONNECT )
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection was unsuccesful..." << endl;
		isConnected = false;
	}
	else
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection timed out..." << endl;
		isConnected = false;
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
