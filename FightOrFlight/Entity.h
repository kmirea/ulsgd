/* 
 * File:   DynamicObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:45 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include "NetworkObject.h"
#include "PhysicsObject.h"

class GameManager;

class Entity : public ReferenceCountedObject
{
public:
	Entity( GameManager* Game, NETID NetID );

protected:
	~Entity();

public:
	NetworkObject* getNetworkObject() const;
	PhysicsObject* getPhysicsObject() const;

	virtual void update();

protected:
	virtual string getDebugInfo() const;

private:
	NetworkObject* Network;
	PhysicsObject* Physics;

	GameManager* Game;
};

#endif	/* ENTITY_H */

