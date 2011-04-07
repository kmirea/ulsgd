#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(WorldManager* world, PhysicsObjectCreationStruct& POCS) : ReferenceCountedObject(),
		World(world), LocalData(POCS)
{
	cout << getDebugInfo() << endl;
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

const PhysicsObjectCreationStruct& PhysicsObject::getLocalData() const
{
	return LocalData;
}
