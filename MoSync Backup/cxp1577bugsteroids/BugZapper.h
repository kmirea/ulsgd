/*
 * BugZapper.h
 *
 *  Created on: Feb 22, 2012
 *      Author: Chris
 */

#ifndef BUGZAPPER_H_
#define BUGZAPPER_H_

#include "Bug.h"

class BugZapper
{
private:
	int x, y, scale;

public:
	BugZapper();
	BugZapper( s32 X, s32 Y, s32 Scale );

	void paintZapperTriangle(int x0, int y0, int x1, int y1, int x2, int y2) const;
	void paintBugZapper() const;

	bool impactBug(Bug p) const;
};


#endif /* BUGZAPPER_H_ */
