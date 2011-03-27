#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(WorldManager* world, PhysicsObjectCreationStruct* POCS) : ReferenceCountedObject(),
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