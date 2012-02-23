/*
 * Moblet.h
 *
 *  Created on: Feb 16, 2012
 *      Author: cmps359
 */

#ifndef MOBLET_H_
#define MOBLET_H_

#include <MAUtil/Moblet.h>
#include <MAUI/Scaler.h>
#include <conprint.h>
#include "Types.h"
#include "Bug.h"
#include "EvilBug.h"
#include "BugZapper.h"

using namespace MAUtil;
using namespace MAUI;

const int colors[8] =
		{ 0x00FF00, 0x0000FF, 0xFF00FF, 0x00FFFF, 0xFFFF00, 0x888888, 0x0088FF,
				0x00FF88 };

class Game: public Moblet, public TimerListener
{
	Vector<BugZapper> bugZappers;
	Vector<Bug> bugs;
	Vector<EvilBug> evilBugs;
	int maxBugZappers;
	int maxBugs;
	int maxEvilBugs;
	Bug *myBug;
	int screenWidth, screenHeight;
	int offset;
	int controlDisplayWidth;
	double scale;
	bool play;
	MAHandle control_handle;
	Scaler* control_scaler;

	bool gameRestartWindow;
	MAHandle restart_handle;
	Scaler* restart_scaler;
	int ryx, ryy, rnx, rny;

// *********** make the game elements  **************
	void makeBugZappers();
	void makeBugs();
	void makeMyBug();

// *********** draw the game elements  **************
	void drawCanvas();
	void drawBugZappers();
	void drawBugs();
	void drawEvilBugs();
	void drawMyBug();

// *********** draw the game controls  **************
	void drawControls();

// *********** move the game elements  **************
	void moveBugs();
	void moveEvilBugs();
	void moveMyBug();

// *********** check for collisions of the game elements  **************
	void CollideBugToBug();
	void CollideBugToEvilBug();
	void CollideEvilBugToEvilBug();
	void CollideBugToBugZapper();
	void CollideEvilBugToBugBugZapper();

// *********** check for game over condition  **************
	bool isGameOver();

// *********** update the display  **************
	void updateScreen();

	void drawGameRestart();

	void init();
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
	 * Called when the screen is touched.
	 */
	void pointerPressEvent(MAPoint2d point);

	void runTimerEvent();
};

#endif /* MOBLET_H_ */
