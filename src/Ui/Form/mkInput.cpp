//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkInput.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkSlider.h>

using namespace std::placeholders;

namespace mk
{
	InputInt::InputInt(const string& label, int value, std::function<void(int)> callback)
		: Sheet(styleCls())
	{
		this->makeappend<Input<int>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputFloat::InputFloat(const string& label, float value, std::function<void(float)> callback)
		: Sheet(styleCls())
	{
		this->makeappend<Input<float>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputBool::InputBool(const string& label, bool value, std::function<void(bool)> callback)
		: Sheet(styleCls())
	{
		this->makeappend<Input<bool>>(value, callback);
		this->makeappend<Label>(label);
	}

	InputText::InputText(const string& label, const string& text, std::function<void(string)> callback, bool reverse)
		: Sheet(styleCls())
	{
		this->makeappend<Input<string>>(text, callback);
		this->makeappend<Label>(label);

		//if(reverse)
		//	this->move(0, 1);
	}

	InputDropdown::InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: Sheet(styleCls())
	{
		this->makeappend<Dropdown>([callback](Widget* widget) { callback(widget->label()); }, choices);
		this->makeappend<Label>(label);

		//if(reverse)
		//	this->move(0, 1);
	}

	SliderInt::SliderInt(const string& label, AutoStat<int> value, std::function<void(int)> callback)
		: Sheet(styleCls())
	{
		this->makeappend<StatSlider<int>>(value, callback),
		this->makeappend<Label>(label);
	}

	SliderFloat::SliderFloat(const string& label, AutoStat<float> value, std::function<void(float)> callback)
		: Sheet(styleCls())
	{
		this->makeappend<StatSlider<float>>(value, callback);
		this->makeappend<Label>(label);
	}

	//unique_ptr<Form> dispatchStoreForm(Form* member, Lref& lref, Stock* store) { return make_unique<FStore>(member, member->as<FMember>()->dmember()); }

	template <class T_Val, class T_Widget>
	WValue* valueWidget(Sheet* parent, Lref& lref, T_Val val) { UNUSED(val); return parent->emplace<T_Widget>(lref); }

	template <class T_Val, class T_Widget>
	WValue* statValueWidget(Sheet* parent, Lref& valref, T_Val val)
	{
		/*if(parent->hasAttr("stat"))
		{
			AutoStat<typename BareType<T_Val>::type> stat(val, parent->getAttr("stat")->get<StatDef<typename BareType<T_Val>::type>>());
			return parent->makeappend<FStat<typename BareType<T_Val>::type>>(stat);
		}
		else
		{*/
			return valueWidget<T_Val, T_Widget>(parent, valref, val);
		//}
	}

	//template class Dispatch<ObjectForm, Stock*, dispatchStoreForm>;

	template class Dispatch<ValueWidget, bool&, valueWidget<bool&, Input<bool>>>;
	template class Dispatch<ValueWidget, unsigned int&, valueWidget<unsigned int&, Input<int>>>;
	template class Dispatch<ValueWidget, int&, statValueWidget<int&, Input<int>>>;
	template class Dispatch<ValueWidget, float&, statValueWidget<float&, Input<float>>>;
	template class Dispatch<ValueWidget, double&, valueWidget<double&, Input<double>>>;
	template class Dispatch<ValueWidget, string&, valueWidget<string&, Input<string>>>;

	template class Dispatch<ValueWidget, AutoStat<int>&, valueWidget<AutoStat<int>&, StatSlider<float>>>;
	template class Dispatch<ValueWidget, AutoStat<float>&, valueWidget<AutoStat<float>&, StatSlider<float>>>;
}
