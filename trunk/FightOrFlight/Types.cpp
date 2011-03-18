#include <cstdlib>
#include <sys/time.h>
#include "Types.h"

ptr TimerObject::start_timer()
{
	gettimeofday( &start_time, 0);
	tick_time = start_time;
	return start_time.tv_sec*1000 + start_time.tv_usec/1000;
}
ptr TimerObject::stop_timer()
{
	gettimeofday( &end_time, 0 );
	return end_time.tv_sec*1000 + end_time.tv_usec/1000;
}
ptr TimerObject::tick()
{
	timeval temp_tick = tick_time;
	gettimeofday( &tick_time, 0 );
	return ((tick_time.tv_sec - temp_tick.tv_sec) * 1000) + ((tick_time.tv_usec - temp_tick.tv_usec)/1000);
}
ptr TimerObject::get_start_time() const
{
	return start_time.tv_sec*1000 + start_time.tv_usec/1000;
}
ptr TimerObject::get_end_time() const
{
	return end_time.tv_sec*1000 + end_time.tv_usec/1000;
}
