/* 
 * File:   ClientObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:54 PM
 */

#ifndef CLIENTOBJECT_H
#define	CLIENTOBJECT_H

#include "DynamicObject.h"
#include "NetworkManager.h"


class ClientObject : public Entity
{
public:
	ClientObject( GameManager* Game, NETID NetID );
};

#endif	/* CLIENTOBJECT_H */

