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

// used to allow forward decleration of enet typedefs
class _ENetAddress;
class _ENetHost;
class _ENetPeer;

typedef _ENetAddress ENetAddress;
typedef _ENetHost ENetHost;
typedef _ENetPeer ENetPeer;

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

	virtual string getDebugInfo() const;

public:
	bool run();
	
	void update();
	void sendLocalData();

	bool setConnectionAddress( ENetAddress& Address );

	NetData* getUpdateData( NETID NetObject );

	NETID getNextNETID();

private:
	GameManager* Game;
	const E_MANAGER_MODE Mode;

	deque<u8> IncomingData;

	ENetHost* netinterface;
	ENetAddress* server_name;

	NETID next_id_counter;
	
	map< NETID, queue<NetData*> > MessageList;
	vector<ENetPeer*> PeerList;

	bool isConnected;
	bool FirstConnect;
};

#endif	/* NETWORKMANAGER_H */

