#include "MastEventReceiver.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

bool MastEventReceiver::OnEvent(const SEvent &event)
{
  bool eventprocessed = false;

  //////////////////////////////
  // Keyboard Input Event
  //////////////////////////////
  if (event.EventType == EET_KEY_INPUT_EVENT)
  {
     if (processState == STARTED)
     {
        // if key is Pressed Down
        if (event.KeyInput.PressedDown == true)
        {
           // If key was not down before
           if (keyState[event.KeyInput.Key] != DOWN)
           {
              keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
           }
           else
           {
              // if key was down before
              keyState[event.KeyInput.Key] = DOWN; // Set to Down
           }
        }
        else
        {

              // if the key is down
              if (keyState[event.KeyInput.Key] != UP)
              {
                 keyState[event.KeyInput.Key] = RELEASED; // Set to Released
              }
        }
     }


     eventprocessed = true;
  }

  //////////////////////////////
  // Mouse Input Event
  //////////////////////////////

  if (event.EventType == EET_MOUSE_INPUT_EVENT)
  {
     if (processState == STARTED)
     {
        //Mouse changed position
        if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
        {
           mouse.Y = event.MouseInput.Y;
           mouse.X = event.MouseInput.X;
        }

        //Wheel moved.
        if (event.MouseInput.Event == EMIE_MOUSE_WHEEL)
        {
           mouse.wheel += event.MouseInput.Wheel;
        }

        //Left Mouse Button Pressed
        if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
        {
           //
           if (mouseButtonState[0] == UP || mouseButtonState[0] == RELEASED)
           {
              mouseButtonState[0] = PRESSED;
           }
           else
           {
              mouseButtonState[0] = DOWN;
           }
        }

        //Left Mouse Button Rleased
        if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
        {
           //
           if (mouseButtonState[0] != UP)
           {
              mouseButtonState[0] = RELEASED;
           }
        }

        //Middle Mouse Button Pressed
        if (event.MouseInput.Event == EMIE_MMOUSE_PRESSED_DOWN)
        {
           //
           if (mouseButtonState[1] == UP || mouseButtonState[1] == RELEASED)
           {
              mouseButtonState[1] = PRESSED;
           }
           else
           {
              mouseButtonState[1] = DOWN;
           }
        }

        //Middle Mouse Button Rleased
        if (event.MouseInput.Event == EMIE_MMOUSE_LEFT_UP)
        {
           //
           if (mouseButtonState[1] != UP)
           {
              mouseButtonState[1] = RELEASED;
           }
        }

        //Right Mouse Button Pressed
        if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
        {
           //
           if (mouseButtonState[2] == UP || mouseButtonState[2] == RELEASED)
           {
              mouseButtonState[2] = PRESSED;
           }
           else
           {
              mouseButtonState[2] = DOWN;
           }
        }

        //Right Mouse Button Rleased
        if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
        {
           //
           if (mouseButtonState[2] != UP)
           {
              mouseButtonState[2] = RELEASED;
           }
        }
     }


     eventprocessed = true;
  }


  return eventprocessed;
}

float MastEventReceiver::mouseWheel()
{
  return mouse.wheel;
}

int MastEventReceiver::mouseX()
{
  return mouse.X;
}

int MastEventReceiver::mouseY()
{
  return mouse.Y;
}

bool MastEventReceiver::leftMouseReleased()
{
  if (mouseButtonState[0] == RELEASED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::leftMouseUp()
{
  if (mouseButtonState[0] == RELEASED || mouseButtonState[0] == UP)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::leftMousePressed()
{
  if (mouseButtonState[0] == PRESSED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::leftMouseDown()
{
  if (mouseButtonState[0] == PRESSED || mouseButtonState[0] == DOWN)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::middleMouseReleased()
{
  if (mouseButtonState[1] == RELEASED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::middleMouseUp()
{
  if (mouseButtonState[1] == RELEASED || mouseButtonState[1] == UP)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::middleMousePressed()
{
  if (mouseButtonState[1] == PRESSED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::middleMouseDown()
{
  if (mouseButtonState[1] == PRESSED || mouseButtonState[1] == DOWN)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::rightMouseReleased()
{
  if (mouseButtonState[2] == RELEASED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::rightMouseUp()
{
  if (mouseButtonState[2] == RELEASED || mouseButtonState[2] == UP)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::rightMousePressed()
{
  if (mouseButtonState[2] == PRESSED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::rightMouseDown()
{
  if (mouseButtonState[2] == PRESSED || mouseButtonState[2] == DOWN)
  {
     return true;
  }
  else
  {
     return false;
  }
}//

bool MastEventReceiver::keyPressed(char keycode)
{
  if (keyState[(u32)keycode] == PRESSED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::keyDown(char keycode)
{
  if (keyState[(u32)keycode] == DOWN || keyState[(u32)keycode] == PRESSED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::keyUp(char keycode)
{
  if (keyState[(u32)keycode] == UP || keyState[(u32)keycode] == RELEASED)
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool MastEventReceiver::keyReleased(char keycode)
{
  if (keyState[(u32)keycode] == RELEASED)
  {
     return true;
  }
  else
  {
     return false;
  }
}


// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this at the very START of your Main Loop
void MastEventReceiver::endEventProcess()
{
  processState = ENDED;
}

// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this function at the END of your Main Loop.
void MastEventReceiver::startEventProcess()
{

  processState = STARTED;
  //Keyboard Key States
  for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
  {
     if (keyState[i] == RELEASED)
     {
        keyState[i] = UP;
     }

     if (keyState[i] == PRESSED)
     {
        keyState[i] = DOWN;
     }
  }
  //Mouse Button States
  for (int i = 0; i <= 2; i++)
  {
     if (mouseButtonState[i] == RELEASED)
     {
        mouseButtonState[i] = UP;
     }

     if (mouseButtonState[i] == PRESSED)
     {
        mouseButtonState[i] = DOWN;
     }
  }
  //Mouse Wheel state
  mouse.wheel = 0.0f;

}

void MastEventReceiver::init()
{
  //KeyBoard States.
  for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
  {
     keyState[i] = UP;
  }
  //Mouse states
  for (int i = 0; i <= 2; i++)
  {
     mouseButtonState[i] = UP;
  }
  //Mouse X/Y coordenates.
  mouse.X = 0;
  mouse.Y = 0;
  mouse.wheel = 0.0f;
}
