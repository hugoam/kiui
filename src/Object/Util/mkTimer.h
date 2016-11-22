//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TIMER_H_INCLUDED
#define MK_TIMER_H_INCLUDED

/* Basic headers */
#include <Object/mkTyped.h>
#include <Object/mkObject.h>
#include <ctime>
#include <map>

#define TICK_INTERVAL 0.02

namespace mk
{
	inline size_t globalTick()
	{
		return size_t(clock() / TICK_INTERVAL);
	}

	class MK_OBJECT_EXPORT _I_ Time : public Struct
	{
	public:
		_C_ Time(double val) : value(val) {}
		Time(int days, int hours, int minutes, int seconds) : value(days * 86400 + hours * 3600 + minutes * 60 + seconds) {}
		Time(int hours, int minutes, int seconds) : value(hours * 3600 + minutes * 60 + seconds) {}
		Time(const Time& other) : value(other.value) {}
		Time() : value(0.f) {}

		operator double() const { return value; }

		_A_ double value;

		inline int days() { return int(value) / 86400; }
		inline int hours() { return int(value) % 86400 / 3600; }
		inline int minutes() { return int(value) % 3600 / 60; }
		inline int seconds() { return int(value) % 60; }

		static Type& cls() { static Type ty; return ty; }
	};

	class MK_OBJECT_EXPORT _I_ TimeSpan : public Struct
	{
	public:
		_C_ TimeSpan(Time s, Time e) : start(s), end(e) {}
		TimeSpan(int sh, int eh) : start(0, sh, 0, 0), end(0, eh, 0, 0) {}
		TimeSpan() : start(), end() {}

		Time operator [](size_t i) const { return i == 0 ? start : end; }
		Time& operator [](size_t i) { return i == 0 ? start : end; }

		_A_ Time start;
		_A_ Time end;

		static Type& cls() { static Type ty; return ty; }
	};

	class MK_OBJECT_EXPORT Timer
    {
	public:
		static Timer& me() { return sInstance; }

	private:
		static Timer sInstance;

    public:
        Timer();
        ~Timer();

		void firstUpdate(void* updater);
        void update(void* updater);
        double read(void* updater);
		double step(void* updater);

    private:
        typedef std::map<void*, clock_t> TimeTable;
        TimeTable m_timeTable;
    };

	class MK_OBJECT_EXPORT Clock
    {
    public:
		Clock();
        ~Clock();

		void update();
        double read();
		double step();

		size_t readTick();
		size_t stepTick();

    private:
        clock_t m_last;
		size_t m_lastTick;
    };

//	template <> inline void fromString(const string& str, TimeSpan& vec) { string_to_fixed_vector<TimeSpan, float>(str, vec); }
//	template <> inline string toString(const TimeSpan& val) { return fixed_vector_to_string<TimeSpan, 2>(val); }
}

#endif // MK_TIMER_H_INCLUDED
