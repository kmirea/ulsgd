/*
 * EvilBug.h
 *
 *  Created on: Feb 22, 2012
 *      Author: Chris
 */

#ifndef EVILBUG_H_
#define EVILBUG_H_

#include "Bug.h"

class EvilBug : public Bug
{
private:
	Bug* victim;

public:
	EvilBug();

	EvilBug( s32 w, s32 h, s32 initx, s32 inity, f32 initScale, Bug* Victim );

	void calcDirection();
};

#endif /* EVILBUG_H_ */
