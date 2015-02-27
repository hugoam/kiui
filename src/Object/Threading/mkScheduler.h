//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SCHEDULER_H_INCLUDED
#define MK_SCHEDULER_H_INCLUDED

/* mk */
#include <Object/Threading/mkLocklessQueue.h>

/* Standard */
#include <functional>
#include <string>
#include <list>
#include <map>
#include <iostream>

namespace mk
{
	class MK_OBJECT_EXPORT Scheduler
	{
	public:
		typedef std::function<void ()> ProcedureType;

	public:
		Scheduler(size_t queueSize);
		~Scheduler();

		bool scheduleAction(const ProcedureType& action);
		void processActions();

	private:
		LocklessQueue<ProcedureType> mActions;
	};
}

#endif // MK_SCHEDULER_H_INCLUDED
