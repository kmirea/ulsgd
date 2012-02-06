/*
* Pong.cpp
*
*  Created on: Feb 5, 2012
*      Author: cmps359
*/

#include "Pong.h"
#include "maprofile.h"
#include <maxtoa.h>

Pong::Pong() : 	p1( new Paddle(this, top, getScreenX()/2) ), p2(new Paddle(this, bottom, getScreenX()/2) ),
				ball( new Ball(this, getScreenX()/2, getScreenY()/2, 2, 2) )
{
	p1score = 0;
	p2score = 0;
	addTimer(this, 50, 0);
}

Pong::~Pong()
{
	delete p1;
	delete p2;
	delete ball;
}

/**
 * Called when a key is pressed.
 */
void Pong::keyPressEvent(int keyCode, int nativeCode)
{
	switch( keyCode )
	{
	case MAK_BACK:
	case MAK_0:
		close();
		return;
	case MAK_RIGHT:
		p1->setVelocity(10);
		break;
	case MAK_LEFT:
		p1->setVelocity(-10);
		break;
	case MAK_D:
		p2->setVelocity(10);
		break;
	case MAK_A:
		p2->setVelocity(-10);
		break;
	default:
		return;
	}
}


void Pong::keyReleaseEvent( int keyCode, int nativeCode )
{
	switch( keyCode )
	{
	case MAK_LEFT:
		p1->setVelocity(0);
		break;
	case MAK_RIGHT:
		p1->setVelocity(0);
		break;
	case MAK_A:
		p2->setVelocity(0);
		break;
	case MAK_D:
		p2->setVelocity(0);
		break;
	default:
		return;
	}
}
/**
 * Called when the screen is touched.
 */
void Pong::multitouchPressEvent(MAPoint2d point, int touchId)
{
	if( point.x > 0 && point.x < 80 && point.y > 0 && point.y < 80 )
	{
		keyPressEvent(MAK_LEFT, 0);
		return;
	}
	if( point.x > getScreenX()-40 && point.x < getScreenX() && point.y > 0 && point.y < 80 )
	{
		keyPressEvent(MAK_RIGHT, 0);
		return;
	}
	if( point.x > 0 && point.x < 80 && point.y > getScreenY()-80 && point.y < getScreenY() )
	{
		keyPressEvent(MAK_A, 0);
		return;
	}
	if( point.x > getScreenX()-40 && point.x < getScreenX()
			&& point.y > getScreenY()-80 && point.y < getScreenY() )
	{
		keyPressEvent(MAK_D, 0);
		return;
	}
}

void Pong::multitouchReleaseEvent(MAPoint2d point, int touchId)
{
	if( point.x > 0 && point.x < 80 && point.y > 0 && point.y < 80 )
	{
		keyReleaseEvent(MAK_LEFT, 0);
		return;
	}
	if( point.x > getScreenX()-40 && point.x < getScreenX() && point.y > 0 && point.y < 80 )
	{
		keyReleaseEvent(MAK_RIGHT, 0);
		return;
	}
	if( point.x > 0 && point.x < 80 && point.y > getScreenY()-80 && point.y < getScreenY() )
	{
		keyReleaseEvent(MAK_A, 0);
		return;
	}
	if( point.x > getScreenX()-40 && point.x < getScreenX()
			&& point.y > getScreenY()-80 && point.y < getScreenY() )
	{
		keyReleaseEvent(MAK_D, 0);
		return;
	}
}

void Pong::runTimerEvent()
{
	draw();
}

u32 Pong::getScreenX() const
{
	return EXTENT_X(maGetScrSize());
}

u32 Pong::getScreenY() const
{
	return EXTENT_Y(maGetScrSize());
}

void Pong::draw()
{
	maSetColor(0x0);
	maFillRect(0, 0, getScreenX(), getScreenY());

	if( hitPaddle() )
	{
		s32 bvelx,bvely;
		ball->getVelocity(bvelx,bvely);
		ball->setVelocity(bvelx,-(bvely+1));
		ball->setVelMultiplyer( ball->getVelMultiplyer()+1 );
	}

	s32 bx, by;
	ball->getPosition(bx,by);
	if( by < 0 || by > getScreenY() )
	{
		if( by <= 0 )
			p2score++;
		else if( by >= getScreenY() )
			p1score++;

		delete ball;
		ball = new Ball(this, getScreenX()/2, getScreenY()/2, 1, 1);
	}

	p1->draw();
	p2->draw();
	ball->draw();

	// Draw score
	c8 buf[10];
	Gfx_setColor(255,255,255);

	ltoa( p1score, buf, 10 );
	Gfx_drawText(10, getScreenY()/2, "Top" );
	Gfx_drawText(10, getScreenY()/2+10, buf );

	ltoa( p2score, buf, 10 );
	Gfx_drawText(getScreenX()-40, getScreenY()/2, "Bot" );
	Gfx_drawText(getScreenX()-40, getScreenY()/2+10, buf );

	// Draw on-screen arrows for touch-screens
#ifdef MA_PROF_SUPPORT_STYLUS
	MARect arr_rect;
	arr_rect.top = 0;
	arr_rect.left = 0;
	arr_rect.width = 40;
	arr_rect.height = 80;

	MAPoint2d arr_point;
	arr_point.x = 0;
	arr_point.y = 0;

	Gfx_drawImageRegion(ARROW_LEFT_IMG, &arr_rect, &arr_point, TRANS_NONE);
	arr_point.x = getScreenX()-40;
	Gfx_drawImageRegion(ARROW_RIGHT_IMG, &arr_rect, &arr_point, TRANS_NONE);
	arr_point.y = getScreenY()-80;
	Gfx_drawImageRegion(ARROW_RIGHT_IMG, &arr_rect, &arr_point, TRANS_NONE);
	arr_point.x = 0;
	Gfx_drawImageRegion(ARROW_LEFT_IMG, &arr_rect, &arr_point, TRANS_NONE);
#endif

	maUpdateScreen();
}

bool Pong::hitPaddle() const
{
	MARect p1rect, p2rect, brect;
	p1rect.left = p1->getPosition() - 90;
	p1rect.top = 10;
	p1rect.width = p1rect.left+180;
	p1rect.height = p1rect.top+40;

	p2rect.left = p2->getPosition() - 90;
	p2rect.top = getScreenY()-50;
	p2rect.width = p2rect.left+180;
	p2rect.height = p1rect.top+40;

	s32 bx,by;
	ball->getPosition(bx,by);
	s32 bvx, bvy;
	ball->getVelocity(bvx, bvy);
	bvx *= ball->getVelMultiplyer();
	bvy *= ball->getVelMultiplyer();
	bx += bvx;
	by += bvy;

	brect.left = bx-20;
	brect.top = by-20;
	brect.width = brect.left+40;
	brect.height = brect.top+40;

	if( brect.top <= p1rect.height )
	{
		if( brect.width > p1rect.left && brect.left < p1rect.width )
			return true;
	}

	if( brect.height >= p2rect.top )
	{
		if( brect.width > p2rect.left && brect.left < p2rect.width )
			return true;
	}

	return false;
}
