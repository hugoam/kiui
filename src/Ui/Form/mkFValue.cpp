//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkFValue.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkWTypeIn.h>
#include <Ui/Widget/mkWSlider.h>

using namespace std::placeholders;

namespace mk
{
	FValue::FValue(Lref& value, const string& cls, bool edit)
		: Form(edit ? cls + " value input" : cls + " value", "")
		, mLref(value)
		, mUpdate(0)
		, mEdit(edit)
	{
		if(edit)
			mAttrs["edit"] = "true";
	}

	FValue::FValue(Lref&& value, const string& cls, bool edit)
		: Form(edit ? cls + " value input" : cls + " value", "")
		, mValue(value)
		, mLref(mValue)
		, mUpdate(0)
		, mEdit(edit)
	{
		if(edit)
			mAttrs["edit"] = "true";
	}

	void FValue::nextFrame(size_t tick, size_t delta)
	{
		Form::nextFrame(tick, delta);

		if(mLref->update() > mUpdate)
			this->updateValue();
	}

	void FValue::updateValue()
	{
		mUpdate = mLref->update();
		mWidget->markDirty();
		//this->updated();
	}

	string FValue::toString()
	{
		return mLref->getString();
	}

	void FValue::setString(const string& value)
	{
		mLref->setString(value);
	}

	FInt::FInt(Lref& value, bool edit)
		: FValue(value, "int", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WInt>(this); });
		setLabel(this->toString());
	}

	FInt::FInt(int value)
		: FValue(lref(value), "int")
	{
		mScheme.setMapper([this]() { return make_unique<WInt>(this); });
	}

	void FInt::updateValue()
	{
		setLabel(this->toString());
		FValue::updateValue();
	}
	
	FFloat::FFloat(Lref& value, bool edit)
		: FValue(value, "float", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WFloat>(this); });
		setLabel(this->toString());
	}

	FFloat::FFloat(float value)
		: FValue(lref(value), "int")
	{
		mScheme.setMapper([this]() { return make_unique<WFloat>(this); });
	}

	void FFloat::updateValue()
	{
		setLabel(this->toString());
		FValue::updateValue();
	}

	FIntStat::FIntStat(Lref& value, bool edit)
		: FValue(value, "intstat", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WIntSlider>(this); });
	}
	
	FIntStat::FIntStat(Stat<int> value)
		: FValue(lref(value), "intstat")
	{
		mScheme.setMapper([this]() { return make_unique<WIntSlider>(this); });
	}

	FFloatStat::FFloatStat(Lref& value, bool edit)
		: FValue(value, "floatstat", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WFloatSlider>(this); });
	}

	FFloatStat::FFloatStat(Stat<float> value)
		: FValue(lref(value), "floatstat")
	{
		mScheme.setMapper([this]() { return make_unique<WFloatSlider>(this); });
	}

	FBool::FBool(Lref& value, bool edit)
		: FValue(value, "bool", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WBool>(this); });
		setLabel(this->toString());
	}

	FBool::FBool(bool value)
		: FValue(lref(value), "bool")
	{
		mScheme.setMapper([this]() { return make_unique<WBool>(this); });
	}

	FString::FString(Lref& value, bool edit)
		: FValue(value, "string", edit)
	{
		mScheme.setMapper([this]() { return make_unique<WString>(this); });
		setLabel(this->toString());
	}
	
	FString::FString(string value)
		: FValue(lref(value), "string")
	{
		mScheme.setMapper([this]() { return make_unique<WString>(this); });
	}

	InputInt::InputInt(const string& label, int value, std::function<void(int)> callback)
		: Form("intinput")
	{
		this->makeappend<FInt>(value);
		this->makeappend<Label>("", label);
	}

	InputFloat::InputFloat(const string& label, float value, std::function<void(float)> callback)
		: Form("floatinput")
	{
		this->makeappend<FFloat>(value);
		this->makeappend<Label>("", label);
	}

	InputBool::InputBool(const string& label, bool value, std::function<void()> on, std::function<void()> off)
		: Form("boolinput")
	{
		this->makeappend<FBool>(value);
		this->makeappend<Label>("", label);
	}

	InputText::InputText(const string& label, const string& text, std::function<void(string)> callback, bool reverse)
		: Form("textinput")
	{
		this->makeappend<FString>(text);
		this->makeappend<Label>("", label);

		if(reverse)
			this->move(0, 1);
	}

	InputDropdown::InputDropdown(const string& label, StringVector choices, std::function<void(string)> callback, bool reverse)
		: Form("dropdowninput")
	{
		this->makeappend<Dropdown>(callback, choices);
		this->makeappend<Label>("", label);

		if(reverse)
			this->move(0, 1);
	}

	SliderInt::SliderInt(const string& label, Stat<int> value, std::function<void(int)> callback)
		: Form("sliderint")
	{
		this->makeappend<FIntStat>(value),
		this->makeappend<Label>("", label);
	}

	SliderFloat::SliderFloat(const string& label, Stat<float> value, std::function<void(float)> callback)
		: Form("sliderfloat")
	{
		this->makeappend<FFloatStat>(value);
		this->makeappend<Label>("", label);
	}

	//unique_ptr<Form> dispatchStoreForm(Form* member, Lref& lref, Stock* store) { return make_unique<FStore>(member, member->as<FMember>()->dmember()); }

	template <class T_Val, class T_Form>
	Form* dispatchValueForm(Form* parent, Lref& lref, T_Val val) { UNUSED(val); return parent->makeappend<T_Form>(lref); }

	//template class Dispatch<ObjectForm, Stock*, dispatchStoreForm>;

	template class Dispatch<ValueForm, bool&, dispatchValueForm<bool&, FBool>>;
	template class Dispatch<ValueForm, unsigned int&, dispatchValueForm<unsigned int&, FInt>>;
	template class Dispatch<ValueForm, int&, dispatchValueForm<int&, FInt>>;
	template class Dispatch<ValueForm, double&, dispatchValueForm<double&, FFloat>>;
	template class Dispatch<ValueForm, float&, dispatchValueForm<float&, FFloat>>;
	template class Dispatch<ValueForm, string&, dispatchValueForm<string&, FString>>;
}
