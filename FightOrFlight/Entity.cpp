#include "Entity.h"

#include "GameManager.h"

Entity::Entity(GameManager* game, NETID netid) : ReferenceCountedObject(),
		Game(game),
		Network( new NetworkObject( game->getNetworkManager(), netid) )
{
	PhysicsObjectCreationStruct pocs;

	Network->update();
	NetData* data = Network->getInStream();

	if( data != NULL && data->MsgType == ENMT_CREATE )
	{
		pocs.MeshName = data->Create.Meshname;
		pocs.CollisionName = pocs.MeshName + string("_col");
		pocs.Mass = data->Create.Mass;
		for( u32 i=0; i<3; i++ )
		{
			pocs.Position[i] = data->Create.Position[i];
			pocs.Rotation[i] = data->Create.Rotation[i];
			pocs.Scale[i] = data->Create.Scale[i];
			pocs.LinearVelocity[i] = data->Create.LinearVelocity[i];
			pocs.AngularVelocity[i] = data->Create.AngularVelocity[i];
		}
	}
	else
	{
		cerr << "Invalid Entity Replication Data, exiting" << endl;
		exit(EXIT_FAILURE);
	}

	Physics = new PhysicsObject( Game->getWorldManager(), pocs );

	Game->grab();
	Network->grab();
	Physics->grab();
}

Entity::Entity(GameManager* game, E_MANAGER_MODE Mode, NETID NetID, PhysicsObject* physics ) :
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
	return Network;
}

PhysicsObject* Entity::getPhysicsObject() const
{
	return Physics;
}

void Entity::update()
{
	Network->update();
	Physics->update();
}

string Entity::getDebugInfo() const
{
	return string("Entity");
}

void Entity::syncCreate() const
{
	NetData* data = new NetData();
	
	data->MessageStart = Message_Begin;
	data->net_id = Network->getNetID();
	data->MsgTime = Game->getTimer()->getTime();
	data->MsgType = ENMT_CREATE;

	strncpy( data->Create.Meshname, Physics->getLocalData().MeshName.c_str(), 15 );

	data->Create.Mass = Physics->getLocalData().Mass;

	for( u32 i=0; i<3; i++ )
	{
			data->Create.Position[i] = Physics->getLocalData().Position[i];
			data->Create.Rotation[i] = Physics->getLocalData().Rotation[i];
			data->Create.Scale[i] = Physics->getLocalData().Scale[i];
			data->Create.LinearVelocity[i] = Physics->getLocalData().LinearVelocity[i];
			data->Create.AngularVelocity[i] = Physics->getLocalData().AngularVelocity[i];
	}

	data->MessageEnd = Message_End;

	Network->sendData( data );
}
