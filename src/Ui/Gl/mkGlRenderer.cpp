//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TOY_GL

#ifdef NANOVG_GLEW
	#include <glew.h>
#elif defined(KIUI_EMSCRIPTEN)
	#define GL_GLEXT_PROTOTYPES
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkGlRenderer.h>

#include <Ui/Frame/mkLayer.h>
#include <Ui/mkUiWindow.h>

#include <iostream>

namespace mk
{
	GlRenderer::GlRenderer(const string& resourcePath)
		: GlNanoRenderer(resourcePath)
		, m_clock()
	{
		this->init();
	}

	GlRenderer::~GlRenderer()
	{
	}

	void GlRenderer::init()
	{
		initGlew();
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

	void GlRenderer::render(MasterLayer& masterLayer)
	{
		this->logFPS();

		if(masterLayer.target().gammaCorrected())
			glDisable(GL_FRAMEBUFFER_SRGB);

		// Update and render
		glViewport(0, 0, masterLayer.width(), masterLayer.height());

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		NanoRenderer::render(masterLayer);

		if(masterLayer.target().gammaCorrected())
			glEnable(GL_FRAMEBUFFER_SRGB);
	}

	void GlRenderer::logFPS()
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

		++frames;
	}
}

#endif