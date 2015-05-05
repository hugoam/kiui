//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FVALUE_H_INCLUDED
#define MK_FVALUE_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Widget/mkSheet.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT ValueWidget : public HashDispatch<ValueWidget, Sheet*, WValue&>
	{};

	class MK_UI_EXPORT Value : public NonCopy
	{
	public:
		Value(Lref& lref, bool edit = false);
		Value(Lref&& lref, bool edit = false);

		Lref& value() { return mValue; }
		size_t update() { return mUpdate; }

		string getString();
		void setString(const string& value);

		void triggerUpdate();
		void triggerModify();

		virtual void notifyUpdate() {}
		virtual void notifyModify() {}

		template <class T>
		void modifyValue(T val) { mValue->set<T>(val); this->triggerModify(); }

		template <class T>
		void updateValue(T val) { mValue->set<T>(val); this->triggerUpdate(); }

	protected:
		Lref mCopy;
		Lref& mValue;
		size_t mUpdate;
		bool mEdit;
	};

	class MK_UI_EXPORT WValue : public Sheet, public Value
	{
	public:
		WValue(Lref& lref, bool edit = false);
		WValue(Lref&& lref, bool edit = false);

		void notifyUpdate();

		static StyleType& cls() { static StyleType ty("WValue", Sheet::cls()); return ty; }
	};
}

#endif // MK_FVALUE_H_INCLUDED
