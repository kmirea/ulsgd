/*
 * BugZapper.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Chris
 */

#include "BugZapper.h"

BugZapper::BugZapper() { }

BugZapper::BugZapper(s32 X, s32 Y, s32 Scale) :
		x(X), y(Y), scale(Scale)
{

}

void BugZapper::paintZapperTriangle(int x0, int y0, int x1, int y1, int x2,
		int y2) const
{
	MAPoint2d points[3];
	points[0].x = x0;
	points[0].y = y0;
	points[1].x = x1;
	points[1].y = y1;
	points[2].x = x2;
	points[2].y = y2;
	maFillTriangleFan(points, 3);
}

void BugZapper::paintBugZapper() const
{
	maSetColor(0x88AA55);
	paintZapperTriangle(x, y, x, y + scale / 2, x + scale / 2, y);
	paintZapperTriangle(x, y, x, y - scale / 2, x - scale / 2, y);
	maSetColor(0x887755);
	paintZapperTriangle(x, y, x + scale / 2, y, x, y - scale / 2);
	paintZapperTriangle(x, y, x - scale / 2, y, x, y + scale / 2);
}

bool BugZapper::impactBug(Bug p) const
{
	int halfscale = scale / 2;
	if (p.returnx() > x - halfscale && p.returnx() < x + halfscale
			&& p.returny() > y - halfscale && p.returny() < y + halfscale)
		return true;
	else
		return false;
}
