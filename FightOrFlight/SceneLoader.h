/* 
 * File:   SceneLoader.h
 * Author: chris
 *
 * Created on July 2, 2011, 4:21 AM
 */

#ifndef SCENELOADER_H
#define	SCENELOADER_H

#include "Types.h"
#include "ReferenceCountedObject.h"
#include "PhysicsObject.h"

struct SpawnPoint
{
	f32 Position[3];
	f32 Rotation[3];
};

class SceneLoader : public ReferenceCountedObject
{
	u32 SpawnPointIndex;
	
	vector<SpawnPoint> SpawnPointList;
	vector<PhysicsObjectCreationStruct> POCSList;
	
	string SceneName;
	string SceneDisc;
	
public:
	SceneLoader( string filename );
	
protected:
	virtual ~SceneLoader();
	virtual string getDebugInfo();
	
public:
	const SpawnPoint& getNextSpawnPoint();
	const PhysicsObjectCreationStruct& getNextPOCS();
	
	bool getIsPOCSListEmpty() const;
	
	const string& getSceneName() const;
	const string& getSceneDisc() const;
};

#endif	/* SCENELOADER_H */

