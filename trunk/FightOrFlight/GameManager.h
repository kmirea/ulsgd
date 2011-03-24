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

class GameManager : public ReferenceCountedObject
{
public:
	GameManager( u32 argc, c8** argv );
	GameManager();

	virtual ~GameManager();

	bool run();

	NetworkManager* getNetworkManager() const;
	WorldManager* getWorldManager() const;
	
	void createObject( NETID NetID );

private:

	NetworkManager* Network;
	WorldManager* World;
	
	vector<Entity*> EntityList;

};

#endif	/* GAMEMANAGER_H */

