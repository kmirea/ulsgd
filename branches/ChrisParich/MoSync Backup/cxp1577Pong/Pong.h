/*
 * Pong.h
 *
 *  Created on: Feb 5, 2012
 *      Author: cmps359
 */

#ifndef PONG_H_
#define PONG_H_

#include "Types.h"
#include "Paddle.h"
#include "Ball.h"
#include "MAHeaders.h"

#include <MAUtil/Moblet.h>
#include <conprint.h>

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class Pong : public Moblet, TimerListener
{
	Paddle* p1;
	Paddle* p2;
	u32 p1score, p2score;
	Ball* ball;
public:
	Pong();
	~Pong();

	void keyPressEvent(int keyCode, int nativeCode);
	void keyReleaseEvent( int keyCode, int nativeCode );

	void multitouchPressEvent(MAPoint2d point, int touchId);
	void multitouchReleaseEvent(MAPoint2d point, int touchId);

	void runTimerEvent();

	u32 getScreenX() const;
	u32 getScreenY() const;

	void draw();

	bool hitPaddle() const;
};
#endif /* PONG_H_ */
