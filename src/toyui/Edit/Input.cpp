//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/Input.h>

#include <toyui/Button/Image.h>

namespace toy
{
	template <class T_Val, class T_Widget>
	object_ptr<Widget> valueWidget(Lref& lref, T_Val& val, Lref& parent)
	{ 
		UNUSED(val);
		if(lref.mode() == VALUE)
			return make_object<T_Widget>(parent.ref<Wedge>(), T_Val(lref.any<T_Val>()));
		else // if(lref.mode() == REF)
			return make_object<T_Widget>(parent.ref<Wedge>(), lref.any<T_Val>());
	}

	template <class T_Val, class T_Widget>
	object_ptr<Widget> statValueWidget(Lref& lref, T_Val& val, Lref& parent) { UNUSED(lref); return make_object<T_Widget>(parent.ref<Wedge>(), AutoStat<T_Val>(val, StatDef<T_Val>())); }
	
	class TOY_UI_EXPORT InputDispatch : public Global<InputDispatch>
	{
	public:
		InputDispatch()
		{
			DispatchInput::me().singleBranch<bool, valueWidget<bool, Input<bool>>>();
			DispatchInput::me().singleBranch<unsigned int, statValueWidget<unsigned int, Input<unsigned int>>>();
			DispatchInput::me().singleBranch<int, statValueWidget<int, Input<int>>>();
			DispatchInput::me().singleBranch<float, statValueWidget<float, Input<float>>>();
			DispatchInput::me().singleBranch<double, statValueWidget<double, Input<double>>>();
			DispatchInput::me().singleBranch<string, valueWidget<string, Input<string>>>();

			DispatchInput::me().singleBranch<AutoStat<int>, valueWidget<AutoStat<int>, StatSlider<int>>>();
			DispatchInput::me().singleBranch<AutoStat<float>, valueWidget<AutoStat<float>, StatSlider<float>>>();

			DispatchInput::me().singleBranch<Image256, valueWidget<Image256, Figure>>();
		}
	};
}
