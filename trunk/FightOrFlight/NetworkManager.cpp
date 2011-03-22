#include "NetworkManager.h"
#include "GameManager.h"
#include <enet/enet.h>

NetworkManager::NetworkManager( GameManager* game, E_MANAGER_MODE mode ) : ReferenceCountedObject(),
		Game(game), Mode(mode)
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
		break;
	default:
		cerr << "Invalid network service state, exiting..." << endl;
	}
}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::update()
{
	NetData UpdateData;
}

void NetworkManager::sendLocalData()
{
	
}

bool NetworkManager::setConnectionAddress( ENetAddress& Address )
{
	server_name->host = Address.host;

	PeerList.push_back( enet_host_connect( netinterface, server_name, 1 ) );

	if( PeerList.back() == NULL )
	{
		cerr << "No available peers left to connect with." << endl;
		return false;
	}

	ENetEvent event;

	if( enet_host_service( netinterface, &event, 5000 ) > 0 && event.type == ENET_EVENT_TYPE_CONNECT )
	{
		cerr << "Connection was succesful. Syncing with peer..." << endl;
		return true;
	}
	else if( event.type != ENET_EVENT_TYPE_CONNECT )
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection was unsuccesful..." << endl;
		return false;
	}
	else
	{
		enet_peer_reset( PeerList.back() );
		cerr << "Connection timed out..." << endl;
		return false;
	}
}

deque<u8> NetworkManager::getUpdateData( NETID NetObject )
{
	
}

string NetworkManager::getDebugInfo()
{
	return string("NetworkManager");
}
