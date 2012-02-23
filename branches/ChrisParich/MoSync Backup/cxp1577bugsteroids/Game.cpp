/*
 * Moblet.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: cmps359
 */

#include "Game.h"

void Game::makeBugZappers()
{
	for (int i = 0; i < maxBugZappers; i++)
	{
		int x = rand() % screenWidth, y = rand() % screenHeight - offset;

		while( x - screenWidth/2 > -10*scale && x - screenWidth/2 < 10*scale )
			x = rand() % screenWidth;
		while( y - (screenHeight-offset)/2 > - 10*scale && x - (screenHeight-offset)/2 < 10*scale )
			y = rand() % screenHeight;

		BugZapper bz = BugZapper(x, y, (s32)(scale*25));
		bugZappers.add(bz);
	}
}

void Game::makeBugs()
{
	for (int i = 0; i < maxBugs; i++)
	{
		int x = rand() % screenWidth, y = rand() % screenHeight - offset;

		while( x - screenWidth/2 > -10*scale && x - screenWidth/2 < 10*scale )
			x = rand() % screenWidth;
		while( y - (screenHeight-offset)/2 > - 10*scale && x - (screenHeight-offset)/2 < 10*scale )
			y = rand() % screenHeight;

		Bug b = Bug(screenWidth, screenHeight - offset, x, y, scale);
		b.setBugColor(colors[rand() % 8]);
		int turn = rand() % 8;
		for (int j = 0; j < turn; j++)
		{
			b.turnright();
			b.turnright();
		}
		bugs.add(b);
	}
	for (int i = 0; i < maxEvilBugs; i++)
	{

		int x = rand() % screenWidth, y = rand() % screenHeight - offset;

		while( x - screenWidth/2 > -10*scale && x - screenWidth/2 < 10*scale )
			x = rand() % screenWidth;
		while( y - (screenHeight-offset)/2 > - 10*scale && x - (screenHeight-offset)/2 < 10*scale )
			y = rand() % screenHeight-offset;

		EvilBug b = EvilBug(screenWidth, screenHeight - offset,
				x, y, scale,
				myBug);
		b.setBugColor(0xFFFFFF);
		int turn = rand() % 8;
		for (int j = 0; j < turn; j++)
		{
			b.turnright();
			b.turnright();
		}
		evilBugs.add(b);
	}
}
void Game::makeMyBug()
{
	myBug = new Bug(screenWidth, screenHeight - offset, screenWidth / 2,
			(screenHeight - offset) / 2, scale);
	myBug->setBugColor(0xFF0000);
}
// *********** draw the game elements  **************
void Game::drawCanvas()
{
	maSetColor(0);
	maFillRect(0, 0, screenWidth, screenHeight - offset);
}
void Game::drawBugZappers()
{
	for (int i = 0; i < bugZappers.size(); i++)
		bugZappers[i].paintBugZapper();
}
void Game::drawBugs()
{
	for (int i = 0; i < bugs.size(); i++)
		if (bugs[i].isAlive())
			bugs[i].paintBug();
}
void Game::drawEvilBugs()
{
	for (int i = 0; i < evilBugs.size(); i++)
		if (evilBugs[i].isAlive())
			evilBugs[i].paintBug();
}
void Game::drawMyBug()
{
	myBug->paintBug();
}
// *********** draw the game controls  **************
void Game::drawControls()
{
	control_scaler->draw(screenWidth/2, screenHeight - offset/2, 0);
}
// *********** move the game elements  **************
void Game::moveBugs()
{
	int d;
	for (int i = 0; i < maxBugs; i++)
	{
		if (bugs[i].isAlive())
		{
			d = rand() % 20;
			if (d < 1)
				bugs[i].turnright();
			else if (d > 18)
				bugs[i].turnleft();
			bugs[i].go();
		}
	}
}
void Game::moveEvilBugs()
{
	for (int x = 0; x < maxEvilBugs; x++)
	{
		if (evilBugs[x].isAlive())
		{
			evilBugs[x].calcDirection();
			evilBugs[x].go();
		}
	}
}
void Game::moveMyBug()
{
	myBug->go();
}
// *********** check for collisions of the game elements  **************
void Game::CollideBugToBug()
{
	for (int a = 0; a < maxBugs - 1; a++)
		for (int b = a + 1; b < maxBugs; b++)
			if (bugs[a].isAlive() & bugs[b].isAlive()
					& bugs[a].impactBug(bugs[b]))
			{
				bugs[a].isDead();
				bugs[b].isDead();
			}
}
void Game::CollideBugToEvilBug()
{
	for (int a = 0; a < maxBugs - 1; a++)
		for (int b = 0; b < maxEvilBugs; b++)
			if (bugs[a].isAlive() & evilBugs[b].isAlive()
					& bugs[b].impactBug(evilBugs[a]))
			{
				bugs[a].isDead();
				evilBugs[b].isDead();
			}
}
void Game::CollideEvilBugToEvilBug()
{
	for (int a = 0; a < maxEvilBugs - 1; a++)
		for (int b = a + 1; b < maxEvilBugs; b++)
			if (evilBugs[a].isAlive() & evilBugs[b].isAlive()
					& evilBugs[b].impactBug(evilBugs[a]))
			{
				evilBugs[a].isDead();
				evilBugs[b].isDead();
			}
}
void Game::CollideBugToBugZapper()
{
	for (int a = 0; a < maxBugs; a++)
		for (int b = 0; b < maxBugZappers; b++)
			if (bugs[a].isAlive() & bugZappers[b].impactBug(bugs[a]))
			{
				bugs[a].isDead();
			}
}
void Game::CollideEvilBugToBugBugZapper()
{
	for (int a = 0; a < maxEvilBugs; a++)
		for (int b = 0; b < maxBugZappers; b++)
			if (evilBugs[a].isAlive() & bugZappers[b].impactBug(evilBugs[a]))
			{
				evilBugs[a].isDead();
			}
}
// *********** check for game over condition  **************
bool Game::isGameOver()
{
	for (int x = 0; x < maxBugs; x++)
		if (bugs[x].isAlive() && myBug->impactBug(bugs[x]))
			return true;
	for (int x = 0; x < maxEvilBugs; x++)
		if (evilBugs[x].isAlive() && evilBugs[x].impactBug((*myBug)))
			return true;
	for (int y = 0; y < maxBugZappers; y++)
		if (bugZappers[y].impactBug((*myBug)))
			return true;
	return false;
}
// *********** update the display  **************
void Game::updateScreen()
{
	if( gameRestartWindow )
		drawGameRestart();
	else
	{
		drawCanvas();
		drawBugZappers();
		drawBugs();
		drawEvilBugs();
		drawMyBug();
		drawControls();
	}
	maUpdateScreen();
}

