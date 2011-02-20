#ifndef MASTEVENTRECIEVER_H_
#define MASTEVENTRECIEVER_H_

/// ==================================================================================================
/// MastEventReceiver code is © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit
/// This file may be used in any non-commercial or commercial project as long as the following conditions are met:
/// You may not claim this code as being your own.
/// You may not use this code for any harmful, malicious or otherwise damaging programs.
///
/// This is version 1.2a of the class.
/// This class is designed for use with the Irrlicht Engine, it was written for version 1.3 of the engine.
/// ==================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// To use this Class just add  #include "MastEventReceiver.cpp"  to the end of your includes list. (or add the class in-line into your program)
// Then create an instance of it like so: MastEventReceiver eventReceiver;
// Then call the initialization fucntion like so: eventReceiver.init();
// Then inside your Main Game Loop place "eventReceiver.endEventProcess();" in the beginning of your game loop, before anything -
// that would require input, then put "eventReceiver.startEventProcess();" at the very end of your Main Game Loop.
// yeah I know it's confusing, but it makes alot more sense in the internals of the class.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Change this to the path where your Irrlicht Header Files are.
#include "./irrlicht/irrlicht.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/// ==============================
/// MastEventReceiver
/// ==============================
class MastEventReceiver : public IEventReceiver
{

   protected:
   // Enumeration for UP, DOWN, PRESSED and RELEASED key states. Also used for mouse button states.
   enum keyStatesENUM {UP, DOWN, PRESSED, RELEASED};

   // Enumeration for Event Handling State.
   enum processStateENUM {STARTED, ENDED};

   // Mouse button states.
   keyStatesENUM mouseButtonState[3]; //Left(0), Middle(1) and Right(2) Buttons.

   // Keyboard key states.
   keyStatesENUM keyState[KEY_KEY_CODES_COUNT];

   // Mouse X/Y coordinates and Wheel data.
   struct mouseData
   {
   int X;
   int Y;
   float wheel; //wheel is how far the wheel has moved
   };
   struct mouseData mouse;

   processStateENUM processState; // STARTED = handling events, ENDED = not handling events

   bool OnEvent(const SEvent &event);

   //////////////////////
   // Public functions
   //////////////////////
   public:

   float mouseWheel();
   int mouseX();
   int mouseY();

   bool leftMouseReleased();
   bool leftMouseUp();
   bool leftMousePressed();
   bool leftMouseDown();

   bool middleMouseReleased();
   bool middleMouseUp();
   bool middleMousePressed();
   bool middleMouseDown();

   bool rightMouseReleased();
   bool rightMouseUp();
   bool rightMousePressed();
   bool rightMouseDown();

   bool keyPressed(char keycode);
   bool keyDown(char keycode);
   bool keyUp(char keycode);
   bool keyReleased(char keycode);

   // This is used so that the Key States will not be changed during execution of your Main game loop.
   // Place this at the very START of your Main Loop
   void endEventProcess();

   // This is used so that the Key States will not be changed during execution of your Main game loop.
   // Place this function at the END of your Main Loop.
   void startEventProcess();
   void init();
};
/// ==========================================
/// END OF MastEventReceiver
/// ==========================================

#endif //MASTEVENTRECIEVER_H_
