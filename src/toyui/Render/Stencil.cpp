//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Stencil.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>

#include <toyui/UiWindow.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	int Stencil::s_debugBatch = 0;

	Stencil::Stencil(DrawFrame& frame)
		: m_frame(frame)
	{}

	BoxFloat Stencil::selectCorners()
	{
		Frame& frame = m_frame.frame();
		Stripe& parent = *m_frame.frame().parent();

		BoxFloat& corners = parent.style().skin().cornerRadius();
		if(parent.first(frame))
			return parent.length() == DIM_X ? BoxFloat(corners.v0(), 0.f, 0.f, corners.v3()) : BoxFloat(corners.v0(), corners.v1(), 0.f, 0.f);
		else if(parent.last(frame))
			return parent.length() == DIM_X ? BoxFloat(0.f, corners.v1(), corners.v2(), 0.f) : BoxFloat(0.f, 0.f, corners.v2(), corners.v3());
		else 
			return BoxFloat();
	}

	void Stencil::redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect)
	{
		UNUSED(paddedRect);

		if(!m_frame.frame().hardClip().null())
			return;

		s_debugBatch++;

		InkStyle& skin = m_frame.inkstyle();

		// Shadow
		if(!skin.shadow().d_null)
		{
			target.drawShadow(rect, skin.cornerRadius(), skin.shadow());
		}

		// Rect
		if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f))
		{
			BoxFloat cornerRadius = skin.m_weakCorners ? this->selectCorners() : skin.cornerRadius();
			target.drawRect(rect, cornerRadius, skin);
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

			auto func = [this, &target](ImageSkin::Section section, const BoxFloat& rect) { this->drawSkinImage(target, section, rect); };
			imageSkin.stretchCoords(skinRect.x(), skinRect.y(), skinRect.w(), skinRect.h(), func);
		}

		// Image
		if(skin.image())
			target.drawImage(*skin.image(), contentRect);
		if(skin.overlay())
			target.drawImage(*skin.overlay(), contentRect);
		if(skin.tile())
			target.drawImage(*skin.tile(), rect);
	}

	void Stencil::drawSkinImage(Renderer& target, ImageSkin::Section section, BoxFloat rect)
	{
		ImageSkin& imageSkin = m_frame.inkstyle().imageSkin();
		rect.setX(rect.x() - imageSkin.d_margin);
		rect.setY(rect.y() - imageSkin.d_margin);

		float xratio = 1.f;
		float yratio = 1.f;

		if(section == ImageSkin::TOP || section == ImageSkin::BOTTOM || section == ImageSkin::FILL)
			xratio = rect.w() / imageSkin.d_fillWidth;
		if(section == ImageSkin::LEFT || section == ImageSkin::RIGHT || section == ImageSkin::FILL)
			yratio = rect.h() / imageSkin.d_fillHeight;

		target.drawImageStretch(imageSkin.d_images[section], rect, xratio, yratio);
	}
}
