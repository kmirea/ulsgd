#include "Client.h"
#include "GameManager.h"

Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, EMM_CLIENT, NetID )
{
	camera_target = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_target->setPosition( irr::core::vector3df(0,0,1) );

	camera_up = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_up->setPosition( irr::core::vector3df(0,1,0) );

	camera_side = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addEmptySceneNode( getPhysicsObject()->getDrawMesh() );
	camera_side->setPosition( irr::core::vector3df(1,0,0) );

	client_camera = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode( getPhysicsObject()->getDrawMesh() );

	send_update = false;
}

Client::~Client()
{
	// TODO
}

bool Client::OnEvent( const irr::SEvent& Event )
{
	if( Event.EventType == irr::EET_KEY_INPUT_EVENT )
	{
		switch( Event.KeyInput.Key )
		{
		case irr::KEY_UP:
			send_update = true;
			getPhysicsObject()->getBody()->applyCentralForce( client_camera->getTarget() * .00001 );
			return true;
		case irr::KEY_DOWN:
			send_update = true;
			getPhysicsObject()->getBody()->applyCentralForce( client_camera->getTarget() * -.00001 );
			return true;
		case irr::KEY_LEFT:
			send_update = true;
			getPhysicsObject()->getBody()->applyCentralForce( (camera_side->getAbsolutePosition() -
					client_camera->getAbsolutePosition()).normalize() * -.00001);
			return true;
		case irr::KEY_RIGHT:
			send_update = true;
			getPhysicsObject()->getBody()->applyCentralForce( (camera_side->getAbsolutePosition() -
					client_camera->getAbsolutePosition()).normalize() * .00001 );
			return true;
		}
	}
	return true;
}

void Client::update()
{
	NetData* Update = NULL;
	if( send_update )
	{
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
		send_update = false;
	}

	Network->update();

	Physics->update( Network->getInStream() );

	client_camera->setTarget( camera_target->getAbsolutePosition() );
	client_camera->setUpVector( (camera_up->getAbsolutePosition() - client_camera->getAbsolutePosition()).normalize() );

	if( Update )
	{
		Network->sendData( Update );
		Update->drop();
	}
}

string Client::getDebugInfo() const
{
	return string("Client");
}
