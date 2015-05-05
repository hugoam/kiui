//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOINK_H
#define MK_NANOINK_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Nano/nanovg/nanovg.h>

namespace mk
{
	class NanoInk : public Inkbox
	{
	public:
		NanoInk(Frame& frame, NanoLayer& layer);
		~NanoInk();

		void updateContent();
		void updateFrame();
		void updateClip();
		void updatePosition();
		void updateStyle();
		
		void show();
		void hide();

		float contentSize(Dimension dim);
		size_t caretIndex(float x, float y);
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight);

		Image& fetchImage(Image& image, bool tile = false);
		void drawImage(const Image& image, float x, float y, float w, float h);
		void drawImageStretch(const Image& image, float x, float y, float w, float h, float xoff = 0.f, float yoff = 0.f, float xstretch = 1.f, float ystretch = 1.f);
		void drawSkinImage(ImageSkin::Section section, float x, float y, float w, float h);

		void splitImageSkin(int image);

		void setupText();

		void drawImage();
		void drawText();
		void redrawImage();
		void redrawText();

		static bool sDebugDraw;
		static int sDebugBatch;

	private:
		void drawImage(int image, float x, float y, float w, float h, float imgx, float imgy, float imgw, float imgh);

		void drawCache(NVGdisplayList* cache);

	protected:
		NVGcontext* mCtx;
		NVGdisplayList* mImageCache;
		NVGdisplayList* mTextCache;
		NanoLayer& mLayer;
		BoxFloat mCorners;
		Image* mImage;
		Image* mOverlay;
		Image* mTile;
		Image* mSkin;
		Dimension mFitCorners;
		bool mTextUpdate;
		bool mImageUpdate;
		bool mMoved;
		std::vector<NVGtextRow> mTextRows;
	};

}

#endif
