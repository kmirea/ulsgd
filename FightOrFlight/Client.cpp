#include <irrBullet/rigidbody.h>
#include <irrlicht/ITimer.h>

#include "Client.h"
#include "GameManager.h"

irr::scene::ICameraSceneNode* debug_cam = NULL;

Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, EMM_CLIENT, NetID ), update_lin_force(irr::core::vector3df(0,0,0)),
		update_ang_force(irr::core::vector3df(0,0,0))
{
	client_camera = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode( getPhysicsObject()->getDrawMesh() );
	client_camera->bindTargetAndRotation( true );

//	debug_cam = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode();
//	Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->setActiveCamera( debug_cam );

	send_ang_update = send_lin_update = false;
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
	
	const s16 *axis = Event.JoystickEvent.Axis;
	
	if( Event.EventType == irr::EET_JOYSTICK_INPUT_EVENT )
	{
		if( axis[AXIS AXIS_X] > 2048 || axis[AXIS AXIS_X] < -2048 )
		{
			send_ang_update = true;
			update_ang_force += irr::core::vector3df( 0,1,0 ) * accell( ang_accell * (f32)axis[AXIS AXIS_X] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_Y] > 2048 || axis[AXIS AXIS_Y] < -2048 )
		{
			send_ang_update = true;
			update_ang_force += irr::core::vector3df( -1,0,0 ) * accell( ang_accell * (f32)axis[AXIS AXIS_Y] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_R] > 2048 || axis[AXIS AXIS_R] < -2048 )
		{
			send_ang_update = true;
			update_ang_force += irr::core::vector3df( 0,0,-1 ) * accell( ang_accell * (f32)axis[AXIS AXIS_R] / (f32)S16_MAX );
		}
		if( axis[AXIS AXIS_Z] > 2048 || axis[AXIS AXIS_Z] < -2048 )
		{
			send_lin_update = true;
			update_lin_force += irr::core::vector3df( 0,0,-1 ) * accell( lin_accell * (f32)axis[AXIS AXIS_Z] / (f32)S16_MAX );
		}
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
	
	CalculateForces();
	
	if( update_ang_force.getLengthSQ() == 0 && !send_ang_update )
	{
		f32 dt = (Game->getTimer()->getTime() - LastTick)*.001f;
		if( dt <= 0.0f )
		{
			dt = 0.0001f;
		}
		update_ang_force = Physics->getBody()->getAngularVelocity() / dt * Physics->getLocalData().Mass * -0.95f;
		send_ang_update = true;
	}
	
	NetData* Update = NULL;
	if( send_ang_update || send_lin_update )
	{	
		Update = new NetData();
		Update->grab();
		Update->MessageStart = Message_Begin;
		Update->MsgTime = Game->getTimer()->getTime();
		Update->MsgType = ENMT_APPLY_FORCE;
		Update->net_id = Network->getNetID();
		Update->MessageEnd = Message_End;

		Update->ApplyForce.AngularVelocity[0] = update_ang_force.X;
		Update->ApplyForce.AngularVelocity[1] = update_ang_force.Y;
		Update->ApplyForce.AngularVelocity[2] = update_ang_force.Z;
		Update->ApplyForce.LinearVelocity[0] = update_lin_force.X;
		Update->ApplyForce.LinearVelocity[1] = update_lin_force.Y;
		Update->ApplyForce.LinearVelocity[2] = update_lin_force.Z;

		update_lin_force = irr::core::vector3df(0,0,0);
		update_ang_force = irr::core::vector3df(0,0,0);

		send_ang_update = send_lin_update = false;

		Network->sendData( Update );
		Update->drop();
	}
	
	LastTick = Game->getTimer()->getTime();
}

string Client::getDebugInfo() const
{
	return string("Client");
}

#define max_lin_vel_sqr 100
#define max_ang_vel_sqr	1

void Client::CalculateForces()
{
	// We can apply forces to get a velocity, or we can apply forces to get an acceleration. 
	// See if you can pick out which will be harder...
	
	irr::core::matrix4 mat = Physics->getDrawMesh()->getAbsoluteTransformation();
	if( update_lin_force.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_lin_force );
	}
	if( update_ang_force.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_ang_force );
	}
	
	f32 dt = (Game->getTimer()->getTime() - LastTick)*.001f;
	irr::core::vector3df al, vil, vfl, aa, via, vfa;
	al = update_lin_force / Physics->getLocalData().Mass;
	vil = Physics->getBody()->getLinearVelocity();
	vfl = al * dt + vil;
	
	if( vfl.getLengthSQ() > max_lin_vel_sqr && vfl.getLengthSQ() > vil.getLengthSQ() )
	{
		cout << '*';
		update_lin_force.set( 0, 0, 0 );
	}
	
	aa = update_ang_force / Physics->getLocalData().Mass;
	via = Physics->getBody()->getAngularVelocity();
	vfa = aa * dt + via;
	
	if( vfa.getLengthSQ() > max_ang_vel_sqr && vfa.getLengthSQ() > via.getLengthSQ() )
	{
		cout << '^';
		update_ang_force.set( 0, 0, 0 );
	}
	
#ifdef DEBUG
	cout << "LIN_VEL: " << vfl.getLength() << "\tANG_VEL: " << vfa.getLength() << endl;
#endif
}
