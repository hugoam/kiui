//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkWTextbox.h>

#include <Object/String/mkStringConvert.h>
#include <Object/mkStem.h>

#include <Object/Image/mkImage.h>

namespace mk
{
	Control::Control(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	WrapX::WrapX(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	WrapY::WrapY(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	DivX::DivX(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	DivY::DivY(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	PartitionX::PartitionX(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	PartitionY::PartitionY(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	Header::Header(SchemeMapper mapper)
		: Form(styleCls(), "", mapper)
	{}

	Label::Label(Style* style, const string& label)
		: Form(style ? style : styleCls(), label, [this](){ return make_unique<WLabel>(this); })
	{
		mType = cls();
	}
	
	Label::Label(const string& label)
		: Label(styleCls(), label)
	{}

	Textbox::Textbox(Style* style, const string& text)
		: Form(style, text, [this, text](){ return make_unique<WTextbox>(this, text); })
	{
		mType = cls();
	}

	Textbox::Textbox(const string& text)
		: Textbox(nullptr, text)
	{}

	Image::Image(Style* style, const string& image)
		: Form(style ? style : styleCls())
	{
		mType = cls();
		this->setImage(image);
	}

	Image::Image(const string& image)
		: Image(nullptr, image)
	{}

	DynamicImage::DynamicImage(Style* style, unique_ptr<Image256> image)
		: Form(style)
		, mImage(std::move(image))
	{
		mType = cls();
	}

	DynamicImage::~DynamicImage()
	{}

	ProgressBar::ProgressBar(Style* style, AutoStat<float> stat)
		: Form(style)
		, mStat(stat)
		, mValueLabel(this->makeappend<Label>(toString(mStat.value())))
	{
		mType = cls();
		//this->update();
	}
}
