//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABBER_H
#define MK_WTABBER_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT TabHeader : public Button
	{
	public:
		TabHeader(const string& label, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty(Button::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Tab : public Sheet
	{
	public:
		Tab(Button& header, bool active);

		unique_ptr<Widget> vrelease(Widget& widget);

		Button& header() { return mHeader; }

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Button& mHeader;
		bool mActive;
	};

	class MK_UI_EXPORT _I_ TabberHead : public Sequence
	{
	public:
		TabberHead();

		static StyleType& cls() { static StyleType ty(Sequence::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ TabberBody : public Sheet
	{
	public:
		TabberBody();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT Tabber : public Sheet
	{
	public:
		Tabber(bool downtabs = false);
		~Tabber();

		void select(size_t index);

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void headerClicked(Button& button);

		void showTab(Tab& tab);
		void showTab(size_t index);

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		TabberHead& mHeaders;
		TabberBody& mTabs;
		Tab* mCurrentTab;
		bool mDownTabs;
	};
}

#endif
