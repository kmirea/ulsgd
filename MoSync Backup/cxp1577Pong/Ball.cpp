/*
 * Ball.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: cmps359
 */

#include "Ball.h"
#include "Pong.h"
#include <conprint.h>

Ball::Ball(Pong* Game, s32 X, s32 Y, s32 VelX, s32 VelY ) : x(X), y(Y), velX(VelX), velY(VelY), game(Game), multiplyer(1)
{
	image = BALL_IMG;
}

Ball::~Ball()
{

}

void Ball::setPosition( s32 X, s32 Y )
{
	x = X;
	y = Y;
}

void Ball::getPosition( s32& X, s32& Y ) const
{
	X = x;
	Y = y;
}

void Ball::setVelocity( s32 VelX, s32 VelY )
{
	velX = VelX;
	velY = VelY;
}

void Ball::getVelocity( s32& VelX, s32& VelY ) const
{
	VelX = velX;
	VelY = velY;
}

void Ball::setVelMultiplyer( u32 Multiplyer )
{
	multiplyer = Multiplyer;
}

u32 Ball::getVelMultiplyer() const
{
	return multiplyer;
}

void Ball::draw()
{
	x+=velX*multiplyer;
	y+=velY*multiplyer;

	MARect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 40;
	rect.height = 40;

	MAPoint2d point;
	point.x = x-rect.width/2;
	point.y = y-rect.height/2;

	if( point.x <= 0 || point.x + 40 >= game->getScreenX() )
		setVelocity(-velX, velY);

	Gfx_drawImageRegion(image, &rect, &point, TRANS_NONE);
}
