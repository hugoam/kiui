//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkRenderer.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/mkUiWindow.h>

namespace mk
{
	RenderTarget::RenderTarget(Renderer& renderer, MasterLayer& masterLayer)
		: m_renderer(renderer)
		, m_masterLayer(masterLayer)
	{}

	void RenderTarget::render()
	{
		Renderer& renderer = m_masterLayer.widget().uiWindow().renderer();
		renderer.render(m_masterLayer);
	}

	Renderer::Renderer(UiWindow& uiWindow)
		: m_uiWindow(uiWindow)
	{
		DrawFrame::sRenderer = this;
	}
}
