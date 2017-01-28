//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RENDERWINDOW_H
#define TOY_RENDERWINDOW_H

#include <toyobj/String/String.h>

namespace toy
{
	class TOY_UI_EXPORT RenderWindow
	{
	public:
		RenderWindow(const string& title, int width, int height, size_t handle)
			: m_title(title)
			, m_width(width)
			, m_height(height)
			, m_handle(handle)
			, m_nativeHandle(nullptr)
			, m_resized(false)
			, m_active(true)
			, m_shutdown(false)
		{}

		virtual bool nextFrame() = 0;

		string title() { return m_title; }
		
		unsigned int width() { return m_width; }
		unsigned int height() { return m_height; }

		size_t handle() { return m_handle; }
		void* nativeHandle() { return m_nativeHandle; }

		bool resized() { return m_resized; }
		bool active() { return m_active; }
		bool shutdown() { return m_shutdown; }

	protected:
		string m_title;
		unsigned int m_width;
		unsigned int m_height;
		size_t m_handle;
		void* m_nativeHandle;

		bool m_resized;
		bool m_active;
		bool m_shutdown;
	};
}

#endif
