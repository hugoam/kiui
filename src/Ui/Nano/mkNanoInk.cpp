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
		, mCtx(layer->target()->window()->ctx())
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

		float left = floor(mFrame->dabsolute(DIM_X) + mFrame->dclippos(DIM_X) + mFrame->inkstyle()->mMargin[DIM_X]);
		float top = floor(mFrame->dabsolute(DIM_Y) + mFrame->dclippos(DIM_Y) + mFrame->inkstyle()->mMargin[DIM_Y]);

		float width = floor(mFrame->dclipsize(DIM_X) - mFrame->inkstyle()->mMargin[DIM_X] - mFrame->inkstyle()->mMargin[DIM_X + 2]);
		float height = floor(mFrame->dclipsize(DIM_Y) - mFrame->inkstyle()->mMargin[DIM_Y] - mFrame->inkstyle()->mMargin[DIM_Y + 2]);

		float pleft = left + mFrame->inkstyle()->mPadding[DIM_X];
		float ptop = top + mFrame->inkstyle()->mPadding[DIM_Y];
		float pwidth = width - 2.f * mFrame->inkstyle()->mPadding[DIM_X];
		float pheight = height - 2.f * mFrame->inkstyle()->mPadding[DIM_Y];

		//float clipleft = left + mFrame->dclippos(DIM_X);
		//float cliptop = top + mFrame->dclippos(DIM_Y);

		//std::cerr << "ink :: draw " << mFrame->style()->name() << " at " << left << " , " << top << " size " << width << " , " << height << std::endl;

		// Rect

		if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
			nvgScissor(mCtx, left, top, width, height);

		nvgBeginPath(mCtx);

		if(mFrame->inkstyle()->mCornerRadius.null())
			nvgRect(mCtx, left, top, width, height);
		else
			//nvgRoundedRect4(mCtx, left, top, width, height, mFrame->inkstyle()->mCornerRadius.x(), mFrame->inkstyle()->mCornerRadius.y(), mFrame->inkstyle()->mCornerRadius.z(), mFrame->inkstyle()->mCornerRadius.w());
			nvgRoundedRect(mCtx, left, top, width, height, mFrame->inkstyle()->mCornerRadius.x());

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

		// ImageSkin
		if(!mFrame->inkstyle()->mImageSkin.null())
		{
			ImageSkin& imgskin = mFrame->inkstyle()->mImageSkin;
			FrameSkin fskin(mFrame, &imgskin);

			// Borders
			this->drawImage(mTop, fskin.d_inleft, fskin.d_top, fskin.d_inwidth, imgskin.d_topIn); // Top
			this->drawImage(mRight, fskin.d_inright, fskin.d_intop, imgskin.d_rightIn, fskin.d_inheight); // Right

			this->drawImage(mBottom, fskin.d_inleft, fskin.d_inbottom, fskin.d_inwidth, imgskin.d_bottomIn); // Bottom
			this->drawImage(mLeft, fskin.d_left, fskin.d_intop, imgskin.d_leftIn, fskin.d_inheight); // Left

			// Corners
			this->drawImage(mTopLeft, fskin.d_outleft, fskin.d_outtop, imgskin.d_leftIn + imgskin.d_leftOut, imgskin.d_topIn + imgskin.d_topOut);
			this->drawImage(mTopRight, fskin.d_inright, fskin.d_outtop, imgskin.d_rightIn + imgskin.d_rightOut, imgskin.d_topIn + imgskin.d_topOut);
			this->drawImage(mBottomRight, fskin.d_inright, fskin.d_inbottom, imgskin.d_rightIn + imgskin.d_rightOut, imgskin.d_bottomIn + imgskin.d_bottomOut);
			this->drawImage(mBottomLeft, fskin.d_outleft, fskin.d_inbottom, imgskin.d_leftIn + imgskin.d_leftOut, imgskin.d_bottomIn + imgskin.d_bottomOut);

			// Fill
			this->drawImage(mFill, fskin.d_inleft, fskin.d_intop, fskin.d_inwidth, fskin.d_inheight);
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

		const string& image = mFrame->widget()->image();

		if(image != "")
			mImage = fetchImage(image);

		if(!mFrame->inkstyle()->mImageSkin.null())
		{
			ImageSkin& imgskin = mFrame->inkstyle()->mImageSkin;

			mTop = fetchImage(imgskin.d_top);
			mRight = fetchImage(imgskin.d_right);
			mBottom = fetchImage(imgskin.d_bottom);
			mLeft = fetchImage(imgskin.d_left);

			mTopLeft = fetchImage(imgskin.d_topLeft);
			mTopRight = fetchImage(imgskin.d_topRight);
			mBottomRight = fetchImage(imgskin.d_bottomRight);
			mBottomLeft = fetchImage(imgskin.d_bottomLeft);

			mFill = fetchImage(imgskin.d_fill);

			if(!imgskin.d_size)
			{
				int unused;
				nvgImageSize(mCtx, mTop, &unused, &imgskin.d_topIn);
				nvgImageSize(mCtx, mRight, &imgskin.d_rightIn, &unused);
				nvgImageSize(mCtx, mBottom, &unused, &imgskin.d_bottomIn);
				nvgImageSize(mCtx, mLeft, &imgskin.d_leftIn, &unused);

				nvgImageSize(mCtx, mTopLeft, &imgskin.d_leftOut, &imgskin.d_topOut);
				nvgImageSize(mCtx, mBottomRight, &imgskin.d_rightOut, &imgskin.d_bottomOut);

				imgskin.d_leftOut -= imgskin.d_leftIn;
				imgskin.d_topOut -= imgskin.d_topIn;
				imgskin.d_bottomOut -= imgskin.d_bottomIn;
				imgskin.d_rightOut -= imgskin.d_rightIn;
			}
		}
	}

	int NanoInk::fetchImage(const string& image)
	{
		auto it = NanoWindow::sImages.find(image);
		if(it != NanoWindow::sImages.end())
			return (*it).second;

		NanoWindow::sImages[image] = nvgCreateImage(mCtx, (mLayer->target()->window()->ressourcePath() + "/uisprites/" + image).c_str(), 0);
		return NanoWindow::sImages[image];
	}

	void NanoInk::updateFrame()
	{
		if(mFrame->inkstyle()->mEmpty || !mVisible || mFrame->dsize(DIM_X) == 0.f || mFrame->dsize(DIM_X) == 0.f)
			return;

	}

	void NanoInk::drawImage(int image, float left, float top, float width, float height)
	{
		NVGpaint imgPaint = nvgImagePattern(mCtx, left, top, width, height, 0.0f / 180.0f*NVG_PI, image, 1.f);
		nvgBeginPath(mCtx);
		nvgRect(mCtx, left, top, width, height);
		nvgFillPaint(mCtx, imgPaint);
		nvgFill(mCtx);
	}
}
