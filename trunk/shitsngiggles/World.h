/* 
 * File:   World.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:04 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include "Types.h"

class Room;
class InputUser;

class World
{
	Room* CurrentRoom;

	vector<Room*> OffloadedRoomList;

	vector<InputUser*> InputUserList;

        void RegisterInputUser(InputUser*);

public:

};

#endif	/* WORLD_H */

