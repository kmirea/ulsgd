/* 
 * File:   Timer.h
 * Author: chris
 *
 * Created on April 30, 2011, 1:58 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#include <irrlicht/ITimer.h>
#include "ReferenceCountedObject.h"
#include "Types.h"

class GameManager;

class Timer : public ReferenceCountedObject
{
public:
    Timer( GameManager* Game );
    
protected:
	virtual ~Timer();
    
public:
	// let the clock tick
	void tick( u32 StartTime = 0 );
	
    // get time passed since start in milliseconds
    u32 getTimeMS() const;
    // get time passed since last frame in milliseconds
    u32 getTickMS() const;
    
    // get time passed since start in seconds
    f32 getTimeS() const;
    // get time passed since last frame in seconds
    f32 getTickS() const;
    
protected:
    string getDebugInfo() const;
    
private:
	u32 LastTick;
	u32 CurrTick;
	
	irr::ITimer* IrrTimer;
};

#endif	/* TIMER_H */

