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
			Network = new NetworkManager( this, EMM_SERVER );
			World = new WorldManager( this, EMM_SERVER );

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
	PhysicsObjectCreationStruct POCS;

	NetData* data = Network->getUpdateData( NetID );
	data->grab();

	assert( data->MsgType == ENMT_CREATE );

	POCS.MeshName = data->Create.Meshname;
	POCS.CollisionName = POCS.MeshName + string("_col");
	POCS.Mass = data->Create.Mass;
	for( u32 i=0; i<3; i++ )
	{
		POCS.Position[i] = data->Create.Position[i];
		POCS.Rotation[i] = data->Create.Rotation[i];
		POCS.Scale[i] = data->Create.Scale[i];
		POCS.LinearVelocity[i] = data->Create.LinearVelocity[i];
		POCS.AngularVelocity[i] = data->Create.AngularVelocity[i];
	}

	data->drop();

	EntityList.push_back( new Entity( this, NetID, new PhysicsObject( World, &POCS ) ) );
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
	EntityList.push_back( new Entity( this, Network->getNextNETID(), new PhysicsObject(World, &POCS) ) );
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
