//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UPDATABLE_H
#define MK_UPDATABLE_H

#include <Object/mkObjectForward.h>

#include <atomic>

namespace mk
{
	class MK_OBJECT_EXPORT Updatable
	{
	public:
		virtual void nextFrame(size_t tick, size_t delta) = 0;
	};

	class MK_OBJECT_EXPORT Executable
	{
	public:
		Executable() : m_done(false), m_doneFlag(0) {}
		virtual ~Executable() {}

		virtual void begin() = 0;
		virtual void update(size_t tick, double step) { UNUSED(tick); UNUSED(step); }
		virtual void abort() {}
		
		void execute() { m_done = false; this->begin(); }
		void stop()	{ m_done = true; if(m_doneFlag) *m_doneFlag = true; this->abort(); }
		bool done() { return m_done; }

		void flag(std::atomic<bool>* done) { *done = false; m_doneFlag = done; }

	protected:
		bool m_done;
		std::atomic<bool>* m_doneFlag;
	};
}

#endif // MK_UPDATABLE_H
