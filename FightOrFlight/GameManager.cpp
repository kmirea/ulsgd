#include <enet/enet.h>
#include "GameManager.h"

GameManager::GameManager( u32 argc, c8** argv ) : ReferenceCountedObject()
{
	if( argc > 1 )
	{
		if( string(argv[1]) == string("-server") )
		{
			Network = new NetworkManager( this, EMM_SERVER );
			World = new WorldManager( this, EMM_SERVER );

			if( !loadScene(argv[2]) )
			{
				cerr << "Please specify a valid scene file..." << endl;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			cerr << "Invalid option, exiting" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		Network = new NetworkManager( this, EMM_CLIENT );
		
		string serverip;
		
		cout << "Please specify server IP: " << endl;
		cin >> serverip;

		ENetAddress Address;
		enet_address_set_host( &Address, "localhost" );

		Network->setConnectionAddress( Address );

		World = new WorldManager( this, EMM_CLIENT );
	}
//	GUI = new GUIManager( this );
//	Sound = new SoundManager( this );
}

GameManager::~GameManager()
{
	Network->drop();

	for( u32 i=0; i<EntityList.size(); i++ )
		EntityList[i]->drop();

	World->drop();
}

bool GameManager::run()
{
	return ( World->run() && Network->run() );
}

NetworkManager* GameManager::getNetworkManager() const
{
	return Network;
}

WorldManager* GameManager::getWorldManager() const
{
	return World;
}

GUIManager* GameManager::getGUIManager() const
{
	return GUI;
}

SoundManager* GameManager::getSoundManager() const
{
	return Sound;
}

void GameManager::createObject( NETID NetID )
{

}

void GameManager::destroyObject( NETID NetID )
{

}

string GameManager::getDebugInfo() const
{
	return string("GameManager");
}

const vector<Entity*>& GameManager::getEntityList() const
{
	return EntityList;
}

bool GameManager::loadScene(string filename)
{
	ifstream File (filename.c_str());

	if( !File )
	{
		cerr << "Could not load file " << filename << endl;
	}

	
}
