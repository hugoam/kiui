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

#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkWindow.h>
#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkContextMenu.h>

#include <Ui/Controller/mkController.h>

#include <iostream>

namespace mk
{
	UiWindow::UiWindow(const string& resourcePath, User* user)
		: m_resourcePath(resourcePath)
		, m_styler(make_unique<Styler>())
		, m_shutdownRequested(false)
		, m_rootSheet(nullptr)
		, m_user(user)
		, m_renderWindow(nullptr)
		, m_inkWindow(nullptr)
		, m_inputWindow(nullptr)
	{}

	UiWindow::~UiWindow()
	{
		m_rootSheet->clear();
	}

	void UiWindow::setup(RenderWindow& renderWindow, InkWindow& inkWindow, InputWindow& inputWindow)
	{
		m_renderWindow = &renderWindow;
		m_inkWindow = &inkWindow;
		m_inputWindow = &inputWindow;

		m_width = float(renderWindow.width());
		m_height = float(renderWindow.height());

		m_styler->defaultLayout();
		m_styler->defaultSkins();

		this->init();
	}

	void UiWindow::init()
	{
		m_styler->prepare();

		m_rootSheet = make_unique<RootSheet>(*this);
		m_rootDevice = make_unique<RootDevice>(*this, *m_rootSheet);

		m_mouse = make_unique<Mouse>(*m_rootSheet);
		m_keyboard = make_unique<Keyboard>(*m_rootSheet);

		m_inputWindow->initInput(*m_mouse, *m_keyboard, m_renderWindow->handle());

		m_rootSheet->frame().setSize(m_width, m_height);

		this->resize(size_t(m_width), size_t(m_height));
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
