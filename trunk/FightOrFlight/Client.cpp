#include "Client.h"
#include "GameManager.h"

irr::scene::ICameraSceneNode* debug_cam = NULL;

Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, EMM_CLIENT, NetID )
{
	camera_target = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_target->setPosition( irr::core::vector3df(0,0,1) );

	camera_up = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_up->setPosition( irr::core::vector3df(0,1,0) );

	camera_side = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_side->setPosition( irr::core::vector3df(1,0,0) );

	client_camera = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode( getPhysicsObject()->getDrawMesh() );
	client_camera->bindTargetAndRotation( true );

//	debug_cam = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode();
//	Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->setActiveCamera( debug_cam );

	send_update = false;

	update_angvel = update_linvel = irr::core::vector3df(0,0,0);
}

Client::~Client()
{
	// TODO
}

bool Client::OnEvent( const irr::SEvent& Event )
{
	Physics->getBody()->updateObject();

	if( Event.EventType == irr::EET_KEY_INPUT_EVENT )
	{
		switch( Event.KeyInput.Key )
		{
		case irr::KEY_UP:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += ( (camera_target->getAbsolutePosition() -
						client_camera->getAbsolutePosition()).normalize() * (Game->getTimer()->getTime()-LastTick)/1000.0f * .5 );
				return true;
			}
		case irr::KEY_DOWN:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += ( (camera_target->getAbsolutePosition() -
						client_camera->getAbsolutePosition()).normalize() * (Game->getTimer()->getTime()-LastTick)/-1000.0f * .5 );
				return true;
			}
		case irr::KEY_LEFT:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += (camera_side->getAbsolutePosition() - client_camera->getAbsolutePosition()).normalize() * (Game->getTimer()->getTime()-LastTick)*.001f * .5;
				return true;
			}
		case irr::KEY_RIGHT:
			if( Event.KeyInput.PressedDown )
			{
				send_update = true;
				update_linvel += ( (camera_side->getAbsolutePosition() -
						client_camera->getAbsolutePosition()).normalize() * (Game->getTimer()->getTime()-LastTick)/-1000.0f * .5 );
				return true;
			}
		}
	}
	return true;
}

void Client::update()
{
	Network->update();
	
	Physics->update( Network->getInStream() );

//	if( send_update )
//		Physics->getBody()->applyCentralForce( update_linvel );

	Physics->update();

	camera_side->updateAbsolutePosition();
	camera_target->updateAbsolutePosition();
	camera_up->updateAbsolutePosition();
	client_camera->updateAbsolutePosition();

	client_camera->setTarget( camera_target->getAbsolutePosition() );
	client_camera->setUpVector( (camera_up->getAbsolutePosition() - client_camera->getAbsolutePosition()).normalize() );

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
