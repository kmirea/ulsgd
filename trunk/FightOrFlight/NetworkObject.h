/* 
 * File:   NetworkObject.h
 * Author: chris
 *
 * Created on March 18, 2011, 9:12 AM
 */

#ifndef NETWORKOBJECT_H
#define	NETWORKOBJECT_H

#include "ReferenceCountedObject.h"
#include "NetProtocolStruct.h"

class NetworkManager;

class NetworkObject : public ReferenceCountedObject
{
public:
	NetworkObject( NetworkManager* Net, NETID NetID );

protected:
	virtual ~NetworkObject();

	virtual string getDebugInfo() const;

public:
	// Return this object's net id
	NETID getNetID() const;

	// Check to see if any data is pending
	bool isMessageAvailable() const;

	// Make sure to drop this NetData once you are finished with it...
	NetData* getOutStream();
	// Used to provide network data to child classes
	NetData* getInStream();
	
	virtual void update();
	
protected:
	// Used to allow child classes to send network updates
	void sendData( NetData* );
	
private:	
	NetworkManager* Manager;

	const NETID net_id;

	NetData* OutStream;
	NetData* InStream;
	
	bool MessageAvailable;
};

#endif	/* NETWORKOBJECT_H */

