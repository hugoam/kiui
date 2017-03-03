//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/Input.h>

#include <toyobj/Object.h>
#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

#include <toyui/Button/Dropdown.h>
#include <toyui/Button/Typedown.h>
#include <toyui/Button/RadioButton.h>

#include <toyui/Edit/TypeIn.h>

using namespace std::placeholders;

namespace toy
{
	InputRadio::InputRadio(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: WrapControl(parent, cls())
		, m_label(*this, label)
		, m_input(*this, [callback](Widget& widget) { if(callback) callback(widget.label()); }, 0, choices)
	{
		if(reverse)
			this->swap(0, 1);
	}

	InputDropdown::InputDropdown(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback, bool reverse)
		: WrapControl(parent, cls())
		, m_label(*this, label)
		, m_input(*this, [callback](Widget& widget) { if(callback) callback(widget.label()); }, choices)
	{
		if(reverse)
			this->swap(0, 1);
	}

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> valueWidget(Lref& parent, Lref& lref, T_Val val) { UNUSED(parent); UNUSED(val); return make_unique<T_Widget>(parent->as<Wedge>(), lref); }

	template <class T_Val, class T_Widget>
	unique_ptr<WValue> statValueWidget(Lref& parent, Lref& valref, T_Val& val) { UNUSED(parent); UNUSED(valref); return make_unique<T_Widget>(parent->as<Wedge>(), AutoStat<T_Val>(val, StatDef<T_Val>())); }
	
	template class Dispatch<DispatchInput, bool&, valueWidget<bool&, Input<bool>>>;
	template class Dispatch<DispatchInput, unsigned int&, statValueWidget<unsigned int, Input<unsigned int>>>;
	template class Dispatch<DispatchInput, int&, statValueWidget<int, Input<int>>>;
	template class Dispatch<DispatchInput, float&, statValueWidget<float, Input<float>>>;
	template class Dispatch<DispatchInput, double&, statValueWidget<double, Input<double>>>;
	template class Dispatch<DispatchInput, string&, valueWidget<string&, Input<string>>>;

	template class Dispatch<DispatchInput, AutoStat<int>&, valueWidget<AutoStat<int>&, StatSlider<float>>>;
	template class Dispatch<DispatchInput, AutoStat<float>&, valueWidget<AutoStat<float>&, StatSlider<float>>>;
}
