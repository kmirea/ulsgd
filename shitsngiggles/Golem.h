/* 
 * File:   Golem.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:06 PM
 */

#ifndef GOLEM_H
#define	GOLEM_H

#include "Elemental.h"

class Golem : public Elemental
{
    bool isDead(); //checks to see if the golem is dead

    void prepass(const u32 GameTime); //clear state
    void pass(const u32 GameTime); // decision
    void postpass(const u32 GameTime); // action


    void handleCollision(Object* Other); // handles collision
    
};

#endif	/* GOLEM_H */

