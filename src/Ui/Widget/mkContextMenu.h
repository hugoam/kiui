//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WCONTEXTMENU_H
#define MK_WCONTEXTMENU_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	class MK_UI_EXPORT WContextMenu : public Sheet, public Styled<WContextMenu>
	{
	public:
		WContextMenu();
		~WContextMenu();
	};
}

#endif
