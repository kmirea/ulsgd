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
	NetworkObject( const NetworkManager* Net );
	NetworkObject( const NetworkObject& Other );

protected:
	virtual ~NetworkObject();

public:
	NETID getNetID() const;
	bool isMessageAvailable() const;

	const vector<u8>& getOutStream();
	void update();

protected:
	const vector<u8>& getInStream();

	void sendData( const vector<u8>& OutData );
	
private:
	friend class NetworkManager;
	
	const NetworkManager* Manager;

	const NETID net_id;

	vector<u8> InStream;
	vector<u8> OutStream;

	bool MessageAvailable;
};

#endif	/* NETWORKOBJECT_H */

