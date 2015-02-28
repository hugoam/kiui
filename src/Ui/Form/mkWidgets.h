//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WIDGETS_H_INCLUDED
#define MK_WIDGETS_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Util/mkStat.h>
#include <Object/Util/mkMake.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkButton.h>
#include <Ui/Scheme/mkWWindow.h>
#include <Ui/Scheme/mkList.h>
#include <Ui/Scheme/mkWTabber.h>
#include <Ui/Scheme/mkWDropdown.h>
#include <Ui/Scheme/mkWRadioButton.h>

#include <Ui/Form/mkFValue.h>

namespace mk
{
	class MK_UI_EXPORT Label : public Form
	{
	public:
		Label(const string& cls, const string& label);
	};

	class MK_UI_EXPORT Textbox : public Form
	{
	public:
		Textbox(const string& cls, const string& text);
	};

	class MK_UI_EXPORT Image : public Form
	{
	public:
		Image(const string& cls, const string& image);
	};
	
	class MK_UI_EXPORT DynamicImage : public Form
	{
	public:
		DynamicImage(const string& cls, unique_ptr<Image256> image);
		~DynamicImage();

		Image256* imageData() { return mImage.get(); }

	protected:
		unique_ptr<Image256> mImage;
	};

	class MK_UI_EXPORT Bar : public Form
	{
	public:
		Bar(const string& cls, Stat<float>* stat);

		void nextFrame(size_t tick, size_t delta);
		void update();

	protected:
		Stat<float>* mStat;
		Label* mValueLabel;
		Form* mBaseBar;
		Form* mValueBar;
	};
}

#endif // MK_WIDGET_H_INCLUDED
