/* 
 * File:   Room.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:04 PM
 */

#ifndef ROOM_H
#define	ROOM_H

#include "Types.h"

namespace irr
{
namespace scene
{
class ISceneNode;
}
}

class World;

class Room
{
	irr::scene::ISceneNode* RoomRoot;
	
public:
	Room(World* world);
	
	void getExistList( vector<u32>& RoomIdList ) const;
	irr::scene::ISceneNode* getRoomRoot() const;
};

#endif	/* ROOM_H */

