//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STENCIL_H
#define MK_STENCIL_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkRenderer.h>
#include <Ui/Style/mkImageSkin.h>

namespace mk
{
	class MK_UI_EXPORT Stencil
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
