/* 
 * File:   GameManager.h
 * Author: chris
 *
 * Created on March 21, 2011, 7:06 PM
 */

#ifndef GAMEMANAGER_H
#define	GAMEMANAGER_H

#include "NetworkManager.h"
#include "WorldManager.h"
#include "GUIManager.h"
#include "Entity.h"
#include "SoundManager.h"

class GameManager : public ReferenceCountedObject
{
public:
	GameManager( u32 argc, c8** argv );

protected:
	virtual ~GameManager();

public:
	bool run();

	NetworkManager* getNetworkManager() const;
	WorldManager* getWorldManager() const;
	GUIManager* getGUIManager() const;
	SoundManager* getSoundManager() const;
	Client* getClientObject() const;
	
	void createObject( NETID NetID );
	void createSceneObject( PhysicsObjectCreationStruct POCS );
	void createClientObject( NETID NetID );
	void destroyObject( NETID NetID );

	const vector<Entity*>& getEntityList() const;
	const PhysicsObjectCreationStruct& getClientPOCS() const;
	irr::ITimer* getTimer();

	void endGame();

protected:
	bool loadScene( string filename );
	
	virtual string getDebugInfo() const;
	
private:

	E_MANAGER_MODE Mode;
	NetworkManager* Network;
	WorldManager* World;
	GUIManager* GUI;
	SoundManager* Sound;
	
	vector<Entity*> EntityList;
	Client* ClientEntity;

	string ScenarioName;
	string ScenarioDescrip;

	PhysicsObjectCreationStruct ClientCreationStruct;
};

#endif	/* GAMEMANAGER_H */

