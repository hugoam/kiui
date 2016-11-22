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
		StatDef(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(), T step = T(1))
			: m_min(min)
			, m_max(max)
			, m_step(step)
		{}

		inline T min() const { return m_min; }
		inline T max() const { return m_max; }
		inline T step() const { return m_step; }

		T rincrement(T& value, T amount) const { T diff = std::min(m_max - value, amount); value += diff; update(value); return diff; }
		T rdecrement(T& value, T amount) const { T diff = std::max(-m_min + value, amount); value -= diff; update(value); return diff; }
		void increment(T& value, T amount) const { value += amount; update(value); }
		void decrement(T& value, T amount) const { value -= amount; update(value); }

		void increment(T& value) const { value += m_step; update(value); }
		void decrement(T& value) const { value -= m_step; update(value); }

		void multiply(T& value, T& base, T multiplier) const { T diff = value - base; base *= multiplier; value = base + diff; update(value); }
		
		void modify(T& value, T& base, T val) const { value += val - base; base = value; update(value); }
		void modify(T& value, T val) const { value = val; update(value); }

		void update(T& value) const
		{
			if(value < m_min)
				value = m_min;
			if(value > m_max)
				value = m_max;
		}

		static Type& cls() { static Type ty; return ty; }

	protected:
		T m_min;
		T m_max;
		T m_step;
	};

	template <class T>
	class Stat
	{
	public:
		Stat(T base = T())
			: m_base(base)
			, m_value(base)
			//, m_updateHandlers()
		{}

		operator T() const { return m_value; }

		inline T base() const { return m_base; }
		inline T value() const { return m_value; }

		void setModifier(const StatDef<T>& def, void* owner, T amount)
		{
			m_value += amount;

			m_modifiers[owner] = amount;
			def.update(m_value);
		}

		void updateModifier(const StatDef<T>& def, void* owner, T amount)
		{
			m_value -= m_modifiers[owner];
			m_value += amount;

			m_modifiers[owner] = amount;
			def.update(m_value);
		}

		void removeModifier(const StatDef<T>& def, void* owner)
		{
			m_value += m_modifiers[owner];
			m_modifiers.erase(owner);
			def.update(m_value);
		}

		//void addUpdateHandler(const StatObserver<T>& handler) { m_updateHandlers.push_back(handler); handler(this, m_value); }

		virtual const StatDef<T>& vdef() const = 0;

	protected:
		T m_base;
		T m_value;

		//std::vector<StatObserver<T>> m_updateHandlers;

		typedef std::map<void*, T> ModifierMap;
		ModifierMap m_modifiers;
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

		inline void modify(T value) { self()->def().modify(this->m_value, this->m_base, value); }

		inline T rincrement(T amount) { return self()->def().rincrement(this->m_value, amount); }
		inline T rdecrement(T amount) { return self()->def().rdecrement(this->m_value, amount); }
		inline void increment(T amount) { self()->def().increment(this->m_value, amount); }
		inline void decrement(T amount) { self()->def().decrement(this->m_value, amount); }

		inline void increment() { self()->def().increment(this->m_value); }
		inline void decrement() { self()->def().increment(this->m_value); }

		inline void multiply(T multiplier) { self()->def().multiply(this->m_value, this->m_base, multiplier); }
		
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
		AutoStat(T value = T(), T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max(), T step = T(1))
			: m_value(value)
			, m_valueRef(m_value)
			, m_def(min, max, step)
		{}

		AutoStat(T& value, const StatDef<T>& def)
			: m_value()
			, m_valueRef(value)
			, m_def(def)
		{}

		AutoStat(const AutoStat& other)
			: m_value(other.m_value)
			, m_valueRef(&other.m_value == &other.m_valueRef ? m_value : other.m_valueRef)
			, m_def(other.m_def)
		{}

		AutoStat& operator=(const AutoStat& other)
		{
			m_value = other.m_value;
			m_valueRef = other.m_valueRef;
			m_def = other.m_def;
			return *this;
		}

		operator T() const { return m_valueRef; }

		inline T value() const { return m_valueRef; }

		inline T min() const { return m_def.min(); }
		inline T max() const { return m_def.max(); }
		inline T step() const { return m_def.step(); }

		inline void modify(T value) { m_def.modify(m_valueRef, value); }

		inline void increment() { m_def.increment(m_valueRef); }
		inline void decrement() { m_def.decrement(m_valueRef); }

		const StatDef<T>& vdef() const { return m_def; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		T m_value;
		T& m_valueRef;
		StatDef<T> m_def;
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
