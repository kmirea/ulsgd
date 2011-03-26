/* 
 * File:   PhysicsObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:44 PM
 */

#ifndef PHYSICSOBJECT_H
#define	PHYSICSOBJECT_H

#include "ReferenceCountedObject.h"

class WorldManager;

class PhysicsObject : public ReferenceCountedObject
{
public:
	PhysicsObject( WorldManager* World );
protected:
	virtual ~PhysicsObject();

public:
protected:
	virtual string getDebugInfo() const;
	
private:
	WorldManager* World;
};

#endif	/* PHYSICSOBJECT_H */

