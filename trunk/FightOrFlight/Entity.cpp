#include "Entity.h"

#include "GameManager.h"

Entity::Entity(GameManager* game, NETID netid) : ReferenceCountedObject(),
		Game(game),
		Network( new NetworkObject( game->getNetworkManager(), netid) ),
		Physics( new PhysicsObject( game->getWorldManager()) )
{
	Network->grab();
	Physics->grab();
}

Entity::~Entity()
{

}

NetworkObject* Entity::getNetworkObject() const
{

}

PhysicsObject* Entity::getPhysicsObject() const
{

}

void Entity::update()
{
	
}

string Entity::getDebugInfo() const
{
	return string("Entity");
}