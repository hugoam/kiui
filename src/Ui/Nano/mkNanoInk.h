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

		int fetchImage(const string& image);
		void drawImage(int image, float x, float y, float w, float h);

		void nanodraw();

	protected:
		NVGcontext* mCtx;
		NanoLayer* mLayer;
		int mImage;
		int mTop, mRight, mBottom, mLeft;
		int mTopLeft, mTopRight, mBottomRight, mBottomLeft;
		int mFill;
	};

}

#endif
