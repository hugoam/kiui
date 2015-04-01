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
		//std::cerr << "ink :: draw " << mFrame->style()->name() << std::endl;

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
			this->drawSkinImage(mSkin, fskin.d_inleft, fskin.d_top, fskin.d_inwidth, imgskin.d_topIn, -imgskin.d_leftIn, 0.f, width); // Top
			this->drawSkinImage(mSkin, fskin.d_inright, fskin.d_intop, imgskin.d_rightIn, fskin.d_inheight, -(imgskin.d_leftIn + imgskin.d_fillWidth), -imgskin.d_topIn, 0.f, height); // Right
			this->drawSkinImage(mSkin, fskin.d_inleft, fskin.d_inbottom, fskin.d_inwidth, imgskin.d_bottomIn, -imgskin.d_leftIn, -(imgskin.d_topIn + imgskin.d_fillHeight), width); // Bottom
			this->drawSkinImage(mSkin, fskin.d_left, fskin.d_intop, imgskin.d_leftIn, fskin.d_inheight, 0.f, -imgskin.d_topIn, 0.f, height); // Left

			// Corners
			this->drawSkinImage(mSkin, fskin.d_outleft, fskin.d_outtop, imgskin.d_leftIn + imgskin.d_leftOut, imgskin.d_topIn + imgskin.d_topOut, 0.f, 0.f); // TopLeft
			this->drawSkinImage(mSkin, fskin.d_inright, fskin.d_outtop, imgskin.d_rightIn + imgskin.d_rightOut, imgskin.d_topIn + imgskin.d_topOut, -(imgskin.d_leftIn + imgskin.d_fillWidth), 0.f); // TopRight
			this->drawSkinImage(mSkin, fskin.d_inright, fskin.d_inbottom, imgskin.d_rightIn + imgskin.d_rightOut, imgskin.d_bottomIn + imgskin.d_bottomOut, -(imgskin.d_leftIn + imgskin.d_fillWidth), -(imgskin.d_topIn + imgskin.d_fillHeight));
			this->drawSkinImage(mSkin, fskin.d_outleft, fskin.d_inbottom, imgskin.d_leftIn + imgskin.d_leftOut, imgskin.d_bottomIn + imgskin.d_bottomOut, 0.f, -(imgskin.d_topIn + imgskin.d_fillHeight));

			// Fill
			this->drawSkinImage(mSkin, fskin.d_inleft, fskin.d_intop, fskin.d_inwidth, fskin.d_inheight, -imgskin.d_leftIn, -imgskin.d_topIn, width, height);
		}

		// Caption
		if(!mFrame->widget()->label().empty() && !(pwidth <= 0.f || pheight <= 0.f))
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
		if(mImage)
		{
			int width, height;
			nvgImageSize(mCtx, mImage, &width, &height);

			return dim == DIM_X ? float(width) : float(height);
		}
		else if(!mFrame->widget()->label().empty())
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

	size_t NanoInk::caretIndex(float x, float y)
	{
		return 0;
	}

	void NanoInk::caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight)
	{}

	void NanoInk::updateContent()
	{

	}

	void NanoInk::updateStyle()
	{
		if(mFrame->inkstyle()->mEmpty)
			return;

		const string& image = mFrame->widget()->image();

		if(!image.empty())
			mImage = fetchImage(image);

		if(!mFrame->inkstyle()->mImageSkin.null())
		{
			ImageSkin& imgskin = mFrame->inkstyle()->mImageSkin;

			if(!imgskin.d_image.empty())
			{
				mSkin = fetchImage(imgskin.d_image);
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

	void NanoInk::drawSkinImage(int image, float left, float top, float width, float height, float x, float y, float stretchwidth, float stretchheight)
	{
		int imgwidth, imgheight;
		nvgImageSize(mCtx, image, &imgwidth, &imgheight);

		if(stretchwidth > 0.f)
		{
			float ratio = stretchwidth / mFrame->inkstyle()->mImageSkin.d_fillWidth; //float(imgwidth);
			x *= ratio;
			imgwidth *= ratio;
		}
		if(stretchheight > 0.f)
		{
			float ratio = stretchheight / mFrame->inkstyle()->mImageSkin.d_fillHeight; //float(imgheight);
			y *= ratio;
			imgheight *= ratio;
		}

		NVGpaint imgPaint = nvgImagePattern(mCtx, left + x, top + y, imgwidth, imgheight, 0.0f / 180.0f*NVG_PI, image, 1.f);
		nvgBeginPath(mCtx);
		nvgRect(mCtx, left, top, width, height);
		nvgFillPaint(mCtx, imgPaint);
		nvgFill(mCtx);
	}
}
