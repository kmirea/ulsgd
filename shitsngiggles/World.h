/* 
 * File:   World.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:04 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include "Types.h"

#include "IrrObjectNode.h"

class Room;
class InputUser;

class World
{
	Room* CurrentRoom;

	vector<Room*> OffloadedRoomList;

	vector<InputUser*> InputUserList;

	irr::IrrlichtDevice* IrrDevice;

public:
	World();
	~World();

	bool run();

	void RegisterInputUser(InputUser* User);
	irr::IrrlichtDevice* getIrrDevice() const;
};

#endif	/* WORLD_H */

