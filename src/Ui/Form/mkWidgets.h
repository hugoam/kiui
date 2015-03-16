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
	class MK_UI_EXPORT Control : public Form, public Styled<Control>
	{
	public:
		Control(SchemeMapper mapper = nullptr);
	};

	class MK_UI_EXPORT _I_ WrapX : public Form, public Typed<WrapX, Form>, public Styled<WrapX>
	{
	public:
		WrapX(SchemeMapper mapper = nullptr);

		using Typed<WrapX, Form>::cls;
	};

	class MK_UI_EXPORT _I_ WrapY : public Form, public Typed<WrapY, Form>, public Styled<WrapY>
	{
	public:
		WrapY(SchemeMapper mapper = nullptr);

		using Typed<WrapY, Form>::cls;
	};

	class MK_UI_EXPORT _I_ DivX : public Form, public Typed<DivX, Form>, public Styled<DivX>
	{
	public:
		DivX(SchemeMapper mapper = nullptr);

		using Typed<DivX, Form>::cls;
	};

	class MK_UI_EXPORT _I_ DivY : public Form, public Typed<DivY, Form>, public Styled<DivY>
	{
	public:
		DivY(SchemeMapper mapper = nullptr);

		using Typed<DivY, Form>::cls;
	};

	class MK_UI_EXPORT _I_ PartitionX : public Form, public Typed<PartitionX, Form>, public Styled<PartitionX>
	{
	public:
		PartitionX(SchemeMapper mapper = nullptr);

		using Typed<PartitionX, Form>::cls;
	};

	class MK_UI_EXPORT _I_ PartitionY : public Form, public Typed<PartitionY, Form>, public Styled<PartitionY>
	{
	public:
		PartitionY(SchemeMapper mapper = nullptr);

		using Typed<PartitionY, Form>::cls;
	};

	class MK_UI_EXPORT _I_ Header : public Form, public Typed<Header, Form>, public Styled<Header>
	{
	public:
		Header(SchemeMapper mapper = nullptr);

		using Typed<Header, Form>::cls;
	};

	class MK_UI_EXPORT _I_ Label : public Form, public Typed<Label, Form>, public Styled<Label>
	{
	public:
		Label(Style* style, const string& label);
		Label(const string& label);

		using Typed<Label, Form>::cls;
	};

	class MK_UI_EXPORT _I_ Textbox : public Form, public Typed<Textbox, Form>
	{
	public:
		Textbox(Style* style, const string& text);
		Textbox(const string& text);

		using Typed<Textbox, Form>::cls;
	};

	class MK_UI_EXPORT _I_ Image : public Form, public Typed<Image, Form>, public Styled<Image>
	{
	public:
		Image(Style* style, const string& image);
		Image(const string& image);

		using Typed<Image, Form>::cls;
	};
	
	class MK_UI_EXPORT _I_ DynamicImage : public Form, public Typed<DynamicImage, Form>
	{
	public:
		DynamicImage(Style* style, unique_ptr<Image256> image);
		~DynamicImage();

		Image256* imageData() { return mImage.get(); }

		using Typed<DynamicImage, Form>::cls;

	protected:
		unique_ptr<Image256> mImage;
	};

	class MK_UI_EXPORT ProgressBar : public Form, public Typed<ProgressBar, Form>
	{
	public:
		ProgressBar(Style* style, AutoStat<float> stat);

		using Typed<ProgressBar, Form>::cls;

	protected:
		AutoStat<float> mStat;
		Label* mValueLabel;
	};
}

#endif // MK_WIDGET_H_INCLUDED
