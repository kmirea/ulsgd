#include "Entity.h"

#include "GameManager.h"

Entity::Entity(GameManager* game, NETID netid) : ReferenceCountedObject(),
		Game(game),
		Network( new NetworkObject( game->getNetworkManager(), netid) ),
		Physics( new PhysicsObject( game->getWorldManager()) )
{
	Game->grab();
	Network->grab();
	Physics->grab();
}

Entity::Entity(GameManager* game, NETID NetID, PhysicsObject* physics ) :
		ReferenceCountedObject(), Game(game),
		Network( new NetworkObject (game->getNetworkManager(), NetID) ),
		Physics(physics)

{
	Game->grab();
	Network->grab();
	Physics->grab();
}

Entity::~Entity()
{
	Game->drop();
	Network->drop();
	Physics->drop();
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