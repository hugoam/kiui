//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Style/mkStyle.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Widget/mkWidget.h>

namespace mk
{
	Style::Style(Type* type)
		: IdStruct(index<Style>(), cls())
		, mStyleType(type)
		, mName()
		, mLayout("", FLOW, CLIP, VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y)
		, mSubskins()
	{}

	Style::Style(const string& name)
		: IdStruct(index<Style>(), cls())
		, mStyleType(nullptr)
		, mName(name)
		, mLayout("", FLOW, CLIP, VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y)
		, mSubskins()
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

		for(auto& subskin : base->subskins())
			mSubskins.emplace_back(subskin.mState, subskin.mSkin);
	}

	InkStyle* Style::subskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(mSubskins))
			if((state & skin.mState) == skin.mState)
				return &skin.mSkin;
		return &mSkin;
	}

	InkStyle* Style::decline(WidgetState state)
	{
		mSubskins.emplace_back(state, mSkin);
		return &mSubskins.back().mSkin;
	}
}
