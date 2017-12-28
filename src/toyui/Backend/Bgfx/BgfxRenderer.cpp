//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Backend/Bgfx/BgfxRenderer.h>

#include <nanovg_bgfx.h>

#define NANOVG_NULL_IMPLEMENTATION
#include <nanovg_null.h>

namespace toy
{
	BgfxUiRenderer::BgfxUiRenderer(const string& resourcePath)
		: NanoRenderer(resourcePath)
	{
		//m_null = true;
	}

	void BgfxUiRenderer::setupContext()
	{
		if(m_null)
			m_ctx = nvgCreateNull();
		else
			m_ctx = nvgCreate(1, 255);

		if(m_ctx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}
	}

	void BgfxUiRenderer::releaseContext()
	{
		if(m_null)
			nvgDeleteNull(m_ctx);
		else
			nvgDelete(m_ctx);
		m_ctx = nullptr;
	}
}
