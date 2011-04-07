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

struct PhysicsObjectCreationStruct
{
	string MeshName;
	string CollisionName;
	f32 Mass;
	f32 Position [3];
	f32 Rotation [3];
	f32 Scale	 [3];
	f32 LinearVelocity [3];
	f32 AngularVelocity[3];
};

class PhysicsObject : public ReferenceCountedObject
{
public:
	PhysicsObject( WorldManager* World, PhysicsObjectCreationStruct& POCS );
protected:
	virtual ~PhysicsObject();

public:
	void update();
	const PhysicsObjectCreationStruct& getLocalData() const;
	
protected:
	virtual string getDebugInfo() const;
	
private:
	WorldManager* World;
	PhysicsObjectCreationStruct LocalData;
};

#endif	/* PHYSICSOBJECT_H */

