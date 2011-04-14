#include "Entity.h"

#include "GameManager.h"

#define MAX_SYNC_TIME 500

Entity::Entity(GameManager* game, E_MANAGER_MODE mode, NETID netid) : ReferenceCountedObject(),
		Game(game), Mode(mode),
		Network( new NetworkObject( game->getNetworkManager(), netid) ),
		LastTick(Game->getTimer()->getTime())
{
	PhysicsObjectCreationStruct pocs;

	NetData* data = Network->getInStream();

	if( data != NULL && data->MsgType == ENMT_CREATE )
	{
		pocs.MeshName = data->Create.Meshname;
		pocs.CollisionName = pocs.MeshName;
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

	time_for_next_update = Game->getTimer()->getTime() + MAX_SYNC_TIME;


}

Entity::Entity(GameManager* game, E_MANAGER_MODE mode, NETID NetID, PhysicsObject* physics ) :
		ReferenceCountedObject(), Game(game), Mode(mode),
		Network( new NetworkObject (game->getNetworkManager(), NetID) ),
		Physics(physics),
		LastTick(Game->getTimer()->getTime())

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

	if( Mode == EMM_SERVER )
	{
		for( u32 i=0; i<Game->getEntityList().size(); i++ )
		{
			if( Game->getEntityList()[i] != this )
				Game->getEntityList()[i]->applyGravity( Physics->getDrawMesh()->getPosition(), Physics->getLocalData().Mass );
		}
	}
	
	Physics->update( Network->getInStream() );

	NetData* Update = NULL;
	if( Mode == EMM_SERVER && (time_for_next_update <= Game->getTimer()->getTime()
			|| Physics->getBody()->getCollisionFlags() != ECF_NO_CONTACT_RESPONSE ) )
	{
		time_for_next_update = Game->getTimer()->getTime() + MAX_SYNC_TIME;
		Update = new NetData();
		Update->grab();
		Update->MessageStart = Message_Begin;
		Update->MsgTime = Game->getTimer()->getTime();
		Update->MsgType = ENMT_SYNC;
		Update->net_id = Network->getNetID();
		Update->MessageEnd = Message_End;

		for( u32 i=0; i<3; i++ )
		{
			Update->Sync.Position[i] = Physics->getLocalData().Position[i];
			Update->Sync.Rotation[i] = Physics->getLocalData().Rotation[i];
			Update->Sync.LinearVelocity[i] = Physics->getLocalData().LinearVelocity[i];
			Update->Sync.AngularVelocity[i] = Physics->getLocalData().AngularVelocity[i];
		}

		Network->sendData( Update );
		Update->drop();
	}
}

#define BIG_G 0.00000000006673f

void Entity::applyGravity( const irr::core::vector3df& OtherPosition, f32 Mass )
{
	irr::core::vector3df force_vec = (OtherPosition - Physics->getDrawMesh()->getPosition()).normalize();
	f32 distance_sqr = Physics->getDrawMesh()->getPosition().getDistanceFromSQ( OtherPosition );

	f32 force = BIG_G * Mass * Physics->getLocalData().Mass / distance_sqr;

	force_vec *= force * (Game->getTimer()->getTime() - LastTick)/1000.0f;

	Physics->getBody()->applyCentralForce( force_vec );
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
