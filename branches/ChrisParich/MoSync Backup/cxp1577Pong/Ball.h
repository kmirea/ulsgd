/*
 * Ball.h
 *
 *  Created on: Feb 5, 2012
 *      Author: cmps359
 */

#ifndef BALL_H_
#define BALL_H_

#include "Types.h"
#include "MAHeaders.h"

#include <MAUtil/Graphics.h>

class Pong;

class Ball
{
	s32 x, y;
	s32 velX, velY;
	u32 multiplyer;

	MAHandle image;

	Pong* game;

public:
	Ball(Pong* Game, s32 X, s32 Y, s32 VelX, s32 VelY );
	~Ball();

	void setPosition( s32 X, s32 Y );
	void getPosition( s32& X, s32& Y ) const;

	void setVelocity( s32 VelX, s32 VelY );
	void getVelocity( s32& VelX, s32& VelY ) const;

	void setVelMultiplyer( u32 Multiplyer );
	u32 getVelMultiplyer() const;

	void draw();
};

#endif /* BALL_H_ */
