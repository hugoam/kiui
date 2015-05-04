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
	std::map<string, Image> Image::sIcons;

	StyleType::StyleType(const string& name)
		: Type(name)
		, Style(*this, nullptr)
	{}

	StyleType::StyleType(const string& name, StyleType& base)
		: Type(name, *base.styleType())
		, Style(*this, &base)
	{}

	Style::Style(Type& type, Style* base)
		: IdStruct(index<Style>(), cls())
		, mStyleType(&type)
		, mBase(base)
		, mBaseSkin(base)
		, mName(type.name())
		, mLayout()
		, mSubskins()
		, mUpdated(0)
	{
		if(mBase)
			this->inherit();
	}

	Style::Style(const string& name)
		: IdStruct(index<Style>(), cls())
		, mStyleType(nullptr)
		, mBase(nullptr)
		, mBaseSkin(nullptr)
		, mName(name)
		, mLayout()
		, mSkin()
		, mSubskins()
		, mUpdated(0)
	{}

	Style::~Style()
	{}

	void Style::reset()
	{
		mLayout = LayoutStyle();
		mSkin = InkStyle();
		mSubskins.clear();
		if(mBase)
			mBaseSkin = mBase;
		++mUpdated;
	}

	void Style::rebase(Style& base)
	{
		mBase = &base;
		mBaseSkin = &base;
		this->inherit();
	}

	void Style::rebaseSkins(Style& base)
	{
		mBaseSkin = &base;
		this->inherit();
	}

	void Style::inherit()
	{
		if(mBase)
			this->inheritLayout(*mBase);
		if(mBaseSkin)
			this->inheritSkins(*mBaseSkin);

		//for(auto& subskin : mSubskins) //@todo : why doesn't this behave correctly when enabled
		//	subskin.mSkin.copy(mSkin, true);
	}

	void Style::inheritLayout(Style& base)
	{
		mLayout.copy(base.layout(), true);
	}

	void Style::inheritSkins(Style& base)
	{
		mSkin.copy(base.skin(), true);

		for(auto& subskin : base.mSubskins)
		{
			this->copy(subskin.mState, mSkin, false);
			this->copy(subskin.mState, subskin.mSkin, true);
		}
	}

	void Style::copySkins(Style& base)
	{
		mSkin.copy(base.skin(), false);

		for(auto& subskin : base.mSubskins)
			this->copy(subskin.mState, subskin.mSkin, false);
	}

	InkStyle& Style::subskin(WidgetState state)
	{
		for(SubSkin& skin : reverse_adapt(mSubskins))
			if((state & skin.mState) == skin.mState)
				return skin.mSkin;
		return mSkin;
	}

	InkStyle& Style::copy(WidgetState state, InkStyle& original, bool inherit)
	{
		for(SubSkin& skin : reverse_adapt(mSubskins))
			if(state == skin.mState)
			{
				skin.mSkin.copy(original, inherit);
				return skin.mSkin;
			}

		mSubskins.emplace_back(state);
		mSubskins.back().mSkin.copy(original, inherit);
		return mSubskins.back().mSkin;
	}

	InkStyle& Style::decline(WidgetState state)
	{
		return this->copy(state, mSkin, false);
	}
}
