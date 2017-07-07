//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FIGURE_H
#define TOY_FIGURE_H

/* toy */
#include <toyobj/Util/Image.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>

namespace toy
{
	class TOY_UI_EXPORT Figure : public Widget
	{
	public:
		Figure(Wedge& parent, const Image256& source);
		
		virtual void destroyed();

		void updateImage();
		void clearImage();

		static Type& cls() { static Type ty("Figure", Item::cls()); return ty; }

	protected:
		const Image256& m_source;
		Image* m_image;
	};
}

#endif
