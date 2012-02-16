/*
 * Moblet.h
 *
 *  Created on: Feb 16, 2012
 *      Author: cmps359
 */

#ifndef MOBLET_H_
#define MOBLET_H_

#include <MAUtil/Moblet.h>
#include <conprint.h>
#include "Types.h"

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class Game : public Moblet, public IdleListener
{
	f32 scale;
	u32 lasttime;
public:
	/**
	 * Initialize the application in the constructor.
	 */
	Game();

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode);

	/**
	 * Called when a key is released.
	 */
	void keyReleaseEvent(int keyCode, int nativeCode);

	/**
	 * Called when the screen is touched.
	 */
	void pointerPressEvent(MAPoint2d point);

	u32 getScreenX() const;

	u32 getScreenY() const;

	void idle();
};



#endif /* MOBLET_H_ */
