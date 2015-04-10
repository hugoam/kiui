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
		, mUpdated(0)
	{}

	Style::Style(const string& name)
		: IdStruct(index<Style>(), cls())
		, mStyleType(nullptr)
		, mName(name)
		, mLayout("", FLOW, CLIP, VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y)
		, mSkin()
		, mSubskins()
		, mUpdated(0)
	{}

	Style::~Style()
	{}

	void Style::reset()
	{
		mLayout = LayoutStyle("", FLOW, CLIP, VOID, false, DimSizing(SHRINK, SHRINK), DimFloat(1.f, 1.f), DIM_Y);
		mSkin = InkStyle();
		mSubskins.clear();
		++mUpdated;
	}

	void Style::inherit(Style* base)
	{
		this->inheritLayout(base);
		this->inheritSkins(base);
	}

	void Style::inheritLayout(Style* base)
	{
		mLayout = *base->layout();
	}

	void Style::inheritSkins(Style* base)
	{
		mSkin = *base->skin();

		for(auto& subskin : base->mSubskins)
			this->decline(subskin.mState, subskin.mSkin);
	}

	InkStyle* Style::subskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(mSubskins))
			if((state & skin.mState) == skin.mState)
				return &skin.mSkin;
		return &mSkin;
	}

	InkStyle* Style::decline(WidgetState state, InkStyle& original)
	{
		for(SubSkin& skin : reverse_adapt(mSubskins))
			if(state == skin.mState)
			{
				skin.mSkin = original;
				return &skin.mSkin;
			}

		mSubskins.emplace_back(state, original);
		return &mSubskins.back().mSkin;
	}

	InkStyle* Style::decline(WidgetState state)
	{
		return decline(state, mSkin);
	}
}
