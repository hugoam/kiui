//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DRAWFRAME_H
#define TOY_DRAWFRAME_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Image.h>

namespace toy
{
	class TOY_UI_EXPORT Icon : public Object
	{
	public:
		Icon(Frame& frame);

		Image* image() { return m_image; }
		void setImage(Image* image);

		DimFloat contentSize() { return{ float(m_image->d_width), float(m_image->d_height) }; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		Frame& d_frame;
		Image* m_image;
	};
}

#endif
