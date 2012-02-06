/*
 * Paddle.h
 *
 *  Created on: Feb 5, 2012
 *      Author: cmps359
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#include "Types.h"
#include "MAHeaders.h"

#include <MAUtil/Graphics.h>

enum E_SIDE
{
	top,
	bottom
};

class Pong;

class Paddle
{
	s32 vel;
	u32 pos;
	E_SIDE side;

	MAHandle image;

	Pong* game;
public:
	Paddle(Pong* Game, E_SIDE Side, u32 Pos);
	~Paddle();

	void setVelocity( s32 Vel );
	u32 getPosition() const;

	void draw();
};


#endif /* PADDLE_H_ */
