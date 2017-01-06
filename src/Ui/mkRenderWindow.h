//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_RENDERWINDOW_H
#define MK_RENDERWINDOW_H

namespace mk
{
	class MK_UI_EXPORT RenderWindow
	{
	public:
		RenderWindow(unsigned int width, unsigned int height, string title, size_t handle)
			: m_width(width)
			, m_height(height)
			, m_title(title)
			, m_handle(handle)
			, m_resized(false)
			, m_active(true)
			, m_shutdown(false)
		{}
		
		size_t handle() { return m_handle; }
		
		unsigned int width() { return m_width; }
		unsigned int height() { return m_height; }

		bool resized() { return m_resized; }
		bool active() { return m_active; }
		bool shutdown() { return m_shutdown; }

	protected:
		unsigned int m_width;
		unsigned int m_height;
		string m_title;
		size_t m_handle;

		bool m_resized;
		bool m_active;
		bool m_shutdown;
	};
}

#endif
