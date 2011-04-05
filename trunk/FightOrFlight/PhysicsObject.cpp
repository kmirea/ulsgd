#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(WorldManager* world, PhysicsObjectCreationStruct* POCS) : ReferenceCountedObject(),
		World(world)
{
	// TODO
}

PhysicsObject::~PhysicsObject()
{
	// TODO
}

string PhysicsObject::getDebugInfo() const
{
	return string("PhyscisObject");
}

void PhysicsObject::update()
{
	// TODO
}
