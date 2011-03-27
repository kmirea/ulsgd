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

	}
	else
	{
		cerr << "Invalid World Service State, exiting..." << endl;
		exit(EXIT_FAILURE);
	}
}

WorldManager::~WorldManager()
{

}

void WorldManager::update()
{
	
}

bool WorldManager::run()
{
	return true;
}

string WorldManager::getDebugInfo() const
{
	return string("WorldManager");
}