#include <enet/enet.h>
#include "GameManager.h"

GameManager::GameManager( u32 argc, c8** argv ) : ReferenceCountedObject()
{
#ifdef DEBUG
	system("pwd");
#endif
	if( argc > 2 )
	{
		if( string(argv[1]) == string("--server") )
		{
			Mode = EMM_SERVER;
			Network = new NetworkManager( this, Mode );
			World = new WorldManager( this, Mode );

			if( !loadScene( string(argv[2]) ) )
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
		Mode = EMM_CLIENT;
		Network = new NetworkManager( this, Mode );
		
//		string serverip;
		
//		cout << "Please specify server IP: " << endl;
//		cin >> serverip;

		ENetAddress Address;
		Address.host = ENET_HOST_BROADCAST;
//		enet_address_set_host( &Address, "localhost" );

		Network->setConnectionAddress( Address );

		World = new WorldManager( this, Mode );
	}

	Network->grab();
	World->grab();

	getTimer()->start();
//	GUI = new GUIManager( this );
//	Sound = new SoundManager( this );
}

GameManager::~GameManager()
{
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
	EntityList.push_back( new Entity( this, NetID ) );
	EntityList.back()->grab();
}

void GameManager::destroyObject( NETID NetID )
{
	while( Network->getUpdateData( NetID ) );

	for( vector<Entity*>::iterator itr = EntityList.begin();
			itr != EntityList.end(); itr++ )
	{
		if( (*itr)->getNetworkObject()->getNetID() == NetID )
		{
			Entity* temp = *itr;
			EntityList.erase( itr );
			temp->drop();
			return;
		}
	}
}

string GameManager::getDebugInfo() const
{
	return string("GameManager");
}

const vector<Entity*>& GameManager::getEntityList() const
{
	return EntityList;
}

void GameManager::createSceneObject( PhysicsObjectCreationStruct POCS )
{
	EntityList.push_back( new Entity( this, Mode, Network->getNextNETID(), new PhysicsObject(World, POCS) ) );
	EntityList.back()->grab();
}

bool GameManager::loadScene(string filename)
{
	ifstream File (filename.c_str());

	if( !File )
	{
		cerr << "Could not load file " << filename << endl;
		return false;
	}

	File >> ScenarioName;

	string temp;

	while( !File.eof() )
	{
		File >> temp;

		if( temp == "scene_descrip" )
		{
			std::getline( File, ScenarioDescrip );
			File >> temp >> temp;
			continue;
		}
		if( temp == "entity" )
		{
			PhysicsObjectCreationStruct POCS;
			File >> POCS.MeshName >> POCS.CollisionName >> POCS.Mass
					>> POCS.Position[0] >> POCS.Position[1] >> POCS.Position[2]
					>> POCS.Rotation[0] >> POCS.Rotation[1] >> POCS.Rotation[2]
					>> POCS.Scale[0] >> POCS.Scale[1] >> POCS.Scale[2]
					>> POCS.LinearVelocity[0] >> POCS.LinearVelocity[1]
						>> POCS.LinearVelocity[2]
					>> POCS.AngularVelocity[0] >> POCS.AngularVelocity[1]
						>> POCS.AngularVelocity[2]
					>> temp;

			createSceneObject( POCS );
			
			continue;
		}
	}

	return true;
}

irr::ITimer* GameManager::getTimer()
{
	return World->getIrrlichtDriver()->getTimer();
}

void GameManager::endGame()
{
	for( u32 i=0; i<EntityList.size(); i++ )
		EntityList[i]->drop();

	Network->drop();
	World->drop();
}