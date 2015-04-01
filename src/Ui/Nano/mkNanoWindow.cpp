//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Nano/mkNanoInk.h>

#include <Ui/Widget/mkWidget.h>

#include <Object/Util/mkMake.h>

//#define NANOVG_GL_USE_UNIFORMBUFFER 1
#define GLEW_STATIC
#define NANOVG_GLEW
#ifdef NANOVG_GLEW
#   include <Ui/Nano/nanovg/glew.h>
#endif

#include <Ui/Nano/nanovg/nanovg.h>
#define NANOVG_GL2_IMPLEMENTATION
#include <Ui/Nano/nanovg/nanovg_gl.h>

namespace mk
{
	NanoLayer::NanoLayer(Frame* frame, NanoTarget* target, size_t index)
		: InkLayer(target)
		, mTarget(target)
		, mIndex(index)
		, mVisible(true)
		, mFrame(frame)
	{}

	NanoLayer::~NanoLayer()
	{
		mTarget->removeLayer(this);
	}

	unique_ptr<Inkbox> NanoLayer::inkbox(Frame* frame)
	{
		return make_unique<NanoInk>(frame, this);
	}

	void NanoLayer::show()
	{
		mVisible = true;
		mFrame->inkbox()->show();
		//this->moveToTop();
	}

	void NanoLayer::hide()
	{
		mVisible = false;
		mFrame->inkbox()->hide();
	}

	void NanoLayer::moveToTop()
	{
		mTarget->moveToTop(this);
		mIndex = mTarget->zmax();
	}

	void NanoLayer::nanodraw()
	{
		this->draw(mFrame);
	}

	void NanoLayer::draw(Frame* frame)
	{
		static_cast<NanoInk*>(frame->inkbox())->nanodraw();

		if(frame->frameType() >= STRIPE)
			for(Frame* subframe : frame->as<Stripe>()->contents())
				this->draw(subframe);
	}

	NanoTarget::NanoTarget(NanoWindow* window)
		: mWindow(window)
		, mZMax(0)
	{
		mLayers.resize(16);
	}

	void NanoTarget::nanodraw()
	{
		for(auto& layers : mLayers)
			for(NanoLayer* layer : layers)
				if(layer->visible())
					layer->nanodraw();
	}

	void NanoTarget::moveToTop(NanoLayer* layer)
	{
		this->removeLayer(layer);
		mLayers[mZMax].push_back(layer);
	}

	unique_ptr<InkLayer> NanoTarget::layer(Frame* frame, size_t z)
	{
		if(z == 0) z = mZMax++;
		unique_ptr<NanoLayer> layer = make_unique<NanoLayer>(frame, this, z);
		mLayers[z].push_back(layer.get());
		return std::move(layer);
	}

	void NanoTarget::removeLayer(NanoLayer* layer)
	{
		mLayers[layer->index()].erase(std::remove(mLayers[layer->index()].begin(), mLayers[layer->index()].end(), layer), mLayers[layer->index()].end());
	}

	std::map<string, int> NanoWindow::sImages;

	NanoWindow::NanoWindow(size_t width, size_t height, float pixelRatio, string ressourcePath)
		: mWidth(width)
		, mHeight(height)
		, mPixelRatio(pixelRatio)
		, mRessourcePath(ressourcePath)
		, mCtx(nullptr)
	{
		string fontPath = ressourcePath + "/fonts/DejaVuSans.ttf";
		mCtx = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES); // | NVG_DEBUG);
		nvgCreateFont(mCtx, "dejavu", fontPath.c_str());
		nvgFontSize(mCtx, 14.0f);
		nvgFontFace(mCtx, "dejavu");

		if(mCtx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}

		mScreenTarget = make_unique<NanoTarget>(this);
	}

	NanoWindow::~NanoWindow()
	{
		for(auto& kv : sImages)
			nvgDeleteImage(mCtx, kv.second);

		nvgDeleteGL2(mCtx);
	}

	void NanoWindow::nextFrame()
	{
		nvgBeginFrame(mCtx, mWidth, mHeight, mPixelRatio);

		mScreenTarget->nanodraw();

		nvgEndFrame(mCtx);
	}

	InkTarget* NanoWindow::screenTarget()
	{
		return mScreenTarget.get();
	}
}
