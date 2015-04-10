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

#include <cmath>

namespace mk
{
	inline float clamp(float v, float mn, float mx)
	{
		return (v > mx) ? mx : (v < mn) ? mn : v;
	}

	static float fminf(float a, float b)
	{
		return isnan(a) ? b : (isnan(b) ? a : ((a < b) ? a : b));
	}

	static float fmaxf(float a, float b)
	{
		return isnan(a) ? b : (isnan(b) ? a : ((a > b) ? a : b));
	}

	static double fmin(double a, double b)
	{
		return isnan(a) ? b : (isnan(b) ? a : ((a < b) ? a : b));
	}

	static double fmax(double a, double b)
	{
		return isnan(a) ? b : (isnan(b) ? a : ((a > b) ? a : b));
	}

	void nvgRoundedBox(NVGcontext *ctx, float x, float y, float w, float h, float cr0, float cr1, float cr2, float cr3)
	{
		float d;

		w = fmaxf(0, w);
		h = fmaxf(0, h);
		d = fminf(w, h);

		nvgMoveTo(ctx, x, y + h*0.5f);
		nvgArcTo(ctx, x, y, x + w, y, fminf(cr0, d / 2));
		nvgArcTo(ctx, x + w, y, x + w, y + h, fminf(cr1, d / 2));
		nvgArcTo(ctx, x + w, y + h, x, y + h, fminf(cr2, d / 2));
		nvgArcTo(ctx, x, y + h, x, y, fminf(cr3, d / 2));
		nvgClosePath(ctx);
	}

	NVGcolor nvgColour(const Colour& colour)
	{
		return nvgRGBAf(colour.r(), colour.g(), colour.b(), colour.a());
	}

	NVGcolor nvgOffsetColour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return nvgRGBAf(	clamp(colour.r() + offset, 0, 1),
							clamp(colour.g() + offset, 0, 1),
							clamp(colour.b() + offset, 0, 1),
							colour.a());
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

		if(skin()->mEmpty || !mVisible || mFrame->dclip(DIM_Y) == Frame::HIDDEN || mFrame->dclip(DIM_X) == Frame::HIDDEN)
			return;

		//nvgSave(mCtx);

		float left = floor(mFrame->dabsolute(DIM_X) + mFrame->dclippos(DIM_X) + skin()->mMargin[DIM_X]);
		float top = floor(mFrame->dabsolute(DIM_Y) + mFrame->dclippos(DIM_Y) + skin()->mMargin[DIM_Y]);

		float width = floor(mFrame->dclipsize(DIM_X) - skin()->mMargin[DIM_X] - skin()->mMargin[DIM_X + 2]);
		float height = floor(mFrame->dclipsize(DIM_Y) - skin()->mMargin[DIM_Y] - skin()->mMargin[DIM_Y + 2]);

		float pleft = left + skin()->mPadding[DIM_X];
		float ptop = top + skin()->mPadding[DIM_Y];
		float pwidth = width - 2.f * skin()->mPadding[DIM_X];
		float pheight = height - 2.f * skin()->mPadding[DIM_Y];

		float c0 = mCorners.x();
		float c1 = mCorners.y();
		float c2 = mCorners.z();
		float c3 = mCorners.w();


		//float clipleft = left + mFrame->dclippos(DIM_X);
		//float cliptop = top + mFrame->dclippos(DIM_Y);

		//std::cerr << "ink :: draw " << mFrame->style()->name() << " at " << left << " , " << top << " size " << width << " , " << height << std::endl;

		// Rect

		if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
			nvgScissor(mCtx, left, top, width, height);

		nvgBeginPath(mCtx);

		if(mCorners.null())
			nvgRect(mCtx, left, top, width, height);
		else
			nvgRoundedBox(mCtx, left, top, width, height, c0, c1, c2, c3);

		if(skin()->mBackgroundColour.a() != 0.f)
		{
			if(skin()->mTopdownGradient.null())
			{
				nvgFillColor(mCtx, nvgColour(skin()->mBackgroundColour));
			}
			else
			{
				NVGcolor first = nvgOffsetColour(skin()->mBackgroundColour, skin()->mTopdownGradient.x());
				NVGcolor second = nvgOffsetColour(skin()->mBackgroundColour, skin()->mTopdownGradient.y());
				nvgFillPaint(mCtx, (height > width) ?
					nvgLinearGradient(mCtx, left, top, left + width, top, first, second) :
					nvgLinearGradient(mCtx, left, top, left, top + height, first, second));
			}
			nvgFill(mCtx);
		}
		
		if(skin()->mBorderWidth.x() > 0.f)
		{
			nvgBeginPath(mCtx);
			nvgRoundedBox(mCtx, left + 0.5f, top + 0.5f, width - 1.f, height - 1.f, c0, c1, c2, c3);
			//nvgRoundedRect(mCtx, left + 0.5f, top + 0.5f, width - 1.f, height - 1.f, skin()->mCornerRadius.x());
			nvgStrokeWidth(mCtx, skin()->mBorderWidth.x());
			nvgStrokeColor(mCtx, nvgColour(skin()->mBorderColour));
			nvgStroke(mCtx);
		}

