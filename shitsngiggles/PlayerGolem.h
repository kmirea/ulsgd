/* 
 * File:   PlayerGolem.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:06 PM
 */

#ifndef PLAYERGOLEM_H
#define	PLAYERGOLEM_H

#include "Golem.h"

class PlayerGolem : public Golem
{
public:
	PlayerGolem( Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element );

	~PlayerGolem();
	
	void pass( const u32 GameTime );

	bool shoot(DIRECTION Direction);
};

#endif	/* PLAYERGOLEM_H */

