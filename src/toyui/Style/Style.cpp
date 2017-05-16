//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Style/Style.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>

#include <toyui/Edit/Input.h>

namespace toy
{
	void InkStyle::prepare()
	{
		if(m_base)
			this->inherit(m_base.val->skin());

		if(backgroundColour().a() > 0.f || textColour().a() > 0.f || borderColour().a() > 0.f || image() || !imageSkin().null())
			m_empty = false;
	}

	Style::Style(Type& type, Style* base)
		: IdObject(cls())
		, m_styleType(&type)
		, m_base(base)
		, m_name(type.name())
		, m_layout()
		, m_skin(this)
		, m_subskins()
		, m_updated(0)
		, m_ready(false)
	{
		this->index();
	}

	Style::Style(const string& name)
		: IdObject(cls())
		, m_styleType(nullptr)
		, m_base(nullptr)
		, m_name(name)
		, m_layout()
		, m_skin(this)
		, m_subskins()
		, m_updated(0)
		, m_ready(false)
	{
		this->index();
	}

	Style::~Style()
	{}

	void Style::clear()
	{
		m_layout = LayoutStyle();
		m_skin = InkStyle(this);
		m_subskins.clear();
		++m_updated;
		m_ready = false;
	}

	void Style::prepare(Style* definition)
	{
		if(m_ready)
			return;

		if(definition)
			this->define(*definition);

		if(m_base)
		{
			this->inheritLayout(*m_base);
			this->inheritSkin(*m_base);
		}

		for(auto& subskin : m_subskins)
			subskin.m_skin.inherit(m_skin);

		m_skin.prepare();

		for(auto& subskin : m_subskins)
			subskin.m_skin.prepare();

		m_ready = true;
		++m_updated;
	}

	void Style::define(Style& style)
	{
		this->copyLayout(style);
		this->copySkin(style);
	}

	void Style::inheritLayout(Style& base)
	{
		m_layout.inherit(base.layout());
	}

	void Style::copyLayout(Style& base)
	{
		m_layout.copy(base.layout());
	}

	void Style::inheritSkin(Style& base)
	{
		m_skin.inherit(base.skin());

		for(auto& subskin : base.m_subskins)
			this->fetchSubskin(subskin.m_state).inherit(subskin.m_skin);
	}

	void Style::copySkin(Style& base)
	{
		m_skin.copy(base.skin());

		for(auto& subskin : base.m_subskins)
			this->fetchSubskin(subskin.m_state).copy(subskin.m_skin);
	}

	InkStyle& Style::subskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(m_subskins))
			if((state & skin.m_state) == skin.m_state)
				return skin.m_skin;
		return m_skin;
	}

	InkStyle& Style::fetchSubskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(m_subskins))
			if(state == skin.m_state)
				return skin.m_skin;

		m_subskins.emplace_back(state, *this, m_name + toString(state));
		m_subskins.back().m_skin.copy(m_skin);
		return m_subskins.back().m_skin;
	}

	InkStyle& Style::decline(WidgetState state)
	{
		return this->fetchSubskin(state);
	}
}
