//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Style/mkStyle.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Widget/mkWidget.h>

#include <Ui/Widget/mkInput.h>

namespace mk
{
	StyleType::StyleType(const string& name)
		: Type(TYPE, name)
		, Style(*this, nullptr)
	{}

	StyleType::StyleType(const string& name, StyleType& base)
		: Type(*base.styleType(), TYPE, name)
		, Style(*this, &base)
	{}

	Style::Style(Type& type, Style* base)
		: IdStruct(cls())
		, m_styleType(&type)
		, m_base(base)
		, m_baseSkin(base)
		, m_name(type.name())
		, m_layout()
		, m_skin(m_name)
		, m_subskins()
		, m_updated(0)
	{
		if(m_base)
			this->inherit();
	}

	Style::Style(const string& name)
		: IdStruct(cls())
		, m_styleType(nullptr)
		, m_base(nullptr)
		, m_baseSkin(nullptr)
		, m_name(name)
		, m_layout()
		, m_skin(m_name)
		, m_subskins()
		, m_updated(0)
	{}

	Style::~Style()
	{}

	void Style::reset()
	{
		m_layout = LayoutStyle();
		m_skin = InkStyle(m_name);
		m_subskins.clear();
		if(m_base)
			m_baseSkin = m_base;
		++m_updated;
	}

	void Style::rebase(Style& base)
	{
		m_base = &base;
		m_baseSkin = &base;
		this->inherit();
	}

	void Style::rebaseSkins(Style& base)
	{
		m_baseSkin = &base;
		this->inherit();
	}

	void Style::inherit()
	{
		if(m_base)
			this->inheritLayout(*m_base);
		if(m_baseSkin)
			this->inheritSkins(*m_baseSkin);

		//for(auto& subskin : m_subskins) //@todo : why doesn't this behave correctly when enabled
		//	subskin.m_skin.copy(m_skin, true);
	}

	void Style::inheritLayout(Style& base)
	{
		m_layout.copy(base.layout(), true);
	}

	void Style::inheritSkins(Style& base)
	{
		m_skin.copy(base.skin(), true);

		for(auto& subskin : base.m_subskins)
		{
			this->copy(subskin.m_state, m_skin, false);
			this->copy(subskin.m_state, subskin.m_skin, true);
		}
	}

	void Style::copySkins(Style& base)
	{
		m_skin.copy(base.skin(), false);

		for(auto& subskin : base.m_subskins)
			this->copy(subskin.m_state, subskin.m_skin, false);
	}

	InkStyle& Style::subskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(m_subskins))
			if((state & skin.m_state) == skin.m_state)
				return skin.m_skin;
		return m_skin;
	}

	InkStyle& Style::copy(WidgetState state, InkStyle& original, bool inherit)
	{
		for(SubSkin& skin : reverse_adapt(m_subskins))
			if(state == skin.m_state)
			{
				skin.m_skin.copy(original, inherit);
				return skin.m_skin;
			}

		m_subskins.emplace_back(state, m_name + toString(state));
		m_subskins.back().m_skin.copy(original, inherit);
		return m_subskins.back().m_skin;
	}

	InkStyle& Style::decline(WidgetState state)
	{
		return this->copy(state, m_skin, false);
	}
}
