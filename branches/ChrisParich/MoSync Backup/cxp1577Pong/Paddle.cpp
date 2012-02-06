/*
 * Paddle.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: cmps359
 */

#include "Paddle.h"
#include "Pong.h"

Paddle::Paddle(Pong* Game, E_SIDE Side, u32 Position ) : side(Side), pos(Position), game(Game)
{
	image = PADDLE_IMG;
}

Paddle::~Paddle()
{

}

u32 Paddle::getPosition() const
{
	return pos;
}

void Paddle::setVelocity(s32 Vel)
{
	vel = Vel;
}

void Paddle::draw()
{
	MARect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 180;
	rect.height = 40;

	if( (pos+rect.width/2 >= game->getScreenX() && vel > 0) || (pos-rect.width/2 <= 0 && vel < 0) )
			vel = 0;

	pos+=vel;

	MAPoint2d point;
	point.x = pos - rect.width/2;
	switch(side)
	{
	case top:
		point.y = 10;
		break;
	case bottom:
		point.y = game->getScreenY() - 50;
	}

	Gfx_drawImageRegion(image, &rect, &point, TRANS_NONE);
}
