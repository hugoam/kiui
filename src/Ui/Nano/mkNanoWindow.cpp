//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Nano/mkNanoInk.h>

#include <Ui/Widget/mkWidget.h>

#include <Object/Util/mkMake.h>

//#define NANOVG_GL_USE_UNIFORMBUFFER 1
#ifdef NANOVG_GLEW
#include <Ui/Nano/nanovg/glew.h>
#elif KIUI_EMSCRIPTEN
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <Ui/Nano/nanovg/nanovg.h>

#if KIUI_EMSCRIPTEN
#define NANOVG_GLES2_IMPLEMENTATION
#else
#define NANOVG_GL2_IMPLEMENTATION
#endif

#include <Ui/Nano/nanovg/nanovg_gl.h>
#include <Ui/Nano/nanovg/stb_image.h>

#include <dirent.h>

#include <iostream>

namespace mk
{
	ImageRect makeRect(NVGcontext* ctx, const string& path, const string& image, const string& subfolder = "")
	{
		ImageRect ret;
		ret.image = image;
		ret.subfolder = subfolder;
		string fullpath = path + subfolder + image;
		int id = nvgCreateImage(ctx, fullpath.c_str(), 0);
		nvgImageSize(ctx, id, &ret.width, &ret.height);
		nvgDeleteImage(ctx, id);
		return ret;
	}

