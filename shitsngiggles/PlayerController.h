/* 
 * File:   PlayerController.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:07 PM
 */

#ifndef PLAYERCONTROLLER_H
#define	PLAYERCONTROLLER_H

#include "Controller.h"

class PlayerController : public Controller, public InputUser
{
    void InputEvent(const u8 key);
};

#endif	/* PLAYERCONTROLLER_H */

