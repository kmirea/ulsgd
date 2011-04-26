#include <irrBullet/rigidbody.h>

#include "Client.h"
#include "GameManager.h"

irr::scene::ICameraSceneNode* debug_cam = NULL;

Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, EMM_CLIENT, NetID ), update_linvel(irr::core::vector3df(0,0,0)),
		update_angvel(irr::core::vector3df(0,0,0))
{
	client_camera = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode( getPhysicsObject()->getDrawMesh() );
	client_camera->bindTargetAndRotation( true );

//	debug_cam = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode();
//	Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->setActiveCamera( debug_cam );

	send_update = false;
}

Client::~Client()
{
	// TODO
}

#define accell(x) x/((Game->getTimer()->getTime() - LastTick)*0.001f)
#define lin_accell 1.0f
#define ang_accell 0.1f

#define max_lin_vel 10
#define max_ang_vel 1

#define AXIS irr::SEvent::SJoystickEvent::

bool Client::OnEvent( const irr::SEvent& Event )
{
	Physics->getBody()->updateObject();

	// We can do joystick input pretty darned easy here. Just need to create a
	// calibration mechanism to pick our axis
	
	const s16 *axis = Event.JoystickEvent.Axis;
	
	if( Event.EventType == irr::EET_JOYSTICK_INPUT_EVENT )
	{
		if( axis[AXIS AXIS_X] > 2048 || axis[AXIS AXIS_X] < -2048 )
		{
			send_update = true;
			update_angvel += irr::core::vector3df( 0,1,0 ) * accell( ang_accell * (f32)axis[AXIS AXIS_X] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_Y] > 2048 || axis[AXIS AXIS_Y] < -2048 )
		{
			send_update = true;
			update_angvel += irr::core::vector3df( -1,0,0 ) * accell( ang_accell * (f32)axis[AXIS AXIS_Y] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_R] > 2048 || axis[AXIS AXIS_R] < -2048 )
		{
			send_update = true;
			update_angvel += irr::core::vector3df( 0,0,-1 ) * accell( ang_accell * (f32)axis[AXIS AXIS_R] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_Z] > 2048 || axis[AXIS AXIS_Z] < -2048 )
		{
			send_update = true;
			update_linvel += irr::core::vector3df( 0,0,-1 ) * accell( lin_accell * (f32)axis[AXIS AXIS_Z] / (f32)S16_MAX );
		}
	}
	
	irr::core::matrix4 mat = Physics->getDrawMesh()->getAbsoluteTransformation();
	if( update_linvel.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_linvel );
	}
	if( update_angvel.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_angvel );
	}
	
	if( Physics->getBody()->getLinearVelocity().getLengthSQ() >= max_lin_vel * max_lin_vel )
	{
		update_linvel = irr::core::vector3df( 0, 0, 0 );
	}
	if( Physics->getBody()->getAngularVelocity().getLengthSQ() >= max_ang_vel * max_ang_vel )
	{
		update_angvel = irr::core::vector3df( 0,0,0 );
	}
	else if( update_angvel.getLengthSQ() == 0 )
	{
		update_angvel = Physics->getBody()->getAngularVelocity() * -1.0f;
		send_update = true;
	}
	
	return true;
}

void Client::update()
{

	Network->update();
	NetData* input = Network->getInStream();
	do
	{
		Physics->update( input );
		Network->update();
	} while( (input = Network->getInStream()) != NULL );

	Physics->getDrawMesh()->updateAbsolutePosition();

	irr::core::vector3df target ( 0,0,1 );
	irr::core::vector3df upvec ( 0,1,0 );
	Physics->getDrawMesh()->getAbsoluteTransformation().rotateVect( target );
	Physics->getDrawMesh()->getAbsoluteTransformation().rotateVect( upvec );
	target += Physics->getDrawMesh()->getAbsolutePosition();
	
	client_camera->setTarget( target );
	client_camera->setUpVector( upvec );
	
	NetData* Update = NULL;
	if( send_update )
	{
		Update = new NetData();
		Update->grab();
		Update->MessageStart = Message_Begin;
		Update->MsgTime = Game->getTimer()->getTime();
		Update->MsgType = ENMT_APPLY_FORCE;
		Update->net_id = Network->getNetID();
		Update->MessageEnd = Message_End;

		Update->ApplyForce.AngularVelocity[0] = update_angvel.X;
		Update->ApplyForce.AngularVelocity[1] = update_angvel.Y;
		Update->ApplyForce.AngularVelocity[2] = update_angvel.Z;
		Update->ApplyForce.LinearVelocity[0] = update_linvel.X;
		Update->ApplyForce.LinearVelocity[1] = update_linvel.Y;
		Update->ApplyForce.LinearVelocity[2] = update_linvel.Z;

		update_linvel = irr::core::vector3df(0,0,0);
		update_angvel = irr::core::vector3df(0,0,0);

		send_update = false;

		Network->sendData( Update );
		Update->drop();
	}
	
	LastTick = Game->getTimer()->getTime();
}

string Client::getDebugInfo() const
{
	return string("Client");
}
