/*
 * timer.h
 *
 *  Created on: 2015年5月31日
 *      Author: 
 */

#include "translib/timerManager.h"
#include "logger/logger.h"
namespace translib
{

bool TimerManager::init()
{

#if 0
	auto work_fun = std::bind(&TimerManager::do_work, this);
	// actually we want the thread never exit.
	// So we do not kill the thread.
	// start once and leave it there.
	// suppose when the loop stop, the thread will exit then.
	std::thread timer_thread(work_fun);
#endif
	__LOG(debug, "[TimerManager] init timer manager!");
	//start audit timer
	audit_timer = new Timer(_loop);
	audit_timer->startForever(AUDIT_TIMER, this, [&](void *usrdata) {
		((TimerManager *)usrdata)->audit();
	});
	_loop.start(true);
	return true;
}
bool TimerManager::audit()
{
	std::lock_guard<std::mutex> lck(mtx);
	timer_map tmp;
	__LOG(debug, "[TimerManager] there are " << t_map.size() << " timers");

	for_each(t_map.begin(), t_map.end(), [&](std::pair<const int, Timer::ptr_p> &i) {
		__LOG(debug, "[TimerManager] check timer with ID : " << i.first);
		if ((i.second)->isFinished())
		{
			__LOG(debug, "[TimerManager] delete timer, ID is : " << i.first);
		}
		else
		{
			__LOG(debug, "[TimerManager] timer still running  timer, ID is : " << i.first);
			tmp.emplace(i);
		}
	});
	t_map.swap(tmp);
	return true;
}
Timer::ptr_p TimerManager::getTimer(int *timerID)
{
	int tid = getUniqueID();
	Timer::ptr_p tmp_ptr(new Timer(_loop));
	std::lock_guard<std::mutex> lck(mtx);
	t_map.emplace(tid, tmp_ptr);
	if (timerID)
	{
		*timerID = tid;
	}
	return tmp_ptr;
}
// you can call timer.stop or pass in the ID and we will kill the timer
bool TimerManager::killTimer(int timerID)
{
	std::lock_guard<std::mutex> lck(mtx);

	auto iter = t_map.find(timerID);
	if (iter != t_map.end())
	{
		(iter->second)->stop();
	}
	else
	{
		__LOG(debug, "[TimerManager] did not find the timer ID");
	}
	return true;
}

} /* namespace translib */
