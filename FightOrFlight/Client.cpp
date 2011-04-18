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

#define accelleration 0.0001f/((Game->getTimer()->getTime() - LastTick)*0.001f)

bool Client::OnEvent( const irr::SEvent& Event )
{
	Physics->getBody()->updateObject();

	// We can do joystick input pretty darned easy here. Just need to create a
	// calibration mechanism to pick our axis

	if( Event.EventType == irr::EET_KEY_INPUT_EVENT )
	{
		switch( Event.KeyInput.Key )
		{
		case irr::KEY_UP:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += irr::core::vector3df( 0,0,1 );
			}
			break;
		case irr::KEY_DOWN:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += irr::core::vector3df( 0,0,-1);
			}
			break;
		case irr::KEY_LEFT:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += irr::core::vector3df(-1,0,0);
			}
			break;
		case irr::KEY_RIGHT:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += irr::core::vector3df(1,0,0);
			}
			break;
		case irr::KEY_PRIOR:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(0,0,-1);
			}
			break;
		case irr::KEY_HOME:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(0,0,1);
			}
			break;
		case irr::KEY_END:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(0,-1,0);
			}
			break;
		case irr::KEY_NEXT:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(0,1,0);
			}
			break;
		case irr::KEY_PLUS:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(-1,0,0);
			}
			break;
		case irr::KEY_MINUS:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_angvel += irr::core::vector3df(1,0,0);
			}
			break;
		}
	}

	irr::core::matrix4 mat = Physics->getDrawMesh()->getAbsoluteTransformation();
	if( update_linvel.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_linvel );
		update_linvel.setLength( accelleration );
	}
	if( update_angvel.getLengthSQ() != 0 )
	{
		mat.rotateVect( update_angvel );
		update_angvel.setLength( accelleration );
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

	if( update_angvel.getLengthSQ() == 0 )
	{
		update_angvel = Physics->getBody()->getAngularVelocity() * -1.0f;
		if( update_angvel.getLengthSQ() != 0 )
		{
			if( update_angvel.getLengthSQ() > accelleration * accelleration )
			{
				update_angvel.setLength( accelleration );
			}
			send_update = true;
		}
	}
	
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
