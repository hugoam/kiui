//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiWindow.h>

#include <Ui/mkUiLayout.h>

#include <Object/String/mkString.h>
#include <Object/Util/mkUnique.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Controller/mkController.h>

#include <Ui/Nano/nanovg/stb_image.h>
#include <dirent.h>

#include <iostream>

namespace mk
{
	UiContext::UiContext(const string& resourcePath)
		: m_resourcePath(resourcePath)
	{}

	void spritesInFolder(std::vector<Image>& images, const string& path, const string& subfolder)
	{
		DIR* dir = opendir(path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
			{
				string fullpath = path + ent->d_name;
				string name = subfolder + replaceAll(ent->d_name, ".png", "");

				if(subfolder != "")
					int i = 0;
				int width, height, n;
				unsigned char* img = stbi_load(fullpath.c_str(), &width, &height, &n, 4);
				stbi_image_free(img);

				images.emplace_back(name, fullpath, width, height);
			}
				

		closedir(dir);
	}

	UiWindow::UiWindow(UiContext& context, const string& name, int width, int height, bool fullScreen, User* user)
		: m_context(context)
		, m_resourcePath(context.resourcePath())
		, m_renderWindow(context.createRenderWindow(name, width, height, fullScreen))
		, m_inputWindow(context.createInputWindow(*m_renderWindow))
		, m_renderer(context.createRenderer(m_resourcePath))
		, m_images()
		, m_atlas(1024, 1024)
		, m_width(m_renderWindow->width())
		, m_height(m_renderWindow->height())
		, m_styler(make_unique<Styler>())
		, m_shutdownRequested(false)
		, m_rootSheet(nullptr)
		, m_user(user)
	{
		this->initResources();
		this->init();
	}

	UiWindow::~UiWindow()
	{
		for(Image& image : m_images)
			m_renderer->unloadImage(image);

		m_rootSheet->clear();
	}

	void UiWindow::init()
	{
		m_renderer->setupContext();

		this->loadResources();

		m_styler->defaultLayout();
		m_styler->defaultSkins();

		m_styler->prepare();

		m_rootSheet = make_unique<RootSheet>(*this);
		m_rootDevice = make_unique<RootDevice>(*this, *m_rootSheet);

		m_mouse = make_unique<Mouse>(*m_rootSheet);
		m_keyboard = make_unique<Keyboard>(*m_rootSheet);

		m_inputWindow->initInput(*m_mouse, *m_keyboard);

		m_rootSheet->frame().setSize(m_width, m_height);

		this->resize(size_t(m_width), size_t(m_height));
	}

	void UiWindow::initResources()
	{
		string spritePath = m_resourcePath + "interface/uisprites/";

		DIR* dir = opendir(spritePath.c_str());
		dirent* ent;

		spritesInFolder(m_images, spritePath, "");

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
				spritesInFolder(m_images, spritePath + ent->d_name + "/", string(ent->d_name) + "/");

		closedir(dir);
	}

	void UiWindow::loadResources()
	{
		m_renderer->loadFont();

		m_atlas.generateAtlas(m_images);

		for(Image& image : m_images)
			m_renderer->loadImage(image);

		m_renderer->loadImageRGBA(m_atlas.image(), m_atlas.data());
	}

	Image& UiWindow::createImage(const string& name, int width, int height, uint8_t* data)
	{
		m_images.emplace_back(name, name, width, height);
		Image& image = m_images.back();
		m_renderer->loadImageRGBA(image, data);
		return image;
	}

	void UiWindow::resize(size_t width, size_t height)
	{
		m_width = float(width);
		m_height = float(height);

		m_inputWindow->resize(width, height);

		m_rootSheet->frame().setSize(float(width), float(height));
	}

	bool UiWindow::nextFrame()
	{
		if(m_renderWindow->width() != size_t(m_width) 
		|| m_renderWindow->height() != size_t(m_height))
			this->resize(m_renderWindow->width(), m_renderWindow->height());

		// if(manualRender)
		m_rootSheet->layer().target().render();
		// add sub layers

		m_renderWindow->nextFrame();
		m_inputWindow->nextFrame();

		size_t tick = m_clock.readTick();
		size_t delta = m_clock.stepTick();

		m_mouse->nextFrame();
		m_keyboard->nextFrame();

		m_rootSheet->layer().nextFrame(tick, delta);

		return !m_shutdownRequested;
	}

	void UiWindow::shutdown()
	{
		m_shutdownRequested = true;
	}

	void UiWindow::handleDestroyWidget(Widget& widget)
	{
		m_mouse->handleDestroyWidget(widget);
	}
}
