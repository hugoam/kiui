//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DRAWFRAME_H
#define TOY_DRAWFRAME_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
#include <toyui/Frame/Dim.h>
#include <toyui/Image.h>

namespace toy
{
	class TOY_UI_EXPORT Icon : public Object
	{
	public:
		Icon(Frame& frame);

		void setImage(Image* image);

		DimFloat contentSize() { return { float(m_image->d_width), float(m_image->d_height) }; }

	public:
		Frame& d_frame;
		Image* m_image;
	};
}

#endif
