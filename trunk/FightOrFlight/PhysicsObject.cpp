#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(WorldManager* world) : ReferenceCountedObject(),
		World(world)
{
	
}

PhysicsObject::~PhysicsObject()
{

}

string PhysicsObject::getDebugInfo() const
{
	return string("PhyscisObject");
}