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
#include <Ui/Scheme/mkWindow.h>
#include <Ui/Scheme/mkList.h>
#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Scheme/mkRadioButton.h>

namespace mk
{
	class MK_UI_EXPORT Control : public Form, public Styled<Control>
	{
	public:
		Control(unique_ptr<Sheet> sheet = nullptr);
	};

	class MK_UI_EXPORT _I_ WrapX : public Sheet, public Typed<WrapX, Sheet>, public Styled<WrapX>
	{
	public:
		WrapX();

		using Typed<WrapX, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ WrapY : public Sheet, public Typed<WrapY, Sheet>, public Styled<WrapY>
	{
	public:
		WrapY();

		using Typed<WrapY, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ DivX : public Sheet, public Typed<DivX, Sheet>, public Styled<DivX>
	{
	public:
		DivX();

		using Typed<DivX, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ DivY : public Sheet, public Typed<DivY, Sheet>, public Styled<DivY>
	{
	public:
		DivY();

		using Typed<DivY, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ PartitionX : public Sheet, public Typed<PartitionX, Sheet>, public Styled<PartitionX>
	{
	public:
		PartitionX();

		using Typed<PartitionX, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ PartitionY : public Sheet, public Typed<PartitionY, Sheet>, public Styled<PartitionY>
	{
	public:
		PartitionY();

		using Typed<PartitionY, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ Page : public ScrollSheet, public Typed<Page, Sheet>, public Styled<Page>
	{
	public:
		Page(const string& name, const string& dockid = "");

		const string& name() { return mName; }
		const string& dockid() { return mDockId; }

		using Typed<Page, Sheet>::cls;
		using Styled<Page>::styleCls;

	protected:
		string mName;
		string mDockId;
	};

	class MK_UI_EXPORT _I_ Dialog : public Sheet, public Typed<Dialog, Sheet>, public Styled<Dialog>
	{
	public:
		Dialog();

		using Typed<Dialog, Sheet>::cls;
	};

	class MK_UI_EXPORT _I_ Header : public Sheet, public Typed<Header, Sheet>, public Styled<Header>
	{
	public:
		Header();

		using Typed<Header, Sheet>::cls;
	};
}

#endif // MK_WIDGET_H_INCLUDED
