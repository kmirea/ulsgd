/* 
 * File:   NetworkManager.h
 * Author: chris
 *
 * Created on March 18, 2011, 10:28 AM
 */

#ifndef NETWORKMANAGER_H
#define	NETWORKMANAGER_H

#include "ReferenceCountedObject.h"
#include "NetworkObject.h"

class GameManager;

enum E_MANAGER_MODE
{
	EMM_CLIENT,
	EMM_SERVER
};

class NetworkManager : public ReferenceCountedObject
{
public:
	NetworkManager( GameManager* Game, E_MANAGER_MODE Mode );

protected:
	~NetworkManager();

	virtual string getDebugInfo();

public:
	void update();

	deque<u8> getUpdateData( NETID NetObject );

private:
	GameManager* Game;
	const E_MANAGER_MODE Mode;

	map< NETID, queue<NetData*> > MessageList;
};

#endif	/* NETWORKMANAGER_H */