void Game::init()
{
	srand((unsigned) maLocalTime());
	play = false;
	MAExtent size = maGetScrSize();
	screenWidth = EXTENT_X(size);
	screenHeight = EXTENT_Y(size);
	scale = ((double) screenHeight) / 320;
	maxBugZappers = 5;
	maxBugs = 30;
	maxEvilBugs = 5;

	gameRestartWindow = false;

	{
		const char* controls = "L     -     S     +     R";
		int controls_x = EXTENT_X(maGetTextSize(controls));
		int controls_y = EXTENT_Y(maGetTextSize(controls));

		maCreateDrawableImage( control_handle, controls_x, controls_y );
		maSetDrawTarget( control_handle );
		maSetColor(0xFFFFFF);

		maDrawText(0, 0, controls);

		maSetDrawTarget( HANDLE_SCREEN );

		MARect ctrl_rect;
		ctrl_rect.top = 0;
		ctrl_rect.left = 0;
		ctrl_rect.height = controls_y;
		ctrl_rect.width = controls_x;

		double control_scale = (double)screenWidth / (double)controls_x;

		control_scaler = new Scaler( control_handle, &ctrl_rect, control_scale, 1, 1, Scaler::ST_NEAREST_NEIGHBOUR );
	}

	controlDisplayWidth = screenWidth/5;
	offset = EXTENT_Y(control_scaler->getSize(0));

	{
		const char*	say		= "Game Over";
		const char*	ask		= "Play Again?";
		const char*	choice	= "Yes   No";

		int size_x = EXTENT_X( maGetTextSize(ask) );
		int size_y = EXTENT_Y( (maGetTextSize(ask)+4) );

		maCreateDrawableImage( restart_handle, size_x, size_y*3 );
		maSetDrawTarget( restart_handle );

		maSetColor(0xFFFFFF);

		maDrawText( size_x/2 - EXTENT_X(maGetTextSize(say))/2 , 2, say);
		maDrawText( 0, size_y + 2, ask );
		maDrawText( size_x/2 - EXTENT_X(maGetTextSize(choice))/2, 2*size_y+2, choice);

		maSetDrawTarget( HANDLE_SCREEN );

		MARect ctrl_rect;
		ctrl_rect.top = 0;
		ctrl_rect.left = 0;
		ctrl_rect.height = size_y*3;
		ctrl_rect.width = size_x;

		double restart_scale = (double)screenWidth / (double)size_x / 2;

		restart_scaler = new Scaler( restart_handle, &ctrl_rect, restart_scale, 1, 1, Scaler::ST_NEAREST_NEIGHBOUR );
		ryx = screenWidth/2 - EXTENT_X(restart_scaler->getSize(0))/4;
		rnx = screenWidth/2 + EXTENT_X(restart_scaler->getSize(0))/4;
		ryy = screenHeight/2 + EXTENT_Y(restart_scaler->getSize(0))/3;
	}

	makeMyBug();
	drawCanvas();
	makeBugZappers();
	drawBugZappers();
	makeBugs();
	drawBugs();
	drawEvilBugs();
	drawMyBug();
	drawControls();
	maUpdateScreen();
}

