//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INPUT_H_INCLUDED
#define MK_INPUT_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
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
	class MK_UI_EXPORT FInt : public FValue, public Typed<FInt>
	{
	public:
		FInt(Lref& value, bool edit = true);
		FInt(int value);

		void updateValue();

		using Typed<FInt>::cls;
	};

	class MK_UI_EXPORT FFloat : public FValue, public Typed<FFloat>
	{
	public:
		FFloat(Lref& value, bool edit = true);
		FFloat(float value);

		void updateValue();

		using Typed<FFloat>::cls;
	};

	template <class T>
	class FStat : public FValue, public Typed<FStat<T>>
	{
	public:
		FStat(Lref& value, bool edit = true)
			: FValue(value, nullptr, edit)
		{
			mType = cls();
			mScheme.setMapper([this]() { return make_unique<WStatSlider<T>>(this, this->valref()->ref<AutoStat<T>>()); });
		}

		FStat(AutoStat<T> value)
			: FValue(lref(value), nullptr)
		{
			mType = cls();
			mScheme.setMapper([this]() { return make_unique<WStatSlider<T>>(this, this->valref()->ref<AutoStat<T>>()); });
		}

		using Typed<FStat<T>>::cls;
	};

	template class MK_UI_EXPORT FStat<int>;
	template class MK_UI_EXPORT FStat<float>;

	class MK_UI_EXPORT FBool : public FValue, public Typed<FBool>
	{
	public:
		FBool(Lref& value, bool edit = true);
		FBool(bool value);

		using Typed<FBool>::cls;
	};

	class MK_UI_EXPORT FString : public FValue, public Typed<FString>
	{
	public:
		FString(Lref& value, bool edit = true);
		FString(string value);

		using Typed<FString>::cls;
	};

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
		InputBool(const string& label, bool value, std::function<void(void)> on = nullptr, std::function<void(void)> off = nullptr);
	};

	class MK_UI_EXPORT InputText : public Form, public Styled<InputText>
	{
	public:
		InputText(const string& label, const string& text, std::function<void(const string&)> callback = nullptr, bool reverse = false);
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
