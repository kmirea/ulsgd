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
		netinterface = enet_host_create( server_name, 2, 0, 0 );
		break;
	case EMM_SERVER:
		server_name->host = ENET_HOST_ANY;
		netinterface = enet_host_create( server_name, 2, 0, 0 );
		isConnected = true;
		break;
	default:
		cerr << "Invalid network service state, exiting..." << endl;
	}
}

NetworkManager::~NetworkManager()
{
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
			cout << "Added peer" << endl;
			PeerList.push_back( event.peer );
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			cout << "Got new data" << endl;
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
}

void NetworkManager::sendLocalData()
{
	
}

bool NetworkManager::setConnectionAddress( ENetAddress& Address )
{
	server_name->host = Address.host;

	PeerList.push_back( enet_host_connect( netinterface, server_name, 2 ) );

	if( PeerList.back() == NULL )
	{
		cerr << "No available peers left to connect with." << endl;
		return false;
	}

	ENetEvent event;

	if( enet_host_service( netinterface, &event, 5000 ) > 0 && event.type == ENET_EVENT_TYPE_CONNECT )
	{
		cerr << "Connection was succesful. Syncing with peer..." << endl;
		return isConnected = true;
	}
	else if( event.type != ENET_EVENT_TYPE_CONNECT )
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection was unsuccesful..." << endl;
		return isConnected = false;
	}
	else
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection timed out..." << endl;
		return isConnected = false;
	}
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

string NetworkManager::getDebugInfo() const
{
	return string("NetworkManager");
}
