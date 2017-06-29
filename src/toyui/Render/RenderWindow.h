//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RENDERWINDOW_H
#define TOY_RENDERWINDOW_H

#include <toyobj/Type.h>
#include <toyobj/String/String.h>

namespace toy
{
	class TOY_UI_EXPORT RenderWindow : public Object
	{
	public:
		RenderWindow(const string& title, int width, int height, bool fullScreen = false)
			: m_title(title)
			, m_width(width)
			, m_height(height)
			, m_fullScreen(fullScreen)
			, m_handle(0)
			, m_nativeHandle(nullptr)
			, m_nativeTarget(nullptr)
			, m_resized(false)
			, m_active(true)
			, m_shutdown(false)
		{}

		virtual bool nextFrame() = 0;

		static Type& cls() { static Type ty; return ty; }

	public:
		string m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_fullScreen;
		size_t m_handle;
		void* m_nativeHandle;
		void* m_nativeTarget;

		bool m_resized;
		bool m_active;
		bool m_shutdown;
	};
}

#endif
