//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WCONTEXTMENU_H
#define TOY_WCONTEXTMENU_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class TOY_UI_EXPORT ContextMenu : public Overlay
	{
	public:
		ContextMenu(Piece& parent, Trigger onClose);

		void clear();

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);
		virtual void middleClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("ContextMenu", Overlay::cls()); return ty; }

	protected:
		Trigger m_onClose;
	};
}

#endif
