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
    
		inline InkStyle* skin() { return mFrame->inkstyle(); }

		void updateContent();
		void updateFrame();
		void updateStyle();

		void show();
		void hide();

		float contentSize(Dimension dim);
		size_t caretIndex(float x, float y);
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight);

		int fetchImage(const string& image);
		void drawImage(int image, float x, float y, float w, float h);
		void drawSkinImage(int image, float x, float y, float w, float h, float xoff = 0.f, float yoff = 0.f, float stretchwidth = 0.f, float stretchheight = 0.f);

		void splitImageSkin(int image);

		void nanodraw();

	protected:
		NVGcontext* mCtx;
		NanoLayer* mLayer;
		BoxFloat mCorners;
		int mImage;
		int mSkin;
	};

}

#endif
