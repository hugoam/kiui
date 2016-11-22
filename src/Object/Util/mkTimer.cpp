//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Util/mkTimer.h>

#include <iostream>

namespace mk
{
	Timer Timer::sInstance;

    Timer::Timer()
        : m_timeTable()
    {}

    Timer::~Timer()
    {}

	void Timer::firstUpdate(void* updater)
	{
		m_timeTable.insert (std::pair<void*, clock_t> (updater, clock()));
	}

    void Timer::update(void* updater)
    {
        TimeTable::iterator it = m_timeTable.find(updater);
        if(it != m_timeTable.end())
        {
			//std::cerr << "Update_clock: " << clock() << std::endl;
            (*it).second = clock();
        }
    }

    double Timer::read(void* updater)
    {
        double timeStep(0.0f);
        TimeTable::iterator it = m_timeTable.find(updater);
        if(it != m_timeTable.end())
        {
			//std::cerr << "Clock: " << clock() << std::endl;
            timeStep = static_cast<double>(clock() - (*it).second) / CLOCKS_PER_SEC;
        }

        return timeStep;
    }

	double Timer::step(void* updater)
	{
		double step = this->read(updater);
		this->update(updater);
		return step;
	}

    Clock::Clock()
        : m_last(clock())
    {}

    Clock::~Clock()
    {}

    void Clock::update()
    {
		m_last = clock();
    }

	size_t Clock::readTick()
	{
		return size_t(this->read() / TICK_INTERVAL);
	}

	size_t Clock::stepTick()
	{
		size_t tick = this->readTick();
		size_t delta = tick - m_lastTick;

		m_lastTick = tick;
		return delta;
	}

    double Clock::read()
    {
        double timeStep = static_cast<double>(clock() - m_last) / CLOCKS_PER_SEC;
        return timeStep;
    }

	double Clock::step()
	{
		double step = this->read();
		this->update();
		return step;
	}
}