		// Image
		if(mImage)
		{
			NVGpaint imgPaint = nvgImagePattern(mCtx, pleft, ptop, pwidth, pheight, 0.0f / 180.0f*NVG_PI, mImage, 1.f);
			nvgBeginPath(mCtx);
			if(mCorners.null())
				nvgRect(mCtx, left, top, width, height);
			else
				nvgRoundedBox(mCtx, left, top, width, height, c0, c1, c2, c3);
			nvgFillPaint(mCtx, imgPaint);
			nvgFill(mCtx);
		}

		// ImageSkin
		if(!skin()->mImageSkin.null())
		{
			ImageSkin& imgskin = skin()->mImageSkin;
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

			//if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y)) 
			// ^ @note this doesn't work because a frame is set to clipped only by its parent, and not when the label is larger than the frame itself
				nvgScissor(mCtx, pleft, ptop, pwidth, pheight);

			nvgTextAlign(mCtx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
			nvgFillColor(mCtx, nvgColour(skin()->mTextColour));
			nvgText(mCtx, pleft, ptop, mFrame->widget()->label().c_str(), nullptr);

			//if(mFrame->dclip(DIM_X) || mFrame->dclip(DIM_Y))
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
			float height;

			nvgTextBounds(mCtx, 0.f, 0.f, mFrame->widget()->label().c_str(), nullptr, bounds);
			nvgTextMetrics(mCtx, nullptr, nullptr, &height);

			float xoffset = skin()->mPadding[DIM_X] * 2.f;
			float yoffset = skin()->mPadding[DIM_Y] * 2.f;

			//std::cerr << "ink :: contentSize for " << mFrame->style()->name() << " : " << (dim == DIM_X ? " x " : " y ") << (dim == DIM_X ? bounds[2] - bounds[0] + xoffset : bounds[3] - bounds[1] + yoffset) << std::endl;

			return dim == DIM_X ? bounds[2] - bounds[0] + xoffset : height + yoffset;
		}
		
		return 0.f;
	}

	size_t NanoInk::caretIndex(float x, float y)
	{
		return nvgTextGlyphIndex(mCtx, 0.f, 0.f, mFrame->widget()->label().c_str(), nullptr, x);
	}

	void NanoInk::caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight)
	{
		NVGglyphPosition position;
		nvgTextGlyphPosition(mCtx, 0.f, 0.f, mFrame->widget()->label().c_str(), index, &position);
		caretX = skin()->mPadding[DIM_X] + position.x;
		caretY = skin()->mPadding[DIM_Y] + 0.f;
		nvgTextMetrics(mCtx, nullptr, nullptr, &caretHeight);
	}

	void NanoInk::updateContent()
	{

	}

	void NanoInk::updateStyle()
	{
		if(skin()->mEmpty)
			return;

		const string& image = mFrame->widget()->image();

		if(!image.empty())
			mImage = fetchImage(image);

		if(!skin()->mImageSkin.null())
		{
			ImageSkin& imgskin = skin()->mImageSkin;

			if(!imgskin.d_image.empty())
			{
				mSkin = fetchImage(imgskin.d_image);
			}
		}

		mCorners = skin()->mCornerRadius;
	}

	int NanoInk::fetchImage(const string& image)
	{
		auto it = NanoWindow::sImages.find(image);
		if(it != NanoWindow::sImages.end())
			return (*it).second;

		NanoWindow::sImages[image] = nvgCreateImage(mCtx, (mLayer->target()->window()->ressourcePath() + "/uisprites/" + image + ".png").c_str(), 0);
		return NanoWindow::sImages[image];
	}

	void NanoInk::updateFrame()
	{
		if(skin()->mEmpty || !mVisible || mFrame->dsize(DIM_X) == 0.f || mFrame->dsize(DIM_X) == 0.f)
			return;

		NanoInk* parent = static_cast<NanoInk*>(mFrame->parent()->inkbox());
		if(parent->mCorners.null() || !skin()->mWeakCorners)
			return;

		if(mFrame->parent()->layoutDim() == DIM_X)
		{
			mCorners.setX(mFrame->first() ? parent->mCorners.x() : 0.f);
			mCorners.setW(mFrame->first() ? parent->mCorners.w() : 0.f);
			mCorners.setY(mFrame->last() ? parent->mCorners.y() : 0.f);
			mCorners.setZ(mFrame->last() ? parent->mCorners.z() : 0.f);
		}
		else if(mFrame->parent()->layoutDim() == DIM_Y)
		{
			mCorners.setX(mFrame->first() ? parent->mCorners.x() : 0.f);
			mCorners.setY(mFrame->first() ? parent->mCorners.y() : 0.f);
			mCorners.setZ(mFrame->last() ? parent->mCorners.z() : 0.f);
			mCorners.setW(mFrame->last() ? parent->mCorners.w() : 0.f);
		}
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
			float ratio = stretchwidth / skin()->mImageSkin.d_fillWidth; //float(imgwidth);
			x *= ratio;
			imgwidth *= ratio;
		}
		if(stretchheight > 0.f)
		{
			float ratio = stretchheight / skin()->mImageSkin.d_fillHeight; //float(imgheight);
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
