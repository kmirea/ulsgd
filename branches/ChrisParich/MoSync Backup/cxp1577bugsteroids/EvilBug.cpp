/*
 * EvilBug.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Chris
 */

#include "EvilBug.h"

EvilBug::EvilBug() :
		Bug()
{
	victim = NULL;
}

EvilBug::EvilBug(s32 w, s32 h, s32 initx, s32 inity, f32 initScale, Bug* Victim) :
		Bug(w, h, initx, inity, initScale), victim(Victim)
{

}

void EvilBug::calcDirection()
{
	f32 vx = victim->returnx();
	f32 vy = victim->returny();
	s32 direction = 0;
	if (y == vy)
	{
		if (x > vx)
			direction = 12;
		else
			direction = 4;
	}
	else if (x == vx)
	{
		if (y > vy)
			direction = 8;
		else
			direction = 0;
	}
	else
	{
		f32 slope = (vy - y) / (vx - x);
		if (slope > 0)
		{
			if (slope < .5)
			{
				if (x > vx)
					direction = 12;
				else
					direction = 4;
			}
			else if (slope > 2)
			{
				if (x > vx)
					direction = 0;
				else
					direction = 8;
			}
			else
			{
				if (x > vx)
					direction = 14;
				else
					direction = 6;
			}
		}
		else if (slope < 0)
		{
			if (slope > -.5)
			{
				if (x > vx)
					direction = 12;
				else
					direction = 4;
			}
			else if (slope < -2)
			{
				if (x > vx)
					direction = 8;
				else
					direction = 0;
			}
			else
			{
				if (x > vx)
					direction = 10;
				else
					direction = 2;
			}
		}
	}
	setdirection(direction);
}
