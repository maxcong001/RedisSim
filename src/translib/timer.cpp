/*
 * timer.cpp
 *
 *  Created on: 2015年5月31日
 *      Author: 
 */

#include "translib/timer.h"
#include "translib/loop.h"

namespace translib
{

Timer::Timer(const translib::Loop &loop) : _loop(loop),
										   _event(NULL),
										   _interval(0),
										   _round(1),
										   _curRound(0),
										   _handler(NULL)
{
}

Timer::~Timer()
{
	reset();
}

bool Timer::startRounds(
	uint32_t interval,
	uint64_t round,
	void *usrdata,
	translib::Timer::Handler handler)
{
	if (NULL != _event)
	{
		return false;
	}

	_event = event_new(_loop, -1, (round > 1) ? EV_PERSIST : 0, eventHandler, this);
	if (NULL == _event)
	{
		return false;
	}

	struct timeval tv = {};
	evutil_timerclear(&tv);
	tv.tv_sec = interval / 1000;
	tv.tv_usec = interval % 1000 * 1000;

	if (0 != event_add(_event, &tv))
	{
		reset();
		return false;
	}

	_interval = interval;
	_round = round;
	_curRound = 0;
	_handler = handler;
	_usrdata = usrdata;

	return true;
}

bool Timer::startOnce(uint32_t interval, void *usrdata, translib::Timer::Handler handler)
{
	return startRounds(interval, 1, usrdata, handler);
}

bool Timer::startForever(uint32_t interval, void *usrdata, translib::Timer::Handler handler)
{
	return startRounds(interval, uint32_t(-1), usrdata, handler);
}

bool Timer::startAfter(
	uint32_t after,
	uint32_t interval,
	uint64_t round,
	void *usrdata,
	translib::Timer::Handler handler)
{
	return startOnce(after, usrdata, [=](void *usrdataa) {
		startRounds(interval, round, usrdataa, handler);
	});
}

void Timer::reset()
{
	if (NULL != _event)
	{
		event_free(_event);
		_event = NULL;
	}
}

void Timer::eventHandler(evutil_socket_t fd, short events, void *ctx)
{
	Timer *timer = (Timer *)ctx;
	translib::Timer::Handler handler = timer->_handler;

	timer->_curRound++;
	if (timer->_curRound >= timer->_round)
	{
		event_del(timer->_event);
		timer->reset();
	}

	handler(timer->_usrdata);
}

} /* namespace translib */
