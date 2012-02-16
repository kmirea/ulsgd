#include "Game.h"

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new Game());
	return 0;
}
