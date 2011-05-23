#include "Entity.h"

#include "GameManager.h"

#define MIN_TRIGGER_TIME 100
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
	TimeForNextTrigger = Game->getTimer()->getTimeMS() + MIN_TRIGGER_TIME;
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
		if( time_for_next_update >= Game->getTimer()->getTimeMS() )
		{
			Physics->getBody()->activate( true );
			time_for_next_update = Game->getTimer()->getTimeMS() + MAX_SYNC_TIME;
		}
	}
	
	Network->update();
	NetData* input = Network->getInStream();
	do
	{
		if( input!= NULL )
		{
			if( input->MsgType == ENMT_SYNC )
			{
				Physics->getDrawMesh()->setPosition( irr::core::vector3df( input->Create.Position[0],
						input->Create.Position[1],input->Create.Position[2] ) );
				Physics->getDrawMesh()->setRotation( irr::core::vector3df( input->Create.Rotation[0],
						input->Create.Position[1],input->Create.Position[2] ) );
				Physics->getBody()->setLinearVelocity( irr::core::vector3df( input->Create.LinearVelocity[0],
						input->Create.LinearVelocity[1],input->Create.LinearVelocity[2] ) );
				Physics->getBody()->setAngularVelocity( irr::core::vector3df( input->Create.AngularVelocity[0],
						input->Create.AngularVelocity[1],input->Create.AngularVelocity[2] ) );
			}
			else if( input->MsgType == ENMT_INPUT )
			{
				CalculateForces( input->Input );
				u32 timems = Game->getTimer()->getTimeMS();
				if( input->Input.Trigger && timems >= TimeForNextTrigger )
				{
					// Bang! (create a bullet here. we don't have bullet data yet...)
					TimeForNextTrigger = timems + (timems - TimeForNextTrigger) + MIN_TRIGGER_TIME;
				}
			}
			if( input->MsgType != ENMT_DESTROY || (input->MsgType == ENMT_INPUT && input->Input.AXIS_Pitch == 0.0f && 
					input->Input.AXIS_Roll == 0.0f && input->Input.AXIS_Yaw == 0.0f) )
			{
				CalculateSlowDown();
			}
		}
		input->drop();
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

#define max_lin_thrust 1.0f
#define max_ang_thrust 0.1f

#define max_lin_vel_sqr 100.0f
#define max_ang_vel_sqr 1.0f

void Entity::CalculateForces( const NetData::Message_Input& Input )
{
	irr::core::matrix4 mat = Physics->getDrawMesh()->getAbsoluteTransformation();
	
	f32 dt = Game->getTimer()->getTickS();
	f32 mass = getPhysicsObject()->getLocalData().Mass;
	
	irr::core::vector3df linear_velocity = Physics->getBody()->getLinearVelocity();
	irr::core::vector3df angular_velocity = Physics->getBody()->getAngularVelocity();
	
	irr::core::vector3df new_lin_force ( 0, 0, Input.AXIS_Throttle ),
			rev_lin_force ( linear_velocity * -1.0f ),
			new_ang_force ( Input.AXIS_Pitch * 360, Input.AXIS_Yaw * 360, Input.AXIS_Roll * 360 ), // % of 360 rotation
			rev_ang_force ( angular_velocity * -1.0f );
	
	new_lin_force.setLength( max_lin_thrust );
	rev_lin_force.setLength( max_lin_thrust );
	
	new_ang_force.setLength( max_ang_thrust );
	rev_ang_force.setLength( max_ang_thrust );
	
	mat.rotateVect( new_lin_force );
	mat.rotateVect( new_ang_force );
	
	if( (new_lin_force / mass * dt + linear_velocity).getLengthSQ() >= max_lin_vel_sqr )
	{
		new_lin_force += rev_lin_force;
	}
	
	if( (new_ang_force / mass * dt + angular_velocity).getLengthSQ() >= max_ang_vel_sqr )
	{
		new_ang_force += rev_ang_force;
	}
	
	Physics->getBody()->applyCentralForce( new_lin_force );
	Physics->getBody()->applyTorque( new_ang_force );
}

#define MAX_SLOWDOWN_PERCENT 0.20f

void Entity::CalculateSlowDown()
{
	float dt = Game->getTimer()->getTimeS();
	float mass = Physics->getLocalData().Mass;
	irr::core::vector3df angular_velocity = Physics->getBody()->getAngularVelocity();
	
	irr::core::vector3df rev_ang_force = angular_velocity * -1.0f * mass * dt * MAX_SLOWDOWN_PERCENT;
	
	if( rev_ang_force.getLengthSQ() > max_ang_thrust * max_ang_thrust )
		rev_ang_force.setLength(max_ang_thrust);
	
	Physics->getBody()->applyTorque( rev_ang_force );
}
