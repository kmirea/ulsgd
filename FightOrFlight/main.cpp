/* 
 * File:   main.cpp
 * Author: chris
 *
 * Created on March 10, 2011, 6:47 PM
 */

#include <cstdlib>

#include "GameManager.h"

using namespace std;

/*
 * 
 */
GameManager* Game = NULL;

void killserver()
{
	Game->endGame();
	Game->drop();
}

int main(int argc, char** argv)
{
	Game = new GameManager( argc, argv );
	Game->grab();

	atexit( killserver );

	while( Game->run() )
	{
		Game->getNetworkManager()->update();

		for( u32 i=0; i<Game->getEntityList().size(); i++ )
		{
			Game->getEntityList()[i]->update();
		}

		Game->getWorldManager()->update();

		Game->getNetworkManager()->sendLocalData();
	}
	
	return EXIT_SUCCESS;
}

