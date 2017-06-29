//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_POPUP_H
#define TOY_POPUP_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class TOY_UI_EXPORT Popup : public Wedge
	{
	public:
		Popup(Wedge& parent, Callback onClose = nullptr, Type& type = cls());

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		void open(bool modal);
		void close();

		static Type& cls() { static Type ty("Popup", Wedge::Overlay()); return ty; }

	protected:
		Callback m_onClose;
	};
}

#endif
