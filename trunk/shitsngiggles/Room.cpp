#include "World.h"

#include "Room.h"

#include "IrrObjectNode.h"

irr::scene::ISceneNode* Room::getRoomRoot() const
{
	return RoomRoot;
}

Room::Room( World* world )
{
	RoomRoot = world->getIrrDevice()->getSceneManager()->addEmptySceneNode();
}