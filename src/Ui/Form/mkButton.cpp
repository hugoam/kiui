//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkButton.h>

#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkWButton.h>

#include <Object/mkStem.h>

namespace mk
{
	Button::Button(Style* style, const string& label, const string& image, const Trigger& trigger)
		: Form(style, label, [this]() { return make_unique<WButton>(this); })
		, mTrigger(trigger)
	{
		mType = cls();

		if(!image.empty())
		{
			string lower = image;
			std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower); // Images names are lowercase for now
			this->setImage(lower + ".png");
		}
	}
}
