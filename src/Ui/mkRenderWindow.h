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
			: mWidth(width)
			, mHeight(height)
			, mTitle(title)
			, mHandle(handle)
			, mResized(false)
			, mActive(true)
			, mShutdown(false)
		{}
		
		size_t handle() { return mHandle; }
		
		unsigned int width() { return mWidth; }
		unsigned int height() { return mHeight; }

		bool resized() { return mResized; }
		bool active() { return mActive; }
		bool shutdown() { return mShutdown; }

	protected:
		unsigned int mWidth;
		unsigned int mHeight;
		string mTitle;
		bool mResized;
		bool mActive;
		bool mShutdown;

		size_t mHandle;
	};
}

#endif
