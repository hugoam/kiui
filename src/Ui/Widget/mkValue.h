//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FVALUE_H
#define MK_FVALUE_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT Value : public NonCopy
	{
	public:
		typedef std::function<void(Lref&)> OnUpdate;

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
		void modifyValue(T val) { m_value->set<T>(val); this->triggerModify(); }

		template <class T>
		void updateValue(T val) { m_value->set<T>(val); this->triggerUpdate(); }

	protected:
		Lref m_copy;
		Lref& m_value;
		size_t m_update;
		bool m_edit;

		OnUpdate m_onUpdate;
	};

	class MK_UI_EXPORT WValue : public Sheet, public Value
	{
	public:
		WValue(Lref& lref, StyleType& type, const OnUpdate& onUpdate, bool edit = false);
		WValue(Lref&& lref, StyleType& type, const OnUpdate& onUpdate, bool edit = false);

		void notifyUpdate();

		static StyleType& cls() { static StyleType ty("WValue", Sheet::cls()); return ty; }
	};
}

#endif // MK_FVALUE_H
