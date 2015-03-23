//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Style/mkStyle.h>

#include <Ui/Widget/mkWidget.h>

namespace mk
{
	Style::Style(Type* type)
		: IdStruct(cls())
		, mStyleType(type)
		, mName()
		, mLayout("", FLOW, _VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y)
		, mSubskins(5)
	{}

	Style::Style(const string& name)
		: IdStruct(cls())
		, mStyleType(nullptr)
		, mName(name)
		, mLayout("", FLOW, _VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y)
		, mSubskins(5)
	{}

	Style::~Style()
	{}

	void Style::inheritLayout(Style* base)
	{
		mLayout = *base->layout();
	}

	void Style::inheritSkins(Style* base)
	{
		mSkin = *base->skin();

		if(base->subskin(ENABLED))
			mSubskins[ENABLED] = make_unique<InkStyle>(*base->subskin(ENABLED));
		if(base->subskin(HOVERED))
			mSubskins[HOVERED] = make_unique<InkStyle>(*base->subskin(HOVERED));
		if(base->subskin(ACTIVATED))
			mSubskins[ACTIVATED] = make_unique<InkStyle>(*base->subskin(ACTIVATED));
		if(base->subskin(ACTIVATED_HOVERED))
			mSubskins[ACTIVATED_HOVERED] = make_unique<InkStyle>(*base->subskin(ACTIVATED_HOVERED));
	}

	InkStyle* Style::decline(WidgetState state)
	{
		if(!mSubskins[state])
			mSubskins[state] = make_unique<InkStyle>(mSkin);
		return mSubskins[state].get();
	}
}
