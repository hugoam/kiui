//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Threading/mkScheduler.h>

namespace mk
{
	Scheduler::Scheduler(size_t queueSize)
		: mActions(queueSize)
	{}

	Scheduler::~Scheduler() 
	{}

	bool Scheduler::scheduleAction(const ProcedureType& action)
	{
		return mActions.push(action);
	}

	void Scheduler::processActions()
	{
		int i = 0;
		ProcedureType action;

		if(!mActions.empty())
		{
			while(((++i) < 5) && mActions.pop(action))
			{
				action();
			}
		}
	}
}
