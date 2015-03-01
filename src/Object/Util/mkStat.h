//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STAT_H_INCLUDED
#define MK_STAT_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/mkObjectForward.h>

/* Standard */
#include <functional>
#include <algorithm>
#include <vector>
#include <map>

namespace mk
{
	template <class T>
	class TStat;

	template<typename T>
	using StatObserver = std::function<void(TStat<T>* stat, T value)>;

	template <class T>
	class TStat
	{
	public:
		TStat(T base, T min, T max, const StatObserver<T>& handler = nullptr)
			: mBase(base)
			, mValue(base)
			, mMax(max)
			, mMin(min)
			, mUpdateHandlers()
		{
			if(handler) // @bug
				mUpdateHandlers.push_back(handler);
		}

		TStat()
			: mBase()
			, mValue()
			, mMax()
			, mMin()
			, mUpdateHandlers()
		{}

		TStat& operator=(const TStat& other)
		{
			mBase = other.mBase;
			mValue = other.mValue;
			mMax = other.mMax;
			mMin = other.mMin;
			return *this;
		}

		TStat(const TStat& other)
			: mBase(other.mBase)
			, mValue(other.mValue)
			, mMax(other.mMax)
			, mMin(other.mMin)
			, mUpdateHandlers()
		{}

		T base() const { return mBase; }
		T value() const { return mValue; }
		T max() const { return mMax; }
		T min() const { return mMin; }

		operator T() const { return mValue; }

		void addUpdateHandler(const StatObserver<T>& handler) { mUpdateHandlers.push_back(handler); handler(this, mValue); }

		T rincrement(T amount) { T diff = std::min(mMax - mValue, amount); mValue += diff; update(); return diff; }
		T rdecrement(T amount) { T diff = std::max(-mMin + mValue, amount); mValue -= diff; update(); return diff; }
		void increment(T amount) { mValue += amount; update(); }
		void decrement(T amount) { mValue -= amount; update(); }
		void multiply(T multiplier) { T diff = mValue - mBase; mBase*= multiplier; mValue = mBase + diff; update(); }

		void modify(T value) { mValue += value - mBase; mBase = value; }

		void update()
		{
			if(mMin && mValue < mMin)
				mValue = mMin;
			if(mMax && mValue > mMax)
				mValue = mMax;

			for(StatObserver<T>& handler : mUpdateHandlers)
				handler(this, mValue);
		}

		void setMax(T max) { mMax = max; update(); }
		void setMin(T min) { mMin = min; update(); }
		
		void setModifier(void* owner, T amount)
		{
			mValue += amount;

			mModifiers[owner] = amount;
			update();
		}

		void updateModifier(void* owner, T amount)
		{
			mValue -= mModifiers[owner];
			mValue += amount;

			mModifiers[owner] = amount;
			update();
		}

		void removeModifier(void* owner)
		{
			mValue += mModifiers[owner];
			mModifiers.erase(owner);
			update();
		}

	protected:
		T mBase;
		T mValue;
		T mMin;
		T mMax;

		std::vector<StatObserver<T>> mUpdateHandlers;

		typedef std::map<void*, T> ModifierMap;
		ModifierMap mModifiers;
	};

	template <class T, const char* T_Name>
	class TNamedStat : public TStat<T>
	{
	public:
		TNamedStat(T base, T min, T max, const StatObserver<T>& handler = nullptr)
			: TStat<T>(base, min, max)
		{}

		const string& name() { return T_Name; }
	};

	template <class T>
	class Stat
	{};

	template <>
	class _I_ _S_ Stat<float> : public Struct, public Typed<Stat<float>>, public TStat<float>
	{
	public:
		_C_ Stat(float value = 0.f, float min = 0.f, float max = 10.f) : TStat<float>(value, min, max) {}
		Stat(const Stat<float>&) = default;
		Stat<float>& operator=(const Stat<float>&) = default;

		_A_ _M_ float value() const { return TStat<float>::value(); }
		_A_ float min() const { return TStat<float>::min(); }
		_A_ float max() const { return TStat<float>::max(); }
		
		void setValue(float value) { TStat<float>::modify(value); }
	};

	template <>
	class _I_ _S_ Stat<int> : public Struct, public Typed<Stat<int>>, public TStat<int>
	{
	public:
		_C_ Stat(int value = 0, int min = 0, int max = 10) : TStat<int>(value, min, max) {}
		Stat(const Stat<int>&) = default;
		Stat<int>& operator=(const Stat<int>&) = default;

		_A_ _M_ int value() const { return TStat<int>::value(); }
		_A_ int min() const { return TStat<int>::min(); }
		_A_ int max() const { return TStat<int>::max(); }

		void setValue(int value) { TStat<int>::modify(value); }
	};

	template class MK_OBJECT_EXPORT Stat<int>;
	template class MK_OBJECT_EXPORT Stat<float>;
}

#endif // MK_STAT_H_INCLUDED
