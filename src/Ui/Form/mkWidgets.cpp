//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkWidgets.h>

#include <Object/String/mkStringConvert.h>
#include <Object/mkStem.h>

#include <Object/Image/mkImage.h>

namespace mk
{
	Label::Label(const string& cls, const string& label)
		: Form(cls + " label", label)
	{}

	Image::Image(const string& cls, const string& image)
		: Form(cls + " image")
	{
		this->setImage(image);
	}

	DynamicImage::DynamicImage(const string& cls, std::unique_ptr<Image256> image)
		: Form(cls + " dynamicimage")
		, mImage(std::move(image))
	{}

	DynamicImage::~DynamicImage()
	{}

	Bar::Bar(const string& cls, Stat<float>* stat)
		: Form(cls + " statbar")
		, mStat(stat)
		, mValueLabel(this->makeappend<Label>("valuelabel", toString(mStat->value())))
		, mBaseBar(this->makeappend<Form>("basebar"))
		, mValueBar(this->makeappend<Form>("valuebar"))
	{
		//this->update();
	}

	void Bar::nextFrame(size_t tick, size_t delta)
	{
		Form::nextFrame(tick, delta);

		string val = toString(mStat->value());
		if(val != mValueLabel->label())
			this->update();
	}

	void Bar::update()
	{
		mValueLabel->setLabel(toString(mStat->value()));
		mBaseBar->attrs()["ratio"] = toString((mStat->base() - mStat->min()) / (mStat->max() - mStat->min()));
		mValueBar->attrs()["ratio"] = toString((mStat->value() - mStat->min()) / (mStat->max() - mStat->min()));
	}
}
