#include <irrlicht/EDriverTypes.h>
#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/irrArray.h>

#include "GameManager.h"
#include "WorldManager.h"
#include "PhysicsObject.h"

WorldManager::WorldManager(GameManager* game, E_MANAGER_MODE mode) :
	ReferenceCountedObject(), Game(game), Mode(mode)
{
	if( Mode == EMM_CLIENT )
	{
		/*
		 * params are as follows:
		 * Rasterizer Backend (OpenGL)
		 * Resolution (800 x 600)
		 * Color Depth (32 bit)
		 * Fullscreen (false)
		 * Stencil Buffer (true, needed to draw shadows)
		 * VSync (true, optional)
		 * Event Receiver (Need to use the client for this one)
		 */
		Irrlicht = irr::createDevice( irr::video::EDT_OPENGL,
									 irr::core::dimension2d<u32>(800, 600), 32,
									 false, true, true, NULL );
		irr::scene::ILightSceneNode* light = Irrlicht->getSceneManager()->addLightSceneNode();
		light->setLightType( irr::video::ELT_POINT );
		light->setRadius( 1000 );
		light->setPosition( irr::core::vector3df(0, 500, 0) );
		
		irr::core::array<irr::SJoystickInfo> joystick_info;
		Irrlicht->activateJoysticks( joystick_info );
	}
	else if ( Mode == EMM_SERVER )
	{
		Irrlicht = irr::createDevice( irr::video::EDT_NULL );
	}
	else
	{
		cerr << "Invalid World Service State, exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	irrBullet = new	irrBulletWorld( Irrlicht, true,
#ifdef DEBUG
		true
#else
		false
#endif
			);
	irrBullet->setGravity( irr::core::vector3df(0,0,0) );

	LastTime = Irrlicht->getTimer()->getTime();
}

WorldManager::~WorldManager()
{
	delete irrBullet;

	Irrlicht->closeDevice();
}

void WorldManager::preUpdate()
{

	irr::video::IVideoDriver* video = Irrlicht->getVideoDriver();
	irr::scene::ISceneManager* scene = Irrlicht->getSceneManager();
	irr::gui::IGUIEnvironment* gui = Irrlicht->getGUIEnvironment();

	irrBullet->stepSimulation( (Game->getTimer()->getTime()-LastTime)/1000.0f, 120, 1.0f/60.0f );
	//irrBullet->stepSimulation( (Game->getTimer()->getTime()-LastTime)/1000.0f );
	
	video->beginScene( true, true, irr::video::SColor(255,0,0,255) );
}

void WorldManager::postUpdate()
{
	irr::video::IVideoDriver* video = Irrlicht->getVideoDriver();
	irr::scene::ISceneManager* scene = Irrlicht->getSceneManager();
	irr::gui::IGUIEnvironment* gui = Irrlicht->getGUIEnvironment();
	
#ifdef DEBUG
	irrBullet->debugDrawWorld( true );
	irrBullet->debugDrawProperties( true );
#endif

	scene->drawAll();
	gui->drawAll();

	video->endScene();
	
	LastTime = Game->getTimer()->getTime();
}

bool WorldManager::run()
{
	return Irrlicht->run();
}

string WorldManager::getDebugInfo() const
{
	return string("WorldManager");
}

void WorldManager::setClient( Client* ClientEntity )
{
	Irrlicht->setEventReceiver( ClientEntity );
}

irr::IrrlichtDevice* WorldManager::getIrrlichtDriver() const
{
	return Irrlicht;
}

irrBulletWorld* WorldManager::getIrrBulletDriver() const
{
	return irrBullet;
}
