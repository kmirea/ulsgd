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

	virtual string getDebugInfo();

public:
	// Return this object's net id
	NETID getNetID() const;

	// Check to see if any data is pending
	bool isMessageAvailable() const;


	deque<u8> getOutStream();
	
	virtual void update();
	
protected:
	// Used to provide network data to child classes
	const deque<u8>& getInStream();

	// Used to allow child classes to send network updates
	void sendData( const deque<u8>& OutData );
	
private:	
	NetworkManager* Manager;

	const NETID net_id;

	deque<u8> InStream;
	deque<u8> OutStream;

	bool MessageAvailable;
};

#endif	/* NETWORKOBJECT_H */

