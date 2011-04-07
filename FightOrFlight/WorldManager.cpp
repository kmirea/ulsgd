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

	irrBullet = new
#ifdef DEBUG
			irrBulletWorld( Irrlicht, true, true );
#else
			irrBulletWorld( Irrlicht, true, false);
#endif
}

WorldManager::~WorldManager()
{
	delete irrBullet;

	Irrlicht->closeDevice();
}

void WorldManager::update()
{
	irr::video::IVideoDriver* video = Irrlicht->getVideoDriver();
	irr::scene::ISceneManager* scene = Irrlicht->getSceneManager();
	irr::gui::IGUIEnvironment* gui = Irrlicht->getGUIEnvironment();

	video->beginScene( true, true, irr::video::SColor(255,0,0,0) );

	irrBullet->stepSimulation( Game->getTimer()->getTime()*0.001f, 120 );

#ifdef DEBUG
	irrBullet->debugDrawWorld( true );
	irrBullet->debugDrawProperties( true );
#endif

	scene->drawAll();
	gui->drawAll();

	video->endScene();
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
