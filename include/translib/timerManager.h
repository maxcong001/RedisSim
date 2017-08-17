
#pragma once

#include "loop.h"
#include "timer.h"
#include <unordered_map>
#include <atomic>
#include <thread>
#include <algorithm>

namespace translib
{

class Loop;
class Timer;
#define AUDIT_TIMER 5000
class TimerManager
{
  public:
	typedef std::unordered_map<int, Timer::ptr_p> timer_map;
	TimerManager() : _loop()
	{
		uniqueID_atomic = 0;
		init();
	}
	~TimerManager()
	{
		//stop audit timer
		if (!audit_timer)
		{
			delete audit_timer;
		}
		audit_timer = NULL;
	}
	bool init();
	Timer::ptr_p getTimer(int *timerID = NULL);
	bool killTimer(int timerID);
	bool audit();

	TimerManager *Instance()
	{
		static TimerManager *ins = new TimerManager();
		return ins;
	}

  protected:
  private:
	int getUniqueID()
	{
		return (uniqueID_atomic++);
	}

	std::atomic<int> uniqueID_atomic;
	timer_map t_map;
	std::mutex mtx;
	Loop _loop;
	Timer *audit_timer;
};

} /* namespace translib */
