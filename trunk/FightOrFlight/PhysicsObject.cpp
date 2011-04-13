#include "PhysicsObject.h"
#include "WorldManager.h"

PhysicsObject::PhysicsObject(WorldManager* world, const PhysicsObjectCreationStruct& POCS) : ReferenceCountedObject(),
		World(world), LocalData(POCS), DrawMesh(NULL), Body(NULL), CollMesh(NULL)
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

	DrawMesh = World->getIrrlichtDriver()->getSceneManager()->addMeshSceneNode(mesh, NULL, 0, position, rotation, scale, true);
	DrawMesh->setMaterialTexture(0,tex);
	DrawMesh->setMaterialFlag( irr::video::EMF_NORMALIZE_NORMALS, true );
//	DrawMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	CollMesh = new IGImpactMeshShape(DrawMesh,collmesh,LocalData.Mass);
	Body = World->getIrrBulletDriver()->addRigidBody(CollMesh);

	Body->setLinearVelocity(linvel);
	Body->setAngularVelocity(angvel);

	Body->setActivationState( EAS_DISABLE_DEACTIVATION );
}

PhysicsObject::~PhysicsObject()
{
	World->getIrrBulletDriver()->removeCollisionObject( Body, true );
}

string PhysicsObject::getDebugInfo() const
{
	return string("PhyscisObject");
}

void PhysicsObject::update( NetData* InStream )
{
	if( InStream != NULL )
	{
		irr::core::vector3df pos (InStream->Sync.Position[0], InStream->Sync.Position[1], InStream->Sync.Position[2]);
		irr::core::vector3df rot (InStream->Sync.Rotation[0], InStream->Sync.Rotation[1], InStream->Sync.Rotation[2]);
		irr::core::vector3df linvel (InStream->Sync.LinearVelocity[0], InStream->Sync.LinearVelocity[1], InStream->Sync.LinearVelocity[2]);
		irr::core::vector3df angvel (InStream->Sync.AngularVelocity[0], InStream->Sync.AngularVelocity[1], InStream->Sync.AngularVelocity[2]);

		DrawMesh->setPosition( pos );
		DrawMesh->setRotation( rot );
		Body->setLinearVelocity( linvel );
		Body->setAngularVelocity( angvel );
	}

	Body->updateObject();
	DrawMesh->updateAbsolutePosition();

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
}

const PhysicsObjectCreationStruct& PhysicsObject::getLocalData() const
{
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
