//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Context.h>

namespace toy
{
	RenderSystem::RenderSystem(const string& resourcePath, bool manualRender)
		: m_resourcePath(resourcePath)
		, m_manualRender(manualRender)
	{}

	Context::Context(RenderSystem& renderSystem, object_ptr<RenderWindow> renderWindow, object_ptr<InputWindow> inputWindow)
		: m_renderWindow(std::move(renderWindow))
		, m_inputWindow(std::move(inputWindow))
		, m_renderSystem(renderSystem)
		, m_resourcePath(renderSystem.m_resourcePath)
	{}

	Context::~Context()
	{}

}
