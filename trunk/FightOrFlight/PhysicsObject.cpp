#include "PhysicsObject.h"
#include "WorldManager.h"

PhysicsObject::PhysicsObject(WorldManager* world, const PhysicsObjectCreationStruct& POCS) : ReferenceCountedObject(),
		World(world), LocalData(POCS), DrawMesh(NULL), Body(NULL), CollMesh(NULL), gotLocalData(false)
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

	DrawMesh = World->getIrrlichtDriver()->getSceneManager()->addMeshSceneNode(mesh, NULL, 0, position, rotation, irr::core::vector3df(1,1,1), true);
	DrawMesh->setMaterialTexture(0,tex);
	DrawMesh->setMaterialFlag( irr::video::EMF_NORMALIZE_NORMALS, true );
	CollMesh = new IGImpactMeshShape(DrawMesh,collmesh,LocalData.Mass);
	CollMesh->setLocalScaling( scale, ESP_BOTH );
	Body = World->getIrrBulletDriver()->addRigidBody(CollMesh);

	Body->setActivationState( EAS_ACTIVE );
	Body->setSleepingThresholds( 0.0001f, 0.0001f );
	Body->setContactProcessingThreshold( collmesh->getBoundingBox().getExtent().getLength() * 2 );
	
	Body->setLinearVelocity(linvel);
	Body->setAngularVelocity(angvel);
	
	Body->setActivationState( EAS_WANTS_DEACTIVATION );
}

PhysicsObject::~PhysicsObject()
{
	World->getIrrBulletDriver()->removeCollisionObject( Body, true );
}

string PhysicsObject::getDebugInfo() const
{
	return string("PhyscisObject");
}

void PhysicsObject::update()
{
	Body->updateObject();
	DrawMesh->updateAbsolutePosition();
	
	gotLocalData = false;
}

const PhysicsObjectCreationStruct& PhysicsObject::getLocalData()
{
	if( !gotLocalData )
	{
		LocalData.Position[0] = DrawMesh->getPosition().X;
		LocalData.Position[1] = DrawMesh->getPosition().Y;
		LocalData.Position[2] = DrawMesh->getPosition().Z;

		LocalData.Rotation[0] = DrawMesh->getRotation().X;
		LocalData.Rotation[1] = DrawMesh->getRotation().Y;
		LocalData.Rotation[2] = DrawMesh->getRotation().Z;

		LocalData.LinearVelocity[0] = Body->getLinearVelocity().X;
		LocalData.LinearVelocity[1] = Body->getLinearVelocity().Y;
		LocalData.LinearVelocity[2] = Body->getLinearVelocity().Z;

		LocalData.AngularVelocity[0] = Body->getAngularVelocity().X;
		LocalData.AngularVelocity[1] = Body->getAngularVelocity().Y;
		LocalData.AngularVelocity[2] = Body->getAngularVelocity().Z;
		
		gotLocalData = true;
	}
	
	return LocalData;
}

irr::scene::ISceneNode* PhysicsObject::getDrawMesh() const
{
	return DrawMesh;
}

IRigidBody* PhysicsObject::getBody() const
{
	return Body;
}

IGImpactMeshShape* PhysicsObject::getCollisionMesh() const
{
	return CollMesh;
}
