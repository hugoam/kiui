//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FVALUE_H_INCLUDED
#define MK_FVALUE_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT ValueForm : public HashDispatch<ValueForm, Form*, FValue*>
	{};

	class MK_UI_EXPORT FValue : public Form
	{
	public:
		FValue(Lref& lref, Style* style, bool edit = false, SchemeMapper mapper = nullptr);
		FValue(Lref&& lref, Style* style, bool edit = false, SchemeMapper mapper = nullptr);

		Lref& valref() { return mLref; }
		size_t update() { return mUpdate; }

		string toString();
		void setString(const string& value);

		virtual void updateValue();

	protected:
		Lref mValue;
		Lref& mLref;
		size_t mUpdate;
		bool mEdit;
	};
}

#endif // MK_FVALUE_H_INCLUDED
