//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WCONTEXTMENU_H
#define TOY_WCONTEXTMENU_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class TOY_UI_EXPORT ContextMenu : public Sheet
	{
	public:
		ContextMenu(Trigger onClose);
		~ContextMenu();

		virtual void bind(Sheet& parent, size_t index);

		void clear();

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);
		virtual void middleClick(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("ContextMenu", Sheet::cls()); return ty; }

	protected:
		Trigger m_onClose;
	};
}

#endif
