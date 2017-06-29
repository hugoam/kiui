//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/Textbox.h>

#include <toyobj/String/StringConvert.h>

#include <toyobj/Any.h>

#include <toyui/Frame/Frame.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Textbox::Textbox(WValue& input)
		: TypeIn(input, true, cls())
	{}

	Textbox::Textbox(Wedge& parent, string& text)
		: TypeIn(parent, text, true, cls())
	{}
}
