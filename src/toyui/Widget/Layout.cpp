//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Layout.h>

namespace toy
{
	Page::Page(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Dialog::Dialog(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Board::Board(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Layout::Layout(Wedge& parent, Type& type)
		: Board(parent, type)
	{}

	Row::Row(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Div::Div(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Stack::Stack(Wedge& parent, Type& type, FrameType frameType)
		: Container(parent, type, frameType)
	{}

	Sheet::Sheet(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Header::Header(Wedge& parent, Type& type)
		: Row(parent, type)
	{}
}
