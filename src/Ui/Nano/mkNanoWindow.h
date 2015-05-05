//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_GORILLAWINDOW_H
#define MK_GORILLAWINDOW_H

/* mk Og */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Nano/RectPacking/Rect.h>
#include <Ui/Nano/RectPacking/GuillotineBinPack.h>

#include <memory>

namespace mk
{
	struct ImageRect : public BPRect
	{
		string subfolder;
		string image;
	};

	class MK_UI_EXPORT NanoAtlas
	{
	public:
		NanoAtlas(NVGcontext* ctx, const string& path, size_t width, size_t height);

		const string& path() { return mPath; }
		size_t width() { return mWidth; }
		size_t height() { return mHeight; }
		int image() { return mImage; }

		void createAtlas();
		void generateAtlas();
		void loadAtlas();

		void fitImage(ImageRect& image);
		void blitImage(ImageRect& image);

		ImageRect& findSpriteRect(const string& image);
		void appendSprite(const string& image, const string& group);
		void defineSprite(const string& image, float left, float top, float width, float height);

		std::vector<ImageRect>& sprites() { return mSprites; }

	protected:
		NVGcontext* mCtx;
		string mPath;
		size_t mWidth;
		size_t mHeight;
		GuillotineBinPack mRectPacker;
		std::vector<ImageRect> mSprites;
		unsigned char* mData;
		int mImage;
	};

	class MK_UI_EXPORT NanoLayer : public InkLayer
	{
	public:
		NanoLayer(Layer& layer, NanoTarget& target, size_t index);
		~NanoLayer();

		NanoTarget& target() { return mTarget; }

		unique_ptr<Inkbox> createInkbox(Frame& frame);

		void show();
		void hide();

		void move(size_t index) {}

		void nanodraw();
		void drawImage(Frame& frame);
		void drawText(Frame& frame);

	protected:
		NanoTarget& mTarget;
		Frame& mFrame;

		std::vector<Frame*> mOrdered;
	};

	class MK_UI_EXPORT NanoTarget : public InkTarget
	{
	public:
		NanoTarget(NanoWindow& window);

		NanoWindow& window() { return mWindow; }

		unique_ptr<InkLayer> createLayer(Layer& layer, size_t z);

		void nanodraw();
		void drawLayer(Layer& layer);

	protected:
		NanoWindow& mWindow;
	};

	class MK_UI_EXPORT NanoWindow : public InkWindow
	{
	public:
		NanoWindow(size_t width, size_t height, float pixelRatio, string resourcePath);
		~NanoWindow();

		void nextFrame(double time, double delta);

		InkTarget& screenTarget();

		string resourcePath() { return mResourcePath; }
		NVGcontext* ctx() { return mCtx; }
		NanoAtlas& atlas() { return *mAtlas.get(); }

	protected:
		size_t mWidth;
		size_t mHeight;
		float mPixelRatio;
		string mResourcePath;

		NVGcontext* mCtx;
		unique_ptr<NanoTarget> mScreenTarget;
		unique_ptr<NanoAtlas> mAtlas;
	};

}

#endif
