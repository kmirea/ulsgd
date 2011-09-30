#include "SceneLoader.h"

SceneLoader::SceneLoader( string filename ) : ReferenceCountedObject(), SpawnPointIndex(0), SceneName(""), SceneDisc("")
{
	ifstream file ( filename.c_str() );
	
	if( !file )
		goto file_error;
	
	while( !file.eof() )
	{
		string temp;
		file >> temp;
		
		if( temp == "<SceneName>" )
		{
			if( SceneName != "" )
				goto file_error;
			getline( temp, file ); getline( SceneName, file );
			file >> temp;
			if( temp != "</SceneName>" )
				goto file_error;
		}
		else if( temp == "<SceneDisc>" )
		{
			if( SceneDisc != "" )
				goto file_error;
			getline( temp, file ); getline( SceneDisc, file );
			file >> temp;
			if( temp != "</SceneDisc>" )
				goto file_error;
		}
		else if( temp == "<Entity>" )
		{
			// TODO: Take care of filling out entity creation data
			file >> temp;
			if( temp != "</Entity>" )
				goto file_error;
		}
		// TODO: Take care of SpawnPoint loading...
	}
	
	return;
	file_error:
	{
		cerr << "Scene Loading error, exiting..." << endl;
		exit(EXIT_FAILURE);
	}
}

SceneLoader::~SceneLoader()
{
	
}

string SceneLoader::getDebugInfo()
{
	
}

const SpawnPoint& SceneLoader::getNextSpawnPoint()
{
	u32 temp = SpawnPointIndex;
	if( SpawnPointIndex >= SpawnPointList.size() )
		SpawnPointIndex++;
	return SpawnPointList[temp];
}

const PhysicsObjectCreationStruct& SceneLoader::getNextPOCS()
{
	
}

bool SceneLoader::getIsPOCSListEmpty() const
{
	return (POCSList.size() > 0);
}
