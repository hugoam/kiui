//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Nano/mkNanoRenderer.h>

#include <Ui/Widget/mkWidget.h>

#include <Object/Util/mkUnique.h>

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
//#define NANOVG_GL2_IMPLEMENTATION
#define NANOVG_GL3_IMPLEMENTATION
#endif

#include <Ui/Nano/nanovg/nanovg_gl.h>
#include <Ui/Nano/nanovg/stb_image.h>

#include <Ui/mkUiWindow.h>
#include <Ui/Widget/mkRootSheet.h>

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

	unique_ptr<NanoAtlas> generateAtlas(NanoWindow& window, size_t atlasWidth, size_t atlasHeight, string resourcePath)
	{
		string path = resourcePath + "interface/uisprites/";
		unique_ptr<NanoAtlas> atlas = make_unique<NanoAtlas>(window, path, atlasWidth, atlasHeight);

		DIR* dir = opendir(path.c_str());
		dirent* ent;

		spritesInFolder(window.ctx(), *atlas, path, "");

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
				spritesInFolder(window.ctx(), *atlas, path + ent->d_name, string(ent->d_name) + "/");

		closedir(dir);

		atlas->createAtlas();
		atlas->generateAtlas();
		atlas->loadAtlas();

		return atlas;
	}

	NanoAtlas::NanoAtlas(NanoWindow& window, const string& path, size_t width, size_t height)
		: m_window(window)
		, m_ctx(window.ctx())
		, m_path(path)
		, m_width(width)
		, m_height(height)
		, m_rectPacker(width, height)
	{}

	void NanoAtlas::createAtlas()
	{
		m_data = new unsigned char[m_width*m_height*4];

		unsigned char* in = m_data;
		for(size_t y = 0; y < m_height; ++y)
			for(size_t x = 0; x < m_width; ++x)
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

		for(ImageRect& image : m_sprites)
		{
			this->fitImage(image);
			string name = image.subfolder + replaceAll(image.image, ".png", "");
			m_window.addImage(name, image.width, image.height);
		}
	}

	void NanoAtlas::loadAtlas()
	{
		m_image = nvgCreateImageRGBA(m_ctx, m_width, m_height, 0, m_data);
		delete [] m_data;
	}

	void NanoAtlas::fitImage(ImageRect& image)
	{
		static_cast<BPRect&>(image) = m_rectPacker.Insert(image.width, image.height, false, GuillotineBinPack::RectBestShortSideFit, GuillotineBinPack::SplitShorterLeftoverAxis);
		this->blitImage(image);
	}

	void NanoAtlas::blitImage(ImageRect& image)
	{
		string path = m_path + image.subfolder + image.image;
		int width, height, n;
		unsigned char* img;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		img = stbi_load(path.c_str(), &width, &height, &n, 4);

		unsigned char* out = img;
		for(int y = 0; y < height; ++y)
		{
			size_t offset = image.x * 4 + (image.y + y) * m_width * 4;
			unsigned char* in = m_data + offset;
			for(int x = 0; x < width; ++x)
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
		for(ImageRect& sprite : m_sprites)
			if(sprite.subfolder + sprite.image == name)
				return sprite;
	}

	void NanoAtlas::appendSprite(const string& name, const string& group)
	{
		m_sprites.push_back(makeRect(m_ctx, name, group));
		ImageRect& sprite = m_sprites.back();
		this->fitImage(sprite);
	}

	NanoWindow::NanoWindow(UiWindow& uiWindow, string resourcePath)
		: InkWindow(uiWindow, make_unique<NanoRenderer>(*this))
		, m_nanorenderer(*static_cast<NanoRenderer*>(m_renderer.get()))
		, m_resourcePath(resourcePath)
		, m_ctx(nullptr)
	{
#if NANOVG_GL2
		m_ctx = nvgCreateGL2(NVG_ANTIALIAS);
#elif NANOVG_GL3
		m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#elif NANOVG_GLES2
		m_ctx = nvgCreateGLES2(NVG_STENCIL_STROKES);
#endif

		m_atlas = generateAtlas(*this, 1024, 1024, resourcePath);

		for(Image& image : m_images)
			m_nanorenderer.initImage(image, false);

		string fontPath = resourcePath + "interface/fonts/DejaVuSans.ttf";
		nvgCreateFont(m_ctx, "dejavu", fontPath.c_str());
		nvgFontSize(m_ctx, 14.0f);
		nvgFontFace(m_ctx, "dejavu");

		if(m_ctx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}
	}

	NanoWindow::~NanoWindow()
	{
		for(Image& image : m_images)
			nvgDeleteImage(m_ctx, image.d_index);

#if NANOVG_GL2
		nvgDeleteGL2(m_ctx);
#elif NANOVG_GL3
		nvgDeleteGL3(m_ctx);
#elif NANOVG_GLES2
		nvgDeleteGLES2(m_ctx);
#endif
	}

	NVGcolor nvgColor(const Colour& colour)
	{
		return nvgRGBAf(colour.r(), colour.g(), colour.b(), colour.a());
	}

	void NanoWindow::nextFrame(double time, double delta)
	{
		float pixelRatio = 1.f;

		Stencil::sDebugBatch = 0;
		nvgBeginFrame(m_ctx, m_uiWindow.width(), m_uiWindow.height(), pixelRatio);

		MasterLayer& rootLayer = m_uiWindow.rootSheet().layer();
		rootLayer.nextFrame(0, 0);

#ifdef KIUI_DRAW_CACHE
		void* layerCache = nullptr;
		m_renderer->layerCache(rootLayer, layerCache);
		m_renderer->drawLayer(layerCache, 0, 0);

		for(Layer* layer : rootLayer.layers())
			if(layer->visible())
			{
				m_renderer->layerCache(*layer, layerCache);
				m_renderer->drawLayer(layerCache, 0, 0);
			}
#endif

		/*nvgGlobalCompositeOperation(ctx(), NVG_SOURCE_IN);

		// clipping shape
		nvgBeginPath(ctx());
		nvgRoundedRect(ctx(), 115, 35, 304, 156, 10);
		nvgFillColor(ctx(), nvgColor(Colour::Black));
		nvgFill(ctx());

		// filling whole screen with red, we want that clipped into the previous shape
		// nvgBeginPath(ctx()); // when calling nvgBeginPath() between two shapes NVG_SOURCE_IN doesn't seem to be applied
		nvgRect(ctx(), 0, 0, m_uiWindow.width(), m_uiWindow.height());
		nvgFillColor(ctx(), nvgColor(Colour::Red));
		nvgFill(ctx());
		nvgClosePath(ctx());

		nvgGlobalCompositeOperation(ctx(), NVG_SOURCE_OVER);*/

		nvgEndFrame(m_ctx);

		static double prevtime = 0.0;
		if(time - prevtime > 1.0)
		{
			//std::cerr << "Frames drawn : " << Stencil::sDebugBatch << std::endl;
			prevtime = time;
		}
	}
}
