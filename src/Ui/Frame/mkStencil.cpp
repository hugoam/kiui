//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkStencil.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/mkUiWindow.h>
#include <Ui/Widget/mkRootSheet.h>

using namespace std::placeholders;

namespace mk
{
	Stencil::Stencil(Frame& frame)
		: m_frame(frame)
		, m_hardClip()
	{}

	Stencil::~Stencil()
	{}

	void Stencil::setHardClip(const BoxFloat& hardClip)
	{
		m_hardClip = hardClip;
		if(m_frame.parent())
			m_frame.parent()->stencil().setHardClip(hardClip);
	}

	void Stencil::redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect)
	{
		if(!m_hardClip.null())
			return;

		InkStyle& skin = m_frame.inkstyle();

		// Shadow
		if(!skin.shadow().d_null)
		{
			target.drawShadow(rect, skin.cornerRadius(), skin.shadow());
		}

		// Rect
		if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f) && skin.m_weakCorners)
		{
			BoxFloat clipBox(-m_frame.dposition(DIM_X), -m_frame.dposition(DIM_Y), m_frame.parent()->width(), m_frame.parent()->height());
			if(m_frame.widget().style().name() == "FillerX")
				int i = 0;
			target.clipFrame(clipBox, m_frame.parent()->inkstyle().cornerRadius());
		}
		
		if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f))
		{
			target.drawRect(rect, skin.cornerRadius(), skin);
		}

		// ImageSkin
		ImageSkin& imageSkin = skin.imageSkin();
		if(!imageSkin.null())
		{
			BoxFloat skinRect;
			float margin = imageSkin.d_margin * 2.f;

			if(imageSkin.d_stretch == DIM_X)
				skinRect.assign(rect.x(), contentRect.y() + margin, rect.w() + margin, imageSkin.d_height);
			else if(imageSkin.d_stretch == DIM_Y)
				skinRect.assign(contentRect.x() + imageSkin.d_margin, rect.y(), imageSkin.d_width, rect.h() + margin);
			else
				skinRect.assign(rect.x(), rect.y(), rect.w() + margin, rect.h() + margin);

			imageSkin.stretchCoords(skinRect.x(), skinRect.y(), skinRect.w(), skinRect.h(), std::bind(&Stencil::drawSkinImage, this, std::ref(target), _1, _2, _3, _4, _5));
		}

		// Image
		if(skin.image())
			target.drawImage(*skin.image(), contentRect);
		if(skin.overlay())
			target.drawImage(*skin.overlay(), contentRect);
		if(skin.tile())
			target.drawImage(*skin.tile(), rect);
	}

	void Stencil::drawSkinImage(Renderer& target, ImageSkin::Section section, int left, int top, int width, int height)
	{
		ImageSkin& imageSkin = m_frame.inkstyle().imageSkin();
		left -= imageSkin.d_margin;
		top -= imageSkin.d_margin;

		float xratio = 1.f;
		float yratio = 1.f;

		if(section == ImageSkin::TOP || section == ImageSkin::BOTTOM || section == ImageSkin::FILL)
			xratio = float(width) / imageSkin.d_fillWidth;
		if(section == ImageSkin::LEFT || section == ImageSkin::RIGHT || section == ImageSkin::FILL)
			yratio = float(height) / imageSkin.d_fillHeight;

		BoxFloat rect(left, top, width, height);
		target.drawImageStretch(imageSkin.d_images[section], rect, xratio, yratio);
	}
}
