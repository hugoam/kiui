//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TOY_GL

#include <Ui/mkUiConfig.h>
#include <Ui/Gl/mkGlNanoRenderer.h>

#ifdef NANOVG_GLEW
	#include <GL/glew.h>
#elif KIUI_EMSCRIPTEN
	#define GL_GLEXT_PROTOTYPES
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif

#include <nanovg.h>

#if KIUI_EMSCRIPTEN
	#define NANOVG_GLES2_IMPLEMENTATION
	//#define NANOVG_GL_USE_UNIFORMBUFFER 1
#else
	#define NANOVG_GL3_IMPLEMENTATION
	//#define NANOVG_GL_USE_UNIFORMBUFFER 1
#endif

#include <Ui/Nano/nanovg/nanovg_gl.h>

namespace mk
{
	GlNanoRenderer::GlNanoRenderer(const string& resourcePath)
		: NanoRenderer(resourcePath)
	{}

	GlNanoRenderer::~GlNanoRenderer()
	{}

	void GlNanoRenderer::setupContext()
	{
#if NANOVG_GL2
		m_ctx = nvgCreateGL2(NVG_ANTIALIAS);
#elif NANOVG_GL3
		m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#elif NANOVG_GLES2
		m_ctx = nvgCreateGLES2(NVG_STENCIL_STROKES);
#endif

		if(m_ctx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}
	}

	void GlNanoRenderer::releaseContext()
	{
#if NANOVG_GL2
		nvgDeleteGL2(m_ctx);
#elif NANOVG_GL3
		nvgDeleteGL3(m_ctx);
#elif NANOVG_GLES2
		nvgDeleteGLES2(m_ctx);
#endif

		m_ctx = nullptr;
	}
}

#endif