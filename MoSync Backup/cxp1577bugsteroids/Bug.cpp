/*
* Bug.cpp
*
*  Created on: Feb 22, 2012
*      Author: Chris
*/

#include "Bug.h"

f32			Xpto[bugPoints];
f32			Ypto[bugPoints];
s32			Speed = 0;
f32			Scale = 0;
s32			Impactzone = 0;
s32			Width = 0;
s32			Height = 0;

void Bug::init1()
{
	Xpto[0] = 0;
	Xpto[1] = (s32)(-2 * Scale + .5);
	Xpto[2] = (s32)(-5 * Scale + .5);
	Xpto[3] = 0;
	Xpto[4] = (s32)( 2 * Scale - .5);
	Xpto[5] = (s32)( 5 * Scale - .5);

	Ypto[0] = (s32)(-5 * Scale + .5);
	Ypto[1] = (s32)( 5 * Scale - .5);
	Ypto[2] = (s32)( 5 * Scale - .5);
	Ypto[3] = (s32)(-5 * Scale + .5);
	Ypto[4] = (s32)( 5 * Scale - .5);
	Ypto[5] = (s32)( 5 * Scale - .5);
	color = 0xff0000;
	Impactzone = (s32)(8 * Scale);
}

void Bug::init2()
{
	direction = 0;
	for (s32 p=0; p<bugPoints; p++) {
		xpt[p] = Xpto[p];
		ypt[p] = Ypto[p];
	}
	oledirection = direction;
	alive = true;
}

Bug::Bug()
{
	Scale = 1;
	init1();
	Width = 0;
	Height = 0;
	Speed = 1;
	x = 0;
	y = 0;
	rx = 0;
	ry = 0;
	init2();
}


Bug::Bug(s32 w, s32 h, s32 initx, s32 inity, f32 initScale)
{
	Scale = initScale;
	init1();
	Width = w;
	Height = h;
	Speed = 1;
	x = initx;
	y = inity;
	rx = x;
	ry = y;
	init2();
}

s32 Bug::returnx() const
{
	return x;
}

s32 Bug::returny() const
{
	return y;
}

bool Bug::isAlive() const
{
	return alive;
}

bool Bug::impactBug(Bug &p) const
{
	if (p.returnx( )<x+Impactzone & p.returnx( )>x-Impactzone &
		p.returny( )<y+Impactzone & p.returny( )>y-Impactzone) {
		return true;
	} else return false;
}

void Bug::isDead( )
{
	alive = false;
}

void Bug::setBugColor(s32 c)
{
	color = c;
}

s32 Bug::speedUp()
{
	if (Speed < 5)
		Speed++;
}

s32 Bug::slowDown()
{
	if (Speed > 1)
		Speed--;
}

void Bug::setdirection(s32 d)
{
	if (d >=0 & d < MAXDIRECTION)
	{
		direction = d;
		oledirection = -1;
	}
}

void Bug::turnright( )
{
	oledirection = direction;
	direction++;
	if (direction >= MAXDIRECTION)
		direction = 0;
}

void Bug::turnleft( )
{
	oledirection = direction;
	direction--;
	if (direction < 0)
		direction = MAXDIRECTION-1;
}

void Bug::calculateBugParts( )
{
	if (direction > 0)
	{
		f32 rotation = 6.28 * ((f32) direction) / ((f32)MAXDIRECTION);
		f32 c = cos(rotation);
		f32 s = sin(rotation);
		f32 trt[3][3];
		trt[0][0] = c;  trt[0][1] = -s;  trt[0][2] = 0;
		trt[1][0] = s;  trt[1][1] = c;   trt[1][2] = 0;
		trt[2][0] = 0;  trt[2][1] = 0;   trt[2][2] = 1;

		f32 point[3];
		f32 newpoint[3];
		for (s32 p=0; p<bugPoints; p++)
		{
			point[0] = Xpto[p];
			point[1] = Ypto[p];
			point[2] = 1;

			for (s32 i=0; i<3; i++)
			{
				newpoint[i] = 0;
				for (s32 j=0; j<3; j++)
					newpoint[i] += trt[i][j] * point[j];
			}
			xpt[p] = newpoint[0];
			ypt[p] = newpoint[1];
			oledirection = direction;
		}
	}
	else if (direction == 0)
	{
		for (s32 p=0; p<bugPoints; p++)
		{
			xpt[p] = Xpto[p];
			ypt[p] = Ypto[p];
		}
		oledirection = direction;
	}
}

void Bug::paintBug()
{
	if (oledirection != direction)
		calculateBugParts( );
	maSetColor(color);
	paintBugTriangle(
			x+((s32)(xpt[0]+0.5)), y+((s32)(ypt[0]+0.5 )),
			x+((s32)(xpt[1]+0.5)), y+((s32)(ypt[1]+0.5 )),
			x+((s32)(xpt[2]+0.5)), y+((s32)(ypt[2]+0.5))
			);

	paintBugTriangle(
			x+((s32)(xpt[3]+0.5)), y+((s32)(ypt[3]+0.5 )),
			x+((s32)(xpt[4]+0.5)), y+((s32)(ypt[4]+0.5 )),
			x+((s32)(xpt[5]+0.5)), y+((s32)(ypt[5]+0.5))
			);
}

void Bug::paintBugTriangle(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2) const
{
	MAPoint2d points[3];
	points[0].x = x0;
	points[0].y = y0;
	points[1].x = x1;
	points[1].y = y1;
	points[2].x = x2;
	points[2].y = y2;
	maFillTriangleFan(points,3);
}

void Bug::go( )
{
	if (direction > 0)
	{
		f32 cpts[3];
		cpts[0] = 0.0;
		cpts[1] = (f32)Speed;
		cpts[2] = 1.0;

		f32 newpos32s[3];
		f32 rotation = 6.28 * ((f32) direction) / ((f32)MAXDIRECTION);
		f32 c = cos(rotation);
		f32 s = sin(rotation);

		f32 trt[3][3];
		trt[0][0] = c;  trt[0][1] = -s;  trt[0][2] = 0;
		trt[1][0] = s;  trt[1][1] = c;   trt[1][2] = 0;
		trt[2][0] = 0;  trt[2][1] = 0;  trt[2][2] = 1;

		f32 newpos32[3];
		for (s32 i=0; i<3; i++)
		{
			newpos32[i] = 0;
			for (s32 j=0; j<3; j++)
				newpos32[i] += trt[i][j] * cpts[j];
		}

		rx -= newpos32[0];
		ry -= newpos32[1];

	}
	else if (direction == 0)
		ry -= (f32)Speed;

	if ((rx+5) >= ((f32)Width))
		rx = (f32)(Width-5);
	else if (rx < 5)
		rx = 5;
	if ((ry+5) >= ((f32)Height))
		ry = (f32)(Height-5);
	else if (ry < 5)
		ry = 5;

	x = (s32)(rx+0.5);
	y = (s32)(ry+0.5);
}
