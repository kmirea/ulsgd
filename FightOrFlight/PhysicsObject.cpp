#include "PhysicsObject.h"
#include "WorldManager.h"

PhysicsObject::PhysicsObject(WorldManager* world, PhysicsObjectCreationStruct& POCS) : ReferenceCountedObject(),
		World(world), LocalData(POCS), Mesh(NULL), Coll(NULL), CollMesh(NULL)
{
	cout << getDebugInfo() << endl;

	irr::scene::IMesh* mesh = World->getIrrlichtDriver()->getSceneManager()->getMesh((string("media/models/")+LocalData.MeshName+string(".obj")).c_str());
	irr::scene::IMesh* collmesh = World->getIrrlichtDriver()->getSceneManager()->getMesh((string("media/models/")+LocalData.CollisionName+string("_coll.obj")).c_str());
	irr::video::ITexture* tex = World->getIrrlichtDriver()->getVideoDriver()->addTexture( (string("media/textures/")+LocalData.MeshName+string(".png")).c_str(),
										 World->getIrrlichtDriver()->getVideoDriver()->createImageFromFile((string("media/textures/")+LocalData.MeshName+string(".png")).c_str()) );
	irr::core::vector3df position (LocalData.Position[0],LocalData.Position[1],LocalData.Position[2]);
	irr::core::vector3df rotation (LocalData.Rotation[0],LocalData.Rotation[1],LocalData.Rotation[2]);
	irr::core::vector3df scale (LocalData.Scale[0],LocalData.Scale[1],LocalData.Scale[2]);
	irr::core::vector3df linvel (LocalData.LinearVelocity[0],LocalData.LinearVelocity[1],LocalData.LinearVelocity[2]);
	irr::core::vector3df angvel (LocalData.AngularVelocity[0],LocalData.AngularVelocity[1],LocalData.AngularVelocity[2]);

	Mesh = World->getIrrlichtDriver()->getSceneManager()->addMeshSceneNode(mesh, NULL, 0, position, rotation, scale, true);
	Mesh->setMaterialTexture(0,tex);
	Mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	CollMesh = new IGImpactMeshShape(Mesh,collmesh,LocalData.Mass);
	Coll = World->getIrrBulletDriver()->addRigidBody(CollMesh);

	Coll->setLinearVelocity(linvel);
	Coll->setAngularVelocity(angvel);
}

PhysicsObject::~PhysicsObject()
{
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