	void spritesInFolder(NVGcontext* ctx, NanoAtlas& atlas, const string& path, const string& subfolder)
	{
		DIR* dir = opendir(path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				atlas.sprites().push_back(makeRect(ctx, atlas.path(), ent->d_name, subfolder));

		closedir(dir);
	}

	unique_ptr<NanoAtlas> generateAtlas(NVGcontext* ctx, size_t atlasWidth, size_t atlasHeight, string resourcePath)
	{
		string path = resourcePath + "interface/uisprites/";
		unique_ptr<NanoAtlas> atlas = make_unique<NanoAtlas>(ctx, path, atlasWidth, atlasHeight);

		DIR* dir = opendir(path.c_str());
		dirent* ent;

		spritesInFolder(ctx, *atlas.get(), path, "");

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
				spritesInFolder(ctx, *atlas.get(), path + ent->d_name, string(ent->d_name) + "/");

		closedir(dir);

		atlas->createAtlas();
		atlas->generateAtlas();
		atlas->loadAtlas();

		return atlas;
	}

	NanoAtlas::NanoAtlas(NVGcontext* ctx, const string& path, size_t width, size_t height)
		: mCtx(ctx)
		, mPath(path)
		, mWidth(width)
		, mHeight(height)
		, mRectPacker(width, height)
	{}

	void NanoAtlas::createAtlas()
	{
		mData = new unsigned char[mWidth*mHeight*4];

		unsigned char* in = mData;
		for(size_t y = 0; y < mHeight; ++y)
			for(size_t x = 0; x < mWidth; ++x)
			{
				*(in++) = 0;
				*(in++) = 0;
				*(in++) = 0;
				*(in++) = 0;
			}
	}

	void NanoAtlas::generateAtlas()
	{
		// @todo : sort images

		for(ImageRect& image : mSprites)
		{
			this->fitImage(image);
			string name = image.subfolder + replaceAll(image.image, ".png", "");
			Image::sIcons[name] = Image(name, image.width, image.height);
		}
	}

	void NanoAtlas::loadAtlas()
	{
		mImage = nvgCreateImageRGBA(mCtx, mWidth, mHeight, 0, mData);
		delete [] mData;
	}

	void NanoAtlas::fitImage(ImageRect& image)
	{
		static_cast<BPRect&>(image) = mRectPacker.Insert(image.width, image.height, false, GuillotineBinPack::RectBestShortSideFit, GuillotineBinPack::SplitShorterLeftoverAxis);
		this->blitImage(image);
	}

	void NanoAtlas::blitImage(ImageRect& image)
	{
		string path = mPath + image.subfolder + image.image;
		int width, height, n;
		unsigned char* img;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		img = stbi_load(path.c_str(), &width, &height, &n, 4);

		unsigned char* out = img;
		for(size_t y = 0; y < height; ++y)
		{
			size_t offset = image.x * 4 + (image.y + y) * mWidth * 4;
			unsigned char* in = mData + offset;
			for(size_t x = 0; x < width; ++x)
			{
				*(in++) = *(out++);
				*(in++) = *(out++);
				*(in++) = *(out++);
				*(in++) = *(out++);
			}
		}

		stbi_image_free(img);
	}

	ImageRect& NanoAtlas::findSpriteRect(const string& name)
	{
		for(ImageRect& sprite : mSprites)
			if(sprite.subfolder + sprite.image == name)
				return sprite;
	}

	void NanoAtlas::appendSprite(const string& name, const string& group)
	{
		mSprites.push_back(makeRect(mCtx, name, group));
		ImageRect& sprite = mSprites.back();
		this->fitImage(sprite);
	}

	NanoLayer::NanoLayer(Layer& layer, NanoTarget& target, size_t index)
		: InkLayer(layer, target, index)
		, mTarget(target)
		, mFrame(layer)
	{}

	NanoLayer::~NanoLayer()
	{}

	unique_ptr<Inkbox> NanoLayer::createInkbox(Frame& frame)
	{
		return make_unique<NanoInk>(frame, *this);
	}

	void NanoLayer::show()
	{
		mFrame.inkbox().show();
		//this->moveToTop();
	}

	void NanoLayer::hide()
	{
		mFrame.inkbox().hide();
	}

	void NanoLayer::nanodraw()
	{
		this->drawImage(mFrame);
		this->drawText(mFrame);
	}

	void NanoLayer::drawImage(Frame& frame)
	{
		static_cast<NanoInk&>(frame.inkbox()).drawImage();

		if(frame.frameType() >= STRIPE)
			for(Frame* subframe : frame.as<Stripe>().contents())
				if(subframe->visible() && subframe->frameType() < LAYER)
					this->drawImage(*subframe);
	}

	void NanoLayer::drawText(Frame& frame)
	{
		static_cast<NanoInk&>(frame.inkbox()).drawText();

		if(frame.frameType() >= STRIPE)
			for(Frame* subframe : frame.as<Stripe>().contents())
				if(subframe->visible() && subframe->frameType() < LAYER)
					this->drawText(*subframe);
	}

	NanoTarget::NanoTarget(NanoWindow& window)
		: InkTarget(50)
		, mWindow(window)
	{}

	void NanoTarget::nanodraw()
	{
		this->drawLayer(*d_rootLayer);
	}

	void NanoTarget::drawLayer(Layer& layer)
	{
		layer.inkLayer().as<NanoLayer>().nanodraw();

		for(Layer* sublayer : layer.layers())
			if(sublayer->layer().visible())
				this->drawLayer(*sublayer);
	}

	unique_ptr<InkLayer> NanoTarget::createLayer(Layer& layer, size_t z)
	{
		if(!d_rootLayer)
			d_rootLayer = &layer;
		return make_unique<NanoLayer>(layer, *this, z);
	}

	NanoWindow::NanoWindow(size_t width, size_t height, float pixelRatio, string resourcePath)
		: mWidth(width)
		, mHeight(height)
		, mPixelRatio(pixelRatio)
		, mResourcePath(resourcePath)
		, mCtx(nullptr)
	{
#if NANOVG_GL2
		mCtx = nvgCreateGL2(NVG_ANTIALIAS);
#elif NANOVG_GLES2
		mCtx = nvgCreateGLES2(NVG_STENCIL_STROKES);
#endif

		mAtlas = generateAtlas(mCtx, 1024, 1024, resourcePath);

		string fontPath = resourcePath + "interface/fonts/DejaVuSans.ttf";
		nvgCreateFont(mCtx, "dejavu", fontPath.c_str());
		nvgFontSize(mCtx, 14.0f);
		nvgFontFace(mCtx, "dejavu");

		if(mCtx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}

		mScreenTarget = make_unique<NanoTarget>(*this);
	}

	NanoWindow::~NanoWindow()
	{
		for(auto& kv : Image::sIcons)
			nvgDeleteImage(mCtx, kv.second.d_index);

#if NANOVG_GL2
		nvgDeleteGL2(mCtx);
#elif NANOVG_GLES2
		nvgDeleteGLES2(mCtx);
#endif
	}

	void NanoWindow::nextFrame(double time, double delta)
	{
		NanoInk::sDebugBatch = 0;
		nvgBeginFrame(mCtx, mWidth, mHeight, mPixelRatio);

		mScreenTarget->nanodraw();

		nvgEndFrame(mCtx);

		static double prevtime = 0.0;
		if(time - prevtime > 1.0)
		{
			std::cerr << "Frames drawn : " << NanoInk::sDebugBatch << std::endl;
			prevtime = time;
		}
	}

	InkTarget& NanoWindow::screenTarget()
	{
		return *mScreenTarget.get();
	}
}
