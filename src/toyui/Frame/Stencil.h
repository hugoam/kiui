//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_STENCIL_H
#define TOY_STENCIL_H

/* toy Front */
#include <toyobj/Indexer.h>
#include <toyobj/Util/NonCopy.h>
#include <toyui/Forward.h>
#include <toyui/Frame/Renderer.h>
#include <toyui/Style/ImageSkin.h>

namespace toy
{
	class TOY_UI_EXPORT Stencil
	{
	public:
		Stencil(Frame& frame);
		~Stencil();

		void redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect);

		void drawSkinImage(Renderer& target, ImageSkin::Section section, int left, int top, int width, int height);

		void setHardClip(const BoxFloat& hardClip);

	protected:
		Frame& m_frame;

		BoxFloat m_hardClip;
	};
}

#endif
