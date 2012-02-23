/*
 * Bug.h
 *
 *  Created on: Feb 16, 2012
 *      Author: cmps359
 */

#ifndef BUG_H_
#define BUG_H_

#include <madmath.h>
#include <mastdlib.h>
#include "Types.h"

const s32 	bugPoints = 6;
const s32 	MAXDIRECTION = 16;

class Bug
{
protected:
	f32		xpt[bugPoints];
	f32		ypt[bugPoints];
	s32		x,	y;
	f32		rx,	ry;
	s32		direction;
	s32		oledirection;
	s32		color;
	bool	alive;

private:
	void init1();

    void init2();

public:

    Bug();


	Bug(s32 w, s32 h, s32 initx, s32 inity, f32 initScale);

	s32 returnx() const;

	s32 returny() const;

	bool isAlive() const;

	bool impactBug(Bug &p) const;

	void isDead( );

	void setBugColor(s32 c);

	s32 speedUp();

	s32 slowDown();

	void setdirection(s32 d);

	void turnright( );

	void turnleft( );

	void calculateBugParts( );

	void paintBug();

	void paintBugTriangle(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2) const;

	void go( );

};


#endif /* BUG_H_ */
