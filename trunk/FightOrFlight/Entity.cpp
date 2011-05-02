#include "Entity.h"

#include "GameManager.h"

#define MAX_SYNC_TIME 10

Entity::Entity(GameManager* game, E_MANAGER_MODE mode, NETID netid) : ReferenceCountedObject(),
		Game(game), Mode(mode),
		Network( new NetworkObject( game->getNetworkManager(), netid) )
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

	time_for_next_update = Game->getTimer()->getTimeMS() + MAX_SYNC_TIME;
}

Entity::Entity(GameManager* game, E_MANAGER_MODE mode, NETID NetID, PhysicsObject* physics ) :
		ReferenceCountedObject(), Game(game), Mode(mode),
		Network( new NetworkObject (game->getNetworkManager(), NetID) ),
		Physics(physics)

{
	Game->grab();
	Network->grab();
	Physics->grab();
	
	time_for_next_update = Game->getTimer()->getTimeMS();
	Physics->getBody()->activate( true );
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
	if( Mode == EMM_CLIENT )
	{
		if( time_for_next_update <= Game->getTimer()->getTimeMS() )
		{
			Physics->getBody()->activate( true );
			time_for_next_update = Game->getTimer()->getTimeMS() + MAX_SYNC_TIME;
		}
	}
	
	Network->update();
	NetData* input = Network->getInStream();
	do
	{
		Physics->update( input );
		Network->update();
	} while( (input = Network->getInStream()) != NULL );
		
	NetData* Update = NULL;
	if( Mode == EMM_SERVER )
	{
		for( u32 i=0; i<Game->getEntityList().size(); i++ )
		{
			if( Game->getEntityList()[i] != this )
				Game->getEntityList()[i]->applyGravity( Physics->getDrawMesh()->getPosition(), Physics->getLocalData().Mass );
		}
		
		Physics->update();
		
		if( time_for_next_update <= Game->getTimer()->getTimeMS() )
		{
			Physics->getBody()->activate( true );
			time_for_next_update = Game->getTimer()->getTimeMS() + MAX_SYNC_TIME;
			
			Update = new NetData();
			Update->grab();
			Update->MessageStart = Message_Begin;
			Update->MsgTime = Game->getTimer()->getTimeMS();
			Update->MsgType = ENMT_SYNC;
			Update->net_id = Network->getNetID();
			Update->MessageEnd = Message_End;

			Update->Sync.Position[0] = Physics->getLocalData().Position[0];
			Update->Sync.Rotation[0] = Physics->getLocalData().Rotation[0];
			Update->Sync.LinearVelocity[0] = Physics->getLocalData().LinearVelocity[0];
			Update->Sync.AngularVelocity[0] = Physics->getLocalData().AngularVelocity[0];

			Update->Sync.Position[1] = Physics->getLocalData().Position[1];
			Update->Sync.Rotation[1] = Physics->getLocalData().Rotation[1];
			Update->Sync.LinearVelocity[1] = Physics->getLocalData().LinearVelocity[1];
			Update->Sync.AngularVelocity[1] = Physics->getLocalData().AngularVelocity[1];

			Update->Sync.Position[2] = Physics->getLocalData().Position[2];
			Update->Sync.Rotation[2] = Physics->getLocalData().Rotation[2];
			Update->Sync.LinearVelocity[2] = Physics->getLocalData().LinearVelocity[2];
			Update->Sync.AngularVelocity[2] = Physics->getLocalData().AngularVelocity[2];
			
			Network->sendData( Update );
			Update->drop();
		}
	}
}

#define BIG_G 0.00000000006673f

void Entity::applyGravity( const irr::core::vector3df& OtherPosition, f32 Mass )
{
	irr::core::vector3df force_vec = (OtherPosition - Physics->getDrawMesh()->getPosition()).normalize();
	f32 distance_sqr = Physics->getDrawMesh()->getPosition().getDistanceFromSQ( OtherPosition );

	f32 force = BIG_G * Mass * Physics->getLocalData().Mass / distance_sqr;

	force_vec *= force * (Game->getTimer()->getTickS());

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
	data->MsgTime = Game->getTimer()->getTimeMS();
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
