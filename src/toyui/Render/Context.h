//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CONTEXT_H
#define TOY_CONTEXT_H

/* toy */
#include <toyobj/Object.h>
#include <toyui/Types.h>
#include <toyui/Render/RenderWindow.h>
#include <toyui/Input/InputDispatcher.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT RenderSystem : public Object
	{
	public:
		RenderSystem(const string& resourcePath, bool manualRender);

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen) = 0;
		virtual object_ptr<Renderer> createRenderer(Context& context) = 0;

	public:
		const string m_resourcePath;
		const bool m_manualRender;
	};

	class _refl_ TOY_UI_EXPORT Context : public Object
	{
	public:
		Context(RenderSystem& renderSystem, object_ptr<RenderWindow> renderWindow, object_ptr<InputWindow> inputWindow);
		~Context();

	public:
		object_ptr<RenderWindow> m_renderWindow;
		object_ptr<InputWindow> m_inputWindow;

		RenderSystem& m_renderSystem;
		const string m_resourcePath;
	};

}

#endif
