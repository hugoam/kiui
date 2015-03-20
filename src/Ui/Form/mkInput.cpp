//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkInput.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkWTypeIn.h>
#include <Ui/Widget/mkWSlider.h>

using namespace std::placeholders;

namespace mk
{
	FInt::FInt(Lref& value, bool edit)
		: FValue(value, nullptr, edit)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WInt>(this); });
		setLabel(this->toString());
	}

	FInt::FInt(int value)
		: FValue(lref(value), nullptr)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WInt>(this); });
	}

	void FInt::updateValue()
	{
		setLabel(this->toString());
		FValue::updateValue();
	}
	
	FFloat::FFloat(Lref& value, bool edit)
		: FValue(value, nullptr, edit)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WFloat>(this); });
		setLabel(this->toString());
	}

	FFloat::FFloat(float value)
		: FValue(lref(value), nullptr)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WFloat>(this); });
	}

	void FFloat::updateValue()
	{
		setLabel(this->toString());
		FValue::updateValue();
	}

	FBool::FBool(Lref& value, bool edit)
		: FValue(value, nullptr, edit)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WBool>(this); });
		setLabel(this->toString());
	}

	FBool::FBool(bool value)
		: FValue(lref(value), nullptr)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WBool>(this); });
	}

	FString::FString(Lref& value, bool edit)
		: FValue(value, nullptr, edit)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WString>(this); });
		setLabel(this->toString());
	}
	
	FString::FString(string value)
		: FValue(lref(value), nullptr)
	{
		mType = cls();
		mScheme.setMapper([this]() { return make_unique<WString>(this); });
	}

	InputInt::InputInt(const string& label, int value, std::function<void(int)> callback)
		: Form(styleCls())
	{
		this->makeappend<FInt>(value);
		this->makeappend<Label>(label);
	}

	InputFloat::InputFloat(const string& label, float value, std::function<void(float)> callback)
		: Form(styleCls())
	{
		this->makeappend<FFloat>(value);
		this->makeappend<Label>(label);
	}

	InputBool::InputBool(const string& label, bool value, std::function<void()> on, std::function<void()> off)
		: Form(styleCls())
	{
		this->makeappend<FBool>(value);
		this->makeappend<Label>(label);
	}

	InputText::InputText(const string& label, const string& text, std::function<void(const string&)> callback, bool reverse)
		: Form(styleCls())
	{
		this->makeappend<FString>(text);
		this->makeappend<Label>(label);

		if(reverse)
			this->move(0, 1);
	}

	InputDropdown::InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: Form(styleCls())
	{
		this->makeappend<Dropdown>(callback, choices);
		this->makeappend<Label>(label);

		if(reverse)
			this->move(0, 1);
	}

	SliderInt::SliderInt(const string& label, AutoStat<int> value, std::function<void(int)> callback)
		: Form(styleCls())
	{
		this->makeappend<FStat<int>>(value),
		this->makeappend<Label>(label);
	}

	SliderFloat::SliderFloat(const string& label, AutoStat<float> value, std::function<void(float)> callback)
		: Form(styleCls())
	{
		this->makeappend<FStat<float>>(value);
		this->makeappend<Label>(label);
	}

	//unique_ptr<Form> dispatchStoreForm(Form* member, Lref& lref, Stock* store) { return make_unique<FStore>(member, member->as<FMember>()->dmember()); }

	template <class T_Val, class T_Form>
	FValue* valueForm(Form* parent, Lref& lref, T_Val val) { UNUSED(val); return parent->makeappend<T_Form>(lref); }

	template <class T_Val, class T_Form>
	FValue* statValueForm(Form* parent, Lref& valref, T_Val val)
	{
		if(parent->hasAttr("stat"))
		{
			AutoStat<BareType<T_Val>::type> stat(val, parent->getAttr("stat")->get<StatDef<BareType<T_Val>::type>>());
			return parent->makeappend<FStat<BareType<T_Val>::type>>(stat);
		}
		else
		{
			return valueForm<T_Val, T_Form>(parent, valref, val);
		}
	}

	//template class Dispatch<ObjectForm, Stock*, dispatchStoreForm>;

	template class Dispatch<ValueForm, bool&, valueForm<bool&, FBool>>;
	template class Dispatch<ValueForm, unsigned int&, valueForm<unsigned int&, FInt>>;
	template class Dispatch<ValueForm, int&, statValueForm<int&, FInt>>;
	template class Dispatch<ValueForm, float&, statValueForm<float&, FFloat>>;
	template class Dispatch<ValueForm, double&, valueForm<double&, FFloat>>;
	template class Dispatch<ValueForm, string&, valueForm<string&, FString>>;

	template class Dispatch<ValueForm, AutoStat<int>&, valueForm<AutoStat<int>&, FStat<float>>>;
	template class Dispatch<ValueForm, AutoStat<float>&, valueForm<AutoStat<float>&, FStat<float>>>;
}
