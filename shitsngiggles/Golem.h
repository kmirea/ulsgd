/* 
 * File:   Golem.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:06 PM
 */

#ifndef GOLEM_H
#define	GOLEM_H

#include "Elemental.h"

enum DIRECTION
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Golem : public Elemental
{
public:
	Golem( Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element );
	virtual ~Golem();
	
	bool move( DIRECTION Direction );
	virtual bool shoot( DIRECTION Direction );

    bool isDead(); //checks to see if the golem is dead

    virtual void prepass(const u32 GameTime); //clear state
    virtual void pass(const u32 GameTime); // decision
    virtual void postpass(const u32 GameTime); // action

	void handleCollision(Object& Other); // handles collision
protected:
	vector<u32> NextPosition;
	vector<u32> NextVelocity;

	bool isMoving;
};

#endif	/* GOLEM_H */

