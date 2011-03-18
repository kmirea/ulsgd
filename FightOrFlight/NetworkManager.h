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

class NetworkManager : public ReferenceCountedObject
{
public:
	NetworkManager( const GameManager* Game );

protected:
	~NetworkManager();

public:
	NETID getNetID();
	void update();

	vector<u8> getUpdateData( NETID NetObject );
};

#endif	/* NETWORKMANAGER_H */

