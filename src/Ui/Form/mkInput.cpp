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
	InputInt::InputInt(const string& label, int value, std::function<void(int)> callback)
		: Form(styleCls())
	{
		this->makeappend<FInput<int>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputFloat::InputFloat(const string& label, float value, std::function<void(float)> callback)
		: Form(styleCls())
	{
		this->makeappend<FInput<float>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputBool::InputBool(const string& label, bool value, std::function<void(bool)> callback)
		: Form(styleCls())
	{
		this->makeappend<FInput<bool>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputText::InputText(const string& label, const string& text, std::function<void(string)> callback, bool reverse)
		: Form(styleCls())
	{
		this->makeappend<FInput<string>>(text, callback);
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
		this->makeappend<FStat<int>>(value, callback),
		this->makeappend<Label>(label);
	}

	SliderFloat::SliderFloat(const string& label, AutoStat<float> value, std::function<void(float)> callback)
		: Form(styleCls())
	{
		this->makeappend<FStat<float>>(value, callback);
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
			AutoStat<BareType<T_Val>::type> stat(val, parent->getAttr("stat")->get<StatDef<typename BareType<T_Val>::type>>());
			return parent->makeappend<FStat<typename BareType<T_Val>::type>>(stat);
		}
		else
		{
			return valueForm<T_Val, T_Form>(parent, valref, val);
		}
	}

	//template class Dispatch<ObjectForm, Stock*, dispatchStoreForm>;

	template class Dispatch<ValueForm, bool&, valueForm<bool&, FInput<bool>>>;
	template class Dispatch<ValueForm, unsigned int&, valueForm<unsigned int&, FInput<int>>>;
	template class Dispatch<ValueForm, int&, statValueForm<int&, FInput<int>>>;
	template class Dispatch<ValueForm, float&, statValueForm<float&, FInput<float>>>;
	template class Dispatch<ValueForm, double&, valueForm<double&, FInput<double>>>;
	template class Dispatch<ValueForm, string&, valueForm<string&, FInput<string>>>;

	template class Dispatch<ValueForm, AutoStat<int>&, valueForm<AutoStat<int>&, FStat<float>>>;
	template class Dispatch<ValueForm, AutoStat<float>&, valueForm<AutoStat<float>&, FStat<float>>>;
}
