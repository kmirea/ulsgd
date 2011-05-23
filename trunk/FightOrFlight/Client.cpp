#include <irrBullet/rigidbody.h>
#include <irrlicht/ITimer.h>

#include "Client.h"
#include "GameManager.h"

irr::scene::ICameraSceneNode* debug_cam = NULL;

Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, EMM_CLIENT, NetID )
{
	client_camera = Game->getWorldManager()->getIrrlichtDriver()->getSceneManager()->addCameraSceneNode( getPhysicsObject()->getDrawMesh() );
	client_camera->bindTargetAndRotation( true );
	
	Physics->getDrawMesh()->setVisible( false );
	
	InputData.AXIS_Pitch = InputData.AXIS_Roll = InputData.AXIS_Throttle = InputData.AXIS_Yaw;
	InputData.Trigger = false;
	
	SendUpdate = false;
}

Client::~Client()
{
	// TODO
}

#define AXIS irr::SEvent::SJoystickEvent::

bool Client::OnEvent( const irr::SEvent& Event )
{
	Physics->getBody()->updateObject();
	
	const s16 *axis = Event.JoystickEvent.Axis;
	
	if( Event.EventType == irr::EET_JOYSTICK_INPUT_EVENT )
	{
		if( axis[AXIS AXIS_X] > 2048 || axis[AXIS AXIS_X] < -2048 )
		{
			InputData.AXIS_Roll = (f32)axis[AXIS AXIS_X] / (f32)S16_MAX;
			SendUpdate = true;
		}
		if( axis[AXIS AXIS_Y] > 2048 || axis[AXIS AXIS_Y] < -2048 )
		{
			InputData.AXIS_Pitch = (f32)axis[AXIS AXIS_Y] / (f32)S16_MAX;
			SendUpdate = true;
		}
		if( axis[AXIS AXIS_R] > 2048 || axis[AXIS AXIS_R] < -2048 )
		{
			InputData.AXIS_Throttle = (f32)axis[AXIS AXIS_R] / (f32)S16_MAX;
			SendUpdate = true;
		}
		if( axis[AXIS AXIS_Z] > 2048 || axis[AXIS AXIS_Z] < -2048 )
		{
			InputData.AXIS_Yaw =(f32)axis[AXIS AXIS_Z] / (f32)S16_MAX;
			SendUpdate = true;
		}
		if( Event.JoystickEvent.IsButtonPressed(0) )
		{
			InputData.Trigger = true;
			SendUpdate = true;
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
		if( input!= NULL )
		{
			if( input->MsgType == ENMT_SYNC )
			{
				Physics->getDrawMesh()->setPosition( irr::core::vector3df( input->Create.Position[0],input->Create.Position[1],input->Create.Position[2] ) );
				Physics->getDrawMesh()->setRotation( irr::core::vector3df( input->Create.Rotation[0],input->Create.Position[1],input->Create.Position[2] ) );
				Physics->getBody()->setLinearVelocity( irr::core::vector3df( input->Create.LinearVelocity[0],input->Create.LinearVelocity[1],input->Create.LinearVelocity[2] ) );
				Physics->getBody()->setAngularVelocity( irr::core::vector3df( input->Create.AngularVelocity[0],input->Create.AngularVelocity[1],input->Create.AngularVelocity[2] ) );
			}
		}
		input->drop();
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
	if( SendUpdate )
	{	
		Update = new NetData();
		Update->grab();
		Update->MessageStart = Message_Begin;
		Update->MsgTime = Game->getTimer()->getTimeMS();
		Update->MsgType = ENMT_INPUT;
		Update->net_id = Network->getNetID();
		Update->MessageEnd = Message_End;

		Update->Input = InputData;

		InputData.AXIS_Pitch = InputData.AXIS_Roll = InputData.AXIS_Throttle = InputData.AXIS_Yaw;
		InputData.Trigger = false;

		Network->sendData( Update );
		Update->drop();
	}
}

string Client::getDebugInfo() const
{
	return string("Client");
}
