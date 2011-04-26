/* 
 * File:   PhysicsObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:44 PM
 */

#ifndef PHYSICSOBJECT_H
#define	PHYSICSOBJECT_H

#include "ReferenceCountedObject.h"
#include <irrlicht/irrlicht.h>
#include <irrBullet/irrbullet.h>

class WorldManager;
class NetData;

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
	PhysicsObject( WorldManager* World, const PhysicsObjectCreationStruct& POCS );
protected:
	virtual ~PhysicsObject();

public:
	void update( NetData* InStream = NULL );

	const PhysicsObjectCreationStruct& getLocalData();

	irr::scene::ISceneNode* getDrawMesh() const;
	IRigidBody* getBody() const;
	IGImpactMeshShape* getCollisionMesh() const;
	
protected:
	virtual string getDebugInfo() const;
	
private:
	WorldManager* World;
	PhysicsObjectCreationStruct LocalData;

	irr::scene::ISceneNode* DrawMesh;
	IRigidBody* Body;
	IGImpactMeshShape* CollMesh;
	
	bool gotLocalData;
};

#endif	/* PHYSICSOBJECT_H */

