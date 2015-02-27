//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WWINDOW_H
#define MK_WWINDOW_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WWindow : public Sheet
	{
	public:
		WWindow(Trigger onClose, string title, bool closable = true, bool dockable = false, WDocksection* dock = nullptr, string clas = "");
		~WWindow();

		void build();

		const string& name();

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		//Widget* content() { return mContent; }
		bool dockable() { return mDockable; }
		WDocksection* dock() { return mDock; }

		Widget* vappend(std::unique_ptr<Widget> widget);
		//std::unique_ptr<Widget> vrelease(Widget* widget);

		void dock(WDocksection* docksection);
		void undock();

		void close();

	protected:
		string mName;
		bool mClosable;
		bool mDockable;
		Widget* mContent;
		Trigger mOnClose;
		Sheet* mHeader;
		WLabel* mTitle;
		WButton* mCloseButton;

		//Form* mContent;

		WDocksection* mDock;
	};

	class MK_UI_EXPORT Window : public Form
	{
	public:
		Window(std::unique_ptr<Form> content, bool closable = true, bool dockable = false, Trigger onClose = nullptr);

		void onClose(Widget* widget);

	protected:
		Trigger mOnClose;
	};
}

#endif
