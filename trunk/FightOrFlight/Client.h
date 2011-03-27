/* 
 * File:   ClientObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:54 PM
 */

#ifndef CLIENTOBJECT_H
#define	CLIENTOBJECT_H

#include "Entity.h"
#include "NetworkManager.h"

#include <irrlicht/IEventReceiver.h>

class Client : public Entity, public irr::IEventReceiver
{
public:
	Client( GameManager* Game, NETID NetID );

protected:
	virtual ~Client();

public:
	bool OnEvent( const irr::SEvent& Event );

protected:
	virtual string getDebugInfo() const;
};

#endif	/* CLIENTOBJECT_H */

