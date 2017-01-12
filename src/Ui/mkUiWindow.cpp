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

	UiWindow::UiWindow(const string& resourcePath, User* user)
		: m_resourcePath(resourcePath)
		, m_images()
		, m_atlas(1024, 1024)
		, m_styler(make_unique<Styler>())
		, m_shutdownRequested(false)
		, m_rootSheet(nullptr)
		, m_user(user)
		, m_renderWindow(nullptr)
		, m_inputWindow(nullptr)
	{
		this->initResources();
	}

	UiWindow::~UiWindow()
	{
		for(Image& image : m_images)
			m_renderer->unloadImage(image);

		m_rootSheet->clear();
	}

	void UiWindow::setup(RenderWindow& renderWindow, InputWindow& inputWindow, Renderer& renderer)
	{
		m_renderWindow = &renderWindow;
		m_inputWindow = &inputWindow;
		m_renderer = &renderer;

		m_width = float(renderWindow.width());
		m_height = float(renderWindow.height());

		m_styler->defaultLayout();
		m_styler->defaultSkins();

		this->init();
	}

	void UiWindow::init()
	{
		m_renderer->setupContext();

		m_atlas.generateAtlas(m_images);

		for(Image& image : m_images)
			m_renderer->loadImage(image);

		m_renderer->loadImageRGBA(m_atlas.image(), m_atlas.data());

		m_styler->prepare();

		m_rootSheet = make_unique<RootSheet>(*this);
		m_rootDevice = make_unique<RootDevice>(*this, *m_rootSheet);

		m_mouse = make_unique<Mouse>(*m_rootSheet);
		m_keyboard = make_unique<Keyboard>(*m_rootSheet);

		m_inputWindow->initInput(*m_mouse, *m_keyboard, m_renderWindow->handle());

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

		if(m_inputWindow)
			m_inputWindow->resize(width, height);

		if(m_rootSheet)
			m_rootSheet->frame().setSize(float(width), float(height));
	}

	bool UiWindow::nextFrame()
	{
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
