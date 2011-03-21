#include "NetworkManager.h"
#include <enet/enet.h>

NetworkManager::NetworkManager( GameManager* game, E_MANAGER_MODE mode ) : ReferenceCountedObject(),
		Game(game), Mode(mode)
{

}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::update()
{

}

deque<u8> NetworkManager::getUpdateData( NETID NetObject )
{
	
}

string NetworkManager::getDebugInfo()
{
	return string("NetworkManager");
}
