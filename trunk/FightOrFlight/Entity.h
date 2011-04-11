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
#include "NetworkManager.h"

class GameManager;

class Entity : public ReferenceCountedObject
{
public:
	Entity( GameManager* Game, E_MANAGER_MODE Mode, NETID NetID );
	Entity( GameManager* Game, E_MANAGER_MODE Mode, NETID NetID, PhysicsObject* Physics );

protected:
	~Entity();

public:
	NetworkObject* getNetworkObject() const;
	PhysicsObject* getPhysicsObject() const;

	virtual void update();

	virtual void syncCreate() const;
	
protected:
	virtual string getDebugInfo() const;

private:
	NetworkObject* Network;
	PhysicsObject* Physics;

	GameManager* Game;
	E_MANAGER_MODE Mode;

	u32 time_for_next_update;
};

#endif	/* ENTITY_H */

