//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INPUT_H_INCLUDED
#define MK_INPUT_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkFValue.h>
#include <Ui/Widget/mkWSlider.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	template <class T>
	class FInput : public FValue, public Typed<FInput<T>>
	{
	public:
		FInput(Lref& value, bool edit = true)
			: FValue(value, nullptr, edit)
		{
			mType = cls();
			mScheme.setMapper([this]() { return make_unique<WInput<T>>(mLref); });
			setLabel(this->toString());
		}

		FInput(T value, std::function<void(T)> callback = nullptr)
			: FValue(lref(value), nullptr)
		{
			mType = cls();
			mScheme.setMapper([this, callback]() { return make_unique<WInput<T>>(mLref, callback); });
		}

		using Typed<FInput<T>>::cls;
	};

	template class MK_UI_EXPORT FInput<int>;
	template class MK_UI_EXPORT FInput<float>;
	template class MK_UI_EXPORT FInput<double>;
	template class MK_UI_EXPORT FInput<bool>;
	template class MK_UI_EXPORT FInput<string>;

	template <class T>
	class FStat : public FValue, public Typed<FStat<T>>
	{
	public:
		FStat(Lref& value, bool edit = true)
			: FValue(value, nullptr, edit)
		{
			mType = cls();
			mScheme.setMapper([this]() { return make_unique<WStatSlider<T>>(mLref); });
		}

		FStat(AutoStat<T> value, std::function<void(T)> callback = nullptr)
			: FValue(lref(value), nullptr)
		{
			mType = cls();
			mScheme.setMapper([this, callback]() { return make_unique<WStatSlider<T>>(mLref, callback); });
		}

		using Typed<FStat<T>>::cls;
	};

	template class MK_UI_EXPORT FStat<int>;
	template class MK_UI_EXPORT FStat<float>;

	class MK_UI_EXPORT InputInt : public Form, public Styled<InputInt>
	{
	public:
		InputInt(const string& label, int value, std::function<void(int)> callback = nullptr);
	};

	class MK_UI_EXPORT InputFloat : public Form, public Styled<InputFloat>
	{
	public:
		InputFloat(const string& label, float value, std::function<void(float)> callback = nullptr);
	};

	class MK_UI_EXPORT InputBool : public Form, public Styled<InputBool>
	{
	public:
		InputBool(const string& label, bool value, std::function<void(bool)> callback = nullptr);
	};

	class MK_UI_EXPORT InputText : public Form, public Styled<InputText>
	{
	public:
		InputText(const string& label, const string& text, std::function<void(string)> callback = nullptr, bool reverse = false);
	};

	class MK_UI_EXPORT InputDropdown : public Form, public Styled<InputDropdown>
	{
	public:
		InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);
	};
	
	class MK_UI_EXPORT SliderInt : public Form, public Styled<SliderInt>
	{
	public:
		SliderInt(const string& label, AutoStat<int> value, std::function<void(int)> callback = nullptr);
	};

	class MK_UI_EXPORT SliderFloat : public Form, public Styled<SliderFloat>
	{
	public:
		SliderFloat(const string& label, AutoStat<float> value, std::function<void(float)> callback = nullptr);
	};
}

#endif // MK_INPUT_H_INCLUDED
