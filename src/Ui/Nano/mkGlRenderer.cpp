//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

//#define NANOVG_GL_USE_UNIFORMBUFFER 1
#ifdef NANOVG_GLEW
#include <Ui/Nano/nanovg/glew.h>
#elif defined(KIUI_EMSCRIPTEN)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkGlRenderer.h>

#include <Ui/mkUiWindow.h>

#include <iostream>

#ifndef KIUI_EMSCRIPTEN
#define CAP_FRAMERATE
#endif

#ifdef CAP_FRAMERATE
#include <thread>
#endif

namespace mk
{
	GlRenderer::GlRenderer(UiWindow& uiWindow, RenderWindow& renderWindow)
		: m_uiWindow(uiWindow)
		, m_renderWindow(renderWindow)
		, m_resourcePath("../data/")
	{
		this->initContext();
	}

	GlRenderer::~GlRenderer()
	{
	}

	void GlRenderer::initContext()
	{
		initGlew();

		m_nanoWindow = make_unique<NanoWindow>(m_uiWindow, m_resourcePath);
	}

	void GlRenderer::initGlew()
	{
#ifdef NANOVG_GLEW
		glewExperimental = true;

		if(glewInit() != GLEW_OK) {
			printf("Could not init glew.\n");
			return;
		}
#endif
	}

	void GlRenderer::renderFrame()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		double delta = time - prevtime;
		if(time - prevtime >= 4.f)
		{
			printf("fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		// if (gammaCorrection)
		glDisable(GL_FRAMEBUFFER_SRGB);

		// Update and render
		glViewport(0, 0, m_uiWindow.width(), m_uiWindow.height());

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClear(GL_STENCIL_BUFFER_BIT);

		m_nanoWindow->nextFrame(time, delta);

		// if (gammaCorrection)
		glEnable(GL_FRAMEBUFFER_SRGB);

		++frames;
	}
}
