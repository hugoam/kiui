//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UPDATABLE_H_INCLUDED
#define MK_UPDATABLE_H_INCLUDED

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
		Executable() : mDone(false), mDoneFlag(0) {}
		virtual ~Executable() {}

		virtual void begin() = 0;
		virtual void update(size_t tick, double step) {}
		virtual void abort() {}
		
		void execute() { mDone = false; this->begin(); }
		void stop()	{ mDone = true; if(mDoneFlag) *mDoneFlag = true; this->abort(); }
		bool done() { return mDone; }

		void flag(std::atomic<bool>* done) { *done = false; mDoneFlag = done; }

	protected:
		bool mDone;
		std::atomic<bool>* mDoneFlag;
	};
}

#endif // MK_UPDATABLE_H_INCLUDED
