//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#define TOY_WIDGET_STATES_CONVERT_IMPL

#include <toyui/Config.h>
#include <toyui/Style/Style.h>

#include <toyobj/Reflect/Meta.h>
#include <toyui/Generated/Meta.h>
#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>

#include <toyui/Edit/Input.h>

namespace toy
{
	static void init_options(Ref object, Options& options)
	{
		for(size_t i = 0; i < options.m_fields.size(); ++i)
			if(!options.m_fields[i].none())
				object.meta().m_members[i].set(object, options.m_fields[i]);
	}

	Style::Style(const string& name, Type* type, Style* base, Args args)
		: m_style_type(type)
		, m_base(base)
		, m_name(name)
		, m_layout()
		, m_skins()
		, m_defined(false)
	{
		Widget::s_styles[name] = this;

		if(base)
			m_layout = base->m_layout;

		init_members(&m_layout, args);
		init_members(&m_skin, args);
	}

	void Style::load(Style& style, StyleMap& layout_defs, StyleMap& skin_defs)
	{
		if(style.m_base)
			this->load(*style.m_base, layout_defs, skin_defs);
		
		init_options(&m_layout, layout_defs[style.m_name]);
		init_options(&m_skin, skin_defs[style.m_name]);

		for(auto& kv : skin_defs)
			if(kv.first.find(style.m_name + ":") == 0)
			{
				WidgetStates states = fromString<WidgetStates>(splitString(kv.first, ":")[1]);
				InkStyle& skin = decline_skin(states);
				init_options(&skin, skin_defs[style.m_name]);
				init_options(&skin, skin_defs[kv.first]);
			}
	}

	void Style::load(StyleMap& layout_defs, StyleMap& skin_defs)
	{
		if(m_defined) return;

		if(m_base)
			m_base->load(layout_defs, skin_defs);

		if(m_name == "Header")
			int i = 0;

		printf("INFO: Loading style %s\n", m_name.c_str());
		this->load(*this, layout_defs, skin_defs);

		m_skin.prepare();
		for(InkStyle& skin : m_skins)
			skin.prepare();

		m_defined = true;
	}

	InkStyle& Style::skin(WidgetState state)
	{
		for(InkStyle& skin : reverse_adapt(m_skins))
			if((state & skin.m_state) == skin.m_state)
				return skin;
		return m_skin;
	}

	InkStyle& Style::decline_skin(WidgetStates state)
	{
		for(InkStyle& skin : m_skins)
			if(state.value == skin.m_state)
				return skin;

		m_skins.emplace_back(m_skin);
		m_skins.back().m_state = static_cast<WidgetState>(state.value);
		return m_skins.back();
	}
}
