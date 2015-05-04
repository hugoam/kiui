//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_EXPANDBOX_H
#define MK_EXPANDBOX_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT ExpandboxHeader : public Sequence
	{
	public:
		ExpandboxHeader();

		static StyleType& cls() { static StyleType ty("ExpandboxHeader", Sequence::cls()); return ty; }
	};

	class MK_UI_EXPORT ExpandboxBody : public Sheet
	{
	public:
		ExpandboxBody();

		static StyleType& cls() { static StyleType ty("ExpandboxBody", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT ExpandboxToggle : public Toggle
	{
	public:
		ExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		static StyleType& cls() { static StyleType ty("ExpandboxToggle", Toggle::cls()); return ty; }
	};

	class MK_UI_EXPORT Expandbox : public Sheet
	{
	public:
		Expandbox(const string& title, bool collapsed = false, bool build = true);
		~Expandbox();

		Sheet* header() { return mHeader; }

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		virtual void expand();
		virtual void collapse();

		static StyleType& cls() { static StyleType ty("Expandbox", Sheet::cls()); return ty; }

	protected:
		string mTitle;
		Sheet* mHeader;
		Sheet* mContainer;
		Toggle* mExpandButton;
		Label* mTitleLabel;
		bool mCollapsed;
	};
}

#endif
