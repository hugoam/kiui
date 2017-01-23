//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Textbox.h>

#include <toyobj/String/StringConvert.h>

#include <toyobj/Ref.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Textbox::Textbox(WValue& input)
		: TypeIn(input, cls())
	{}

	Textbox::Textbox(string& text)
		: TypeIn(text, cls())
	{}
}
