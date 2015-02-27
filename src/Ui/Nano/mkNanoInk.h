//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOINK_H
#define MK_NANOINK_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>

namespace mk
{
	class NanoInk : public Inkbox
	{
	public:
		NanoInk(Frame* frame, NanoLayer* layer);
		~NanoInk();
    
		void updateContent();
		void updateFrame();
		void updateStyle();

		void show();
		void hide();

		float contentSize(Dimension dim);

		void caption(const string& text);

		void nanodraw();

	protected:
		NVGcontext* mCtx;
		NanoLayer* mLayer;
		int mImage;
		bool mVisible;
	};

}

#endif