Game::Game()
{
	control_handle = maCreatePlaceholder();
	restart_handle = maCreatePlaceholder();
	init();
}

/**
 * Called when a key is pressed.
 */
void Game::keyPressEvent(int keyCode, int nativeCode)
{
	if( gameRestartWindow )
	{
		if( MAK_1 == keyCode || MAK_LEFT == keyCode )	// Yes
		{
			bugZappers.clear();
			bugs.clear();
			evilBugs.clear();
			maDestroyObject(control_handle);
			delete control_scaler;
			maDestroyObject(restart_handle);
			delete restart_scaler;
			init();
		}
		else if( MAK_3 == keyCode || MAK_RIGHT == keyCode )	// No
		{
			close();
		}
		else if( MAK_BACK == keyCode || MAK_0 == keyCode )	// Also no
		{
			close();
		}
	}
	else
	{
		if (MAK_3 == keyCode || MAK_RIGHT == keyCode)
		{
			myBug->turnright();
			myBug->turnright();
		}
		else if (MAK_1 == keyCode || MAK_LEFT == keyCode)
		{
			myBug->turnleft();
			myBug->turnleft();
		}
		else if (MAK_UP == keyCode)
		{
			myBug->speedUp();
		}
		else if (MAK_DOWN == keyCode)
		{
			myBug->slowDown();
		}
		else if (MAK_S == keyCode || MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			if ( isGameOver() )
			{
				removeTimer(this);
				close();
			}
			else
			{
				play = true;
				addTimer(this, 50, -1);
			}
		}
	}
}

/**
 * Called when the screen is touched.
 */
void Game::pointerPressEvent(MAPoint2d point)
{
	if( gameRestartWindow )
	{
		if( point.y > ryy - 10*scale && point.y < ryy + 10*scale )
		{
			if( point.x > ryx - 10*scale && point.x < ryx + 10*scale )
				keyPressEvent(MAK_1, 0);
			else if( point.x > rnx - 10*scale && point.x < rnx + 10*scale )
				keyPressEvent(MAK_3, 0);
		}
	}
	else
	{
		if (point.y > screenHeight - offset)
		{
			if (point.x < controlDisplayWidth)
				keyPressEvent(MAK_1, 0);
			else if (point.x < controlDisplayWidth * 2)
				keyPressEvent(MAK_DOWN, 0);
			else if (point.x < controlDisplayWidth * 3)
				keyPressEvent(MAK_S, 0);
			else if (point.x < controlDisplayWidth * 4)
				keyPressEvent(MAK_UP, 0);
			else
				keyPressEvent(MAK_3, 0);
		}
	}
}

//	u32 getScreenX() const;
//
//	u32 getScreenY() const;

void Game::runTimerEvent()
{
	if( gameRestartWindow )
	{
		updateScreen();
		removeTimer(this);
	}
	else
	{
		moveBugs();
		moveEvilBugs();
		moveMyBug();
		updateScreen();
		CollideBugToBug();
		CollideBugToEvilBug();
		CollideEvilBugToEvilBug();
		CollideBugToBugZapper();
		CollideEvilBugToBugBugZapper();

		if (isGameOver())
			gameRestartWindow = true;
	}
}

void Game::drawGameRestart()
{
	int draw_x = screenWidth/2;
	int draw_y = screenHeight/2;
	restart_scaler->draw( draw_x, draw_y, 0 );
}
