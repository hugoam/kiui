//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STAT_H_INCLUDED
#define MK_STAT_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/mkObjectForward.h>
#include <Object/Util/mkGlobalType.h>

/* Standard */
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <cfloat>

namespace mk
{
	template <class T>
	class StatDef : public Struct
	{
	public:
		StatDef(T min = T(), T max = T(), T step = T())
			: mMin(min)
			, mMax(max)
			, mStep(step)
		{}

		inline T min() const { return mMin; }
		inline T max() const { return mMax; }
		inline T step() const { return mStep; }

		T rincrement(T& value, T amount) const { T diff = std::min(mMax - value, amount); value += diff; update(value); return diff; }
		T rdecrement(T& value, T amount) const { T diff = std::max(-mMin + value, amount); value -= diff; update(value); return diff; }
		void increment(T& value, T amount) const { value += amount; update(value); }
		void decrement(T& value, T amount) const { value -= amount; update(value); }

		void increment(T& value) const { value += mStep; update(value); }
		void decrement(T& value) const { value -= mStep; update(value); }

		void multiply(T& value, T& base, T multiplier) const { T diff = value - base; base *= multiplier; value = base + diff; update(value); }
		
		void modify(T& value, T& base, T val) const { value += val - base; base = value; update(value); }
		void modify(T& value, T val) const { value = val; update(value); }

		void update(T& value) const
		{
			if(value < mMin)
				value = mMin;
			if(value > mMax)
				value = mMax;
		}

		static Type& cls() { static Type ty; return ty; }

	protected:
		T mMin;
		T mMax;
		T mStep;
	};

	template <class T>
	class Stat
	{
	public:
		Stat(T base = T())
			: mBase(base)
			, mValue(base)
			//, mUpdateHandlers()
		{}

		operator T() const { return mValue; }

		inline T base() const { return mBase; }
		inline T value() const { return mValue; }

		void setModifier(const StatDef<T>& def, void* owner, T amount)
		{
			mValue += amount;

			mModifiers[owner] = amount;
			def.update(mValue);
		}

		void updateModifier(const StatDef<T>& def, void* owner, T amount)
		{
			mValue -= mModifiers[owner];
			mValue += amount;

			mModifiers[owner] = amount;
			def.update(mValue);
		}

		void removeModifier(const StatDef<T>& def, void* owner)
		{
			mValue += mModifiers[owner];
			mModifiers.erase(owner);
			def.update(mValue);
		}

		//void addUpdateHandler(const StatObserver<T>& handler) { mUpdateHandlers.push_back(handler); handler(this, mValue); }

		virtual const StatDef<T>& vdef() const = 0;

	protected:
		T mBase;
		T mValue;

		//std::vector<StatObserver<T>> mUpdateHandlers;

		typedef std::map<void*, T> ModifierMap;
		ModifierMap mModifiers;
	};

	template <class T, class T_Def>
	class DefStat : public Stat<T>
	{
	public:
		DefStat(T base = T())
			: Stat<T>(base)
		{}

		const T_Def* self() const { return static_cast<const T_Def*>(this); }

		const StatDef<T>& vdef() const { return self()->def(); }

		inline T min() const { return self()->def().min(); }
		inline T max() const { return self()->def().max(); }
		inline T step() const { return self()->def().step(); }

		inline void modify(T value) { self()->def().modify(this->mValue, this->mBase, value); }

		inline T rincrement(T amount) { return self()->def().rincrement(this->mValue, amount); }
		inline T rdecrement(T amount) { return self()->def().rdecrement(this->mValue, amount); }
		inline void increment(T amount) { self()->def().increment(this->mValue, amount); }
		inline void decrement(T amount) { self()->def().decrement(this->mValue, amount); }

		inline void increment() { self()->def().increment(this->mValue); }
		inline void decrement() { self()->def().increment(this->mValue); }

		inline void multiply(T multiplier) { self()->def().multiply(this->mValue, this->mBase, multiplier); }
		
		inline void setModifier(void* owner, T amount) { Stat<T>::setModifier(self()->def(), owner, amount); }
		inline void updateModifier(void* owner, T amount) { Stat<T>::updateModifier(self()->def(), owner, amount); }
		inline void removeModifier(void* owner) { Stat<T>::removeModifier(self()->def(), owner); }
	};

	template <class T, class T_Def, const char* T_Name>
	class TNamedStat : public DefStat<T, T_Def>
	{
	public:
		TNamedStat(T base = T())//, const StatObserver<T>& handler = nullptr)
			: DefStat<T, T_Def>(base)
		{}

		const string name() { return T_Name; }
	};

	template <class T>
	class AutoStat : public Struct
	{
	public:
		AutoStat(T value = T(), T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(), T step = T())
			: mValue(value)
			, mValueRef(mValue)
			, mDef(min, max, step)
		{}

		AutoStat(T& value, const StatDef<T>& def)
			: mValue()
			, mValueRef(value)
			, mDef(def)
		{}

		AutoStat(const AutoStat& other)
			: mValue(other.mValue)
			, mValueRef(&other.mValue == &other.mValueRef ? mValue : other.mValueRef)
			, mDef(other.mDef)
		{}

		AutoStat& operator=(const AutoStat& other)
		{
			mValue = other.mValue;
			mValueRef = other.mValueRef;
			mDef = other.mDef;
			return *this;
		}

		operator T() const { return mValueRef; }

		inline T value() const { return mValueRef; }

		inline T min() const { return mDef.min(); }
		inline T max() const { return mDef.max(); }
		inline T step() const { return mDef.step(); }

		inline void modify(T value) { mDef.modify(mValueRef, value); }

		inline void increment() { mDef.increment(mValueRef); }
		inline void decrement() { mDef.decrement(mValueRef); }

		const StatDef<T>& vdef() const { return mDef; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		T mValue;
		T& mValueRef;
		StatDef<T> mDef;
	};

	template class MK_OBJECT_EXPORT AutoStat<int>;
	template class MK_OBJECT_EXPORT AutoStat<float>;

	class MK_OBJECT_EXPORT _I_ _S_ Ratio : public Struct, public DefStat<float, Ratio>
	{
	public:
		_C_ Ratio(float value = 0.f) : DefStat<float, Ratio>(value) {}
		Ratio(const Ratio&) = default;
		Ratio& operator=(const Ratio&) = default;

		_A_ _M_ float value() const { return DefStat<float, Ratio>::value(); }
		void setValue(float value) { DefStat<float, Ratio>::modify(value); }

		const StatDef<float>& def() const { static StatDef<float> df(0.f, 1.f, 0.01f); return df; }

		static Type& cls() { static Type ty; return ty; }
	};

	class MK_OBJECT_EXPORT _I_ _S_ Gauge : public Struct, public DefStat<float, Gauge>
	{
	public:
		_C_ Gauge(float value = 0.f) : DefStat<float, Gauge>(value) {}
		Gauge(const Gauge&) = default;
		Gauge& operator=(const Gauge&) = default;

		_A_ _M_ float value() const { return DefStat<float, Gauge>::value(); }
		void setValue(float value) { DefStat<float, Gauge>::modify(value); }

		const StatDef<float>& def() const { static StatDef<float> df(0.f, FLT_MAX, 1.f); return df; }

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // MK_STAT_H_INCLUDED
