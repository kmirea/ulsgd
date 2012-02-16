/*
 * Moblet.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: cmps359
 */

#include "Game.h"

Game::Game()
{
	addIdleListener(this);

	f32 a = getScreenX() / 400.0f;
	f32 b = getScreenY() / 600.0f;
	scale = sqrt( a*a+b*b );

	lasttime = maGetMilliSecondCount();
}

void Game::keyPressEvent(int keyCode, int nativeCode)
{
	if (MAK_BACK == keyCode || MAK_0 == keyCode)
	{
		// Call close to exit the application.
		close();
	}

	// Print the key character.
	printf("You typed: %c\n", keyCode);
}

void Game::keyReleaseEvent(int keyCode, int nativeCode)
{
}


void Game::pointerPressEvent(MAPoint2d point)
{
	// Print the x and y coordinate.
	printf("You touched: %i %i\n", point.x, point.y);
}

u32 Game::getScreenX() const
{
	return EXTENT_X(maGetScrSize());
}

u32 Game::getScreenY() const
{
	return EXTENT_Y(maGetScrSize());
}

void Game::idle()
{
	f32 sec_passed = (f32)(maGetMilliSecondCount() - lasttime) / 1000.0f;
	if( sec_passed <= 0 )
		sec_passed = 0.0001f;
}
