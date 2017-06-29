//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FVALUE_H
#define TOY_FVALUE_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/Any.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

#include <toyobj/Util/Stat.h>
#include <toyobj/Util/Dispatch.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT Value : public NonCopy
	{
	public:
		using OnUpdate = std::function<void(Lref&)>;

	public:
		Value(Lref& lref, const OnUpdate& onUpdate = OnUpdate(), bool edit = false);
		Value(Lref&& lref, const OnUpdate& onUpdate = OnUpdate(), bool edit = false);

		Lref& value() { return m_value; }
		size_t update() { return m_update; }

		void onUpdate(const OnUpdate& handler) { m_onUpdate = handler; }

		string getString();
		void setString(const string& value);

		void triggerUpdate();
		void triggerModify();

		virtual void notifyUpdate() {}
		virtual void notifyModify() {}

		template <class T>
		void modifyValue(T val) { m_value.value<T>() = val; this->triggerModify(); }

		template <class T>
		void updateValue(T val) { m_value.value<T>() = val; this->triggerUpdate(); }

	protected:
		Lref m_copy;
		Lref& m_value;
		size_t m_update;
		bool m_edit;

		OnUpdate m_onUpdate;
	};

	class _refl_ TOY_UI_EXPORT WValue : public Wedge, public Value
	{
	public:
		WValue(Wedge& parent, Lref& lref, Type& type, const OnUpdate& onUpdate, bool edit = false);
		WValue(Wedge& parent, Lref&& lref, Type& type, const OnUpdate& onUpdate, bool edit = false);

		string getString();

		void notifyUpdate();

		static Type& cls() { static Type ty("WValue", Wedge::WrapControl()); return ty; }
	};
}

#endif // TOY_FVALUE_H
