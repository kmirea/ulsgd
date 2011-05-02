#include "Timer.h"
#include "GameManager.h"

Timer::Timer( GameManager* Game ) : IrrTimer(Game->getWorldManager()->getIrrlichtDriver()->getTimer()), CurrTick(0), 
		LastTick(0)
{
	IrrTimer->grab();
	IrrTimer->start();
}

Timer::~Timer()
{
	IrrTimer->drop();
}

void Timer::tick( u32 StartTime )
{
	if( StartTime )
	{
		IrrTimer->setTime( StartTime );
	}
	IrrTimer->tick();
	LastTick = CurrTick;
	CurrTick = IrrTimer->getTime();
}

u32 Timer::getTickMS() const
{
	return CurrTick - LastTick;
}

f32 Timer::getTickS() const
{
	return (f32)(CurrTick - LastTick) * 0.001f;
}

u32 Timer::getTimeMS() const
{
	IrrTimer->tick();
	return IrrTimer->getTime();
}

f32 Timer::getTimeS() const
{
	IrrTimer->tick();
	return (f32)(IrrTimer->getTime()) * 0.001f;
}

string Timer::getDebugInfo() const
{
	return string("Timer");
}
