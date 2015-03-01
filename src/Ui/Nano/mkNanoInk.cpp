//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoInk.h>

#include <Object/Util/mkColour.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Nano/nanovg/nanovg.h>

#include <iostream>

namespace mk
{
	NVGcolor nvgColour(const Colour& colour)
	{
		return nvgRGBAf(colour.r(), colour.g(), colour.b(), colour.a());
	}

	NanoInk::NanoInk(Frame* frame, NanoLayer* layer)
		: Inkbox(frame)
		, mCtx(layer->target()->ctx())
		, mLayer(layer)
		, mImage(0)
		, mVisible(frame->visible())
	{}

	NanoInk::~NanoInk()
	{}

	void NanoInk::show()
	{
		mVisible = true;
	}

	void NanoInk::hide()
	{
		mVisible = false;
	}

	void NanoInk::nanodraw()
	{
		if(mFrame->inkstyle()->mEmpty || !mVisible || mFrame->dclip(DIM_Y) == Frame::HIDDEN || mFrame->dclip(DIM_X) == Frame::HIDDEN)
			return;

		//nvgSave(mCtx);

		float left = floor(mFrame->dabsolute(DIM_X) + mFrame->inkstyle()->mMargin[DIM_X]);
		float top = floor(mFrame->dabsolute(DIM_Y) + mFrame->inkstyle()->mMargin[DIM_Y]);

		float width = floor(mFrame->dclipsize(DIM_X) - mFrame->inkstyle()->mMargin[DIM_X] * 2.f);
		float height = floor(mFrame->dclipsize(DIM_Y) - mFrame->inkstyle()->mMargin[DIM_Y] * 2.f);

		float pleft = left + mFrame->inkstyle()->mPadding[DIM_X];
		float ptop = top + mFrame->inkstyle()->mPadding[DIM_Y];
		float pwidth = width - 2.f * mFrame->inkstyle()->mPadding[DIM_X];
		float pheight = height - 2.f * mFrame->inkstyle()->mPadding[DIM_Y];

		float clipleft = left + mFrame->dclippos(DIM_X);
		float cliptop = top + mFrame->dclippos(DIM_Y);

		//std::cerr << "ink :: draw " << mFrame->style()->name() << " at " << left << " , " << top << " size " << width << " , " << height << std::endl;

		// Rect

		if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
			nvgScissor(mCtx, clipleft, cliptop, width, height);

		nvgBeginPath(mCtx);

		if(mFrame->inkstyle()->mCornerRadius.null())
			nvgRect(mCtx, left, top, width, height);
		else
			nvgRoundedRect4(mCtx, left, top, width, height, mFrame->inkstyle()->mCornerRadius.x(), mFrame->inkstyle()->mCornerRadius.y(), mFrame->inkstyle()->mCornerRadius.z(), mFrame->inkstyle()->mCornerRadius.w());
			//nvgRoundedRect(mCtx, left, top, width, height, mFrame->inkstyle()->mCornerRadius);

		if(mFrame->inkstyle()->mBackgroundColour.a() != 0.f)
		{
			nvgFillColor(mCtx, nvgColour(mFrame->inkstyle()->mBackgroundColour));
			nvgFill(mCtx);
		}
		
		if(mFrame->inkstyle()->mBorderWidth.x() > 0.f)
		{
			nvgStrokeWidth(mCtx, mFrame->inkstyle()->mBorderWidth.x() / 2.f);
			nvgStrokeColor(mCtx, nvgColour(mFrame->inkstyle()->mBorderColour));
			nvgStroke(mCtx);
		}

		// Image
		if(mImage)
		{
			NVGpaint imgPaint = nvgImagePattern(mCtx, pleft, ptop, pwidth, pheight, 0.0f / 180.0f*NVG_PI, mImage, 1.f);
			nvgBeginPath(mCtx);
			nvgRect(mCtx, left, top, width, height);
			nvgFillPaint(mCtx, imgPaint);
			nvgFill(mCtx);
		}

		// Caption
		if(mFrame->widget()->label() != "" && !(pwidth <= 0.f || pheight <= 0.f))
		{
			nvgFontSize(mCtx, 14.0f);
			nvgFontFace(mCtx, "dejavu");

			if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
				nvgScissor(mCtx, pleft, ptop, pwidth, pheight);

			nvgTextAlign(mCtx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
			nvgFillColor(mCtx, nvgColour(mFrame->inkstyle()->mTextColour));
			nvgText(mCtx, pleft, ptop, mFrame->widget()->label().c_str(), nullptr);

			if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
				nvgResetScissor(mCtx);
		}

		if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
			nvgResetScissor(mCtx);
		
		//nvgRestore(mCtx);
	}

	float NanoInk::contentSize(Dimension dim)
	{
		if(mFrame->widget()->label() != "")
		{
			float bounds[4];

			nvgTextBounds(mCtx, 0.f, 0.f, mFrame->widget()->label().c_str(), nullptr, bounds);

			float xoffset = mFrame->inkstyle()->mPadding[DIM_X] * 2.f;
			float yoffset = mFrame->inkstyle()->mPadding[DIM_Y] * 2.f;

			//std::cerr << "ink :: contentSize for " << mFrame->style()->name() << " : " << (dim == DIM_X ? " x " : " y ") << (dim == DIM_X ? bounds[2] - bounds[0] + xoffset : bounds[3] - bounds[1] + yoffset) << std::endl;

			return dim == DIM_X ? bounds[2] - bounds[0] + xoffset : bounds[3] - bounds[1] + yoffset;
		}
		
		return 0.f;
	}

	void NanoInk::updateContent()
	{

	}

	void NanoInk::updateStyle()
	{
		if(mFrame->inkstyle()->mEmpty || !mVisible)
			return;

		string image = mFrame->widget()->image();

		if(image != "")
		{
			if(NanoWindow::sImages.find(image) == NanoWindow::sImages.end())
				NanoWindow::sImages[image] = nvgCreateImage(mCtx, ("../Data/interface/uisprites/" + image).c_str(), 0);

			mImage = NanoWindow::sImages[image];
		}
	}

	void NanoInk::updateFrame()
	{
		if(mFrame->inkstyle()->mEmpty || !mVisible || mFrame->dsize(DIM_X) == 0.f || mFrame->dsize(DIM_X) == 0.f)
			return;

	}
}
