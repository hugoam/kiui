//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_POPUP_H
#define TOY_POPUP_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Popup : public Wedge
	{
	public:
		Popup(const Params& params, Callback onClose = nullptr, bool open = true);

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		void open(bool modal);
		void close();

	protected:
		Callback m_onClose;
	};
}

#endif
