#include "WorldManager.h"
#include "PhysicsObject.h"

WorldManager::WorldManager(GameManager* game, E_MANAGER_MODE mode) :
	ReferenceCountedObject(), Game(game), Mode(mode)
{

}

WorldManager::~WorldManager()
{

}

void WorldManager::update()
{
	
}

bool WorldManager::run()
{
	return true;
}

string WorldManager::getDebugInfo() const
{
	return string("WorldManager");
}