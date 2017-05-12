//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Input/InputDevice.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>

#include <cassert>

namespace toy
{
	InputDevice::InputDevice(RootSheet& rootSheet)
		: m_rootSheet(rootSheet)
		, m_rootFrame(rootSheet.controller())
	{}

	Keyboard::Keyboard(RootSheet& rootSheet)
		: InputDevice(rootSheet)
		, m_shiftPressed(false)
		, m_ctrlPressed(false)
	{}

	void Keyboard::nextFrame()
	{}

	void Keyboard::dispatchKeyPressed(KeyCode key, char c)
	{
		/*if(key == KC_ESCAPE)
			m_shutdownRequested = true;
		else */if(key == KC_LSHIFT || key == KC_RSHIFT)
			m_shiftPressed = true;
		else if(key == KC_LCONTROL || key == KC_RCONTROL)
			m_ctrlPressed = true;

		KeyDownEvent keyEvent(key, c);
		m_rootFrame.dispatchEvent(keyEvent);
	}

	void Keyboard::dispatchKeyReleased(KeyCode key, char c)
	{
		if(key == KC_LSHIFT || key == KC_RSHIFT)
			m_shiftPressed = false;
		else if(key == KC_LCONTROL || key == KC_RCONTROL)
			m_ctrlPressed = false;

		KeyUpEvent keyEvent(key, c);
		m_rootFrame.dispatchEvent(keyEvent);
	}

	Mouse::Mouse(RootSheet& rootSheet)
		: InputDevice(rootSheet)
		, m_leftButton(*this, DEVICE_MOUSE_LEFT_BUTTON)
		, m_rightButton(*this, DEVICE_MOUSE_RIGHT_BUTTON)
		, m_middleButton(*this, DEVICE_MOUSE_MIDDLE_BUTTON)
		, m_lastX(0.f)
		, m_lastY(0.f)
	{}

	void Mouse::nextFrame()
	{
	}

	void Mouse::mouseFocus(float x, float y, std::vector<Widget*>& focused)
	{
		if(focused.size() > 0)
			m_rootSheet.cursor().hover(*focused.front());
		else
			m_rootSheet.cursor().unhover();

		std::sort(m_focused.begin(), m_focused.end());
		std::sort(focused.begin(), focused.end());

		MouseEnterEvent mouseEnterEvent(x, y);
		this->transformMouseEvent(mouseEnterEvent);

		MouseLeaveEvent mouseLeaveEvent(x, y);
		this->transformMouseEvent(mouseLeaveEvent);

		for(Widget* newFocus : focused)
			if(std::find(m_focused.begin(), m_focused.end(), newFocus) == m_focused.end())
				newFocus->receiveEvent(mouseEnterEvent);

		for(Widget* oldFocus : m_focused)
			if(std::find(focused.begin(), focused.end(), oldFocus) == focused.end())
				oldFocus->receiveEvent(mouseLeaveEvent);

		m_focused = focused;
	}

	void Mouse::transformMouseEvent(MouseEvent& mouseEvent)
	{
		m_rootSheet.transformCoordinates(mouseEvent);

		mouseEvent.deltaX = mouseEvent.posX - m_lastX;
		mouseEvent.deltaY = mouseEvent.posY - m_lastY;
	}

	void Mouse::dispatchMouseMoved(float x, float y)
	{
		MouseMoveEvent mouseEvent(x, y);
		this->transformMouseEvent(mouseEvent);

		m_lastX = mouseEvent.posX;
		m_lastY = mouseEvent.posY;

		m_rootSheet.cursor().setPosition(mouseEvent.posX, mouseEvent.posY);

		m_rootFrame.dispatchEvent(mouseEvent);

		this->mouseFocus(x, y, mouseEvent.visited);

		m_leftButton.mouseMoved(mouseEvent);
		m_rightButton.mouseMoved(mouseEvent);
		m_middleButton.mouseMoved(mouseEvent);
	}

	void Mouse::dispatchMousePressed(float x, float y, MouseButtonCode button)
	{
		if(button == LEFT_BUTTON)
			m_leftButton.mousePressed(x, y);
		else if(button == RIGHT_BUTTON)
			m_rightButton.mousePressed(x, y);
		else if(button == MIDDLE_BUTTON)
			m_middleButton.mousePressed(x, y);
	}

	void Mouse::dispatchMouseReleased(float x, float y, MouseButtonCode button)
	{
		if(button == LEFT_BUTTON)
			m_leftButton.mouseReleased(x, y);
		else if(button == RIGHT_BUTTON)
			m_rightButton.mouseReleased(x, y);
		else if(button == MIDDLE_BUTTON)
			m_middleButton.mouseReleased(x, y);
	}

	void Mouse::dispatchMouseWheeled(float x, float y, float amount)
	{
		MouseWheelEvent mouseEvent(x, y, amount);
		this->transformMouseEvent(mouseEvent);

		m_rootFrame.dispatchEvent(mouseEvent);
	}

	void Mouse::handleBindWidget(Widget& widget)
	{
		m_leftButton.handleBindWidget(widget);
		m_rightButton.handleBindWidget(widget);
		m_middleButton.handleBindWidget(widget);
	}

	void Mouse::handleUnbindWidget(Widget& widget)
	{
		m_leftButton.handleUnbindWidget(widget);
		m_rightButton.handleUnbindWidget(widget);
		m_middleButton.handleUnbindWidget(widget);

		for(int i = m_focused.size() - 1; i >= 0; --i)
			if(m_focused.at(i) == &widget)
			{
				m_rootSheet.cursor().unhover();
				m_focused.erase(m_focused.begin() + i);
			}
	}

	MouseButton::MouseButton(Mouse& mouse, DeviceType deviceType)
		: InputDevice(mouse.rootSheet())
		, m_mouse(mouse)
		, m_deviceType(deviceType)
		, m_pressed(nullptr)
		, m_dragging(false)
		, m_pressedX(0.f)
		, m_pressedY(0.f)
	{}

	void MouseButton::mouseMoved(MouseEvent& mouseEvent)
	{
		const float threshold = 3.f;

		if(m_dragging)
			this->dragMove(mouseEvent);
		else if(m_pressed && (std::abs(mouseEvent.posX - m_pressedX) > threshold
						   || std::abs(mouseEvent.posY - m_pressedY) > threshold))
		{
			m_dragging = true;
			this->dragStart(mouseEvent);
		}
	}

	void MouseButton::mousePressed(float x, float y)
	{
		MousePressEvent mouseEvent(m_deviceType, x, y);
		m_mouse.transformMouseEvent(mouseEvent);

		m_pressed = m_rootFrame.dispatchEvent(mouseEvent);
		m_pressedX = mouseEvent.posX;
		m_pressedY = mouseEvent.posY;
	}

	void MouseButton::mouseReleased(float x, float y)
	{
		MouseReleaseEvent mouseEvent(m_deviceType, x, y);
		m_mouse.transformMouseEvent(mouseEvent);

		m_pressed->receiveEvent(mouseEvent);

		if(m_dragging)
			this->dragEnd(mouseEvent);
		else
			this->click(mouseEvent);

		m_pressed = nullptr;
		m_dragging = false;
	}

	void MouseButton::dragStart(MouseEvent& mouseEvent)
	{
		MouseDragStartEvent dragEvent(m_deviceType, mouseEvent.posX, mouseEvent.posY, m_pressedX, m_pressedY);
		m_pressed->receiveEvent(dragEvent);
	}

	void MouseButton::dragEnd(MouseEvent& mouseEvent)
	{
		MouseDragEndEvent dragEvent(m_deviceType, mouseEvent.posX, mouseEvent.posY);
		m_pressed->receiveEvent(dragEvent);
	}

	void MouseButton::dragMove(MouseEvent& mouseEvent)
	{
		MouseDragEvent dragEvent(m_deviceType, mouseEvent.posX, mouseEvent.posY, mouseEvent.deltaX, mouseEvent.deltaY);
		m_pressed->receiveEvent(dragEvent);
	}

	void MouseButton::click(MouseEvent& mouseEvent)
	{
		MouseClickEvent clickEvent(m_deviceType, mouseEvent.posX, mouseEvent.posY);
		m_pressed->receiveEvent(clickEvent);
	}

	void MouseButton::handleUnbindWidget(Widget& widget)
	{
		if(m_pressed == &widget)
		{
			m_prevPressed = m_pressed;
			m_pressed = nullptr;
			m_dragging = false;
		}
	}
	
	void MouseButton::handleBindWidget(Widget& widget)
	{
		if(m_prevPressed == &widget)
		{
			m_prevPressed = nullptr;
			m_pressed = &widget;
			m_dragging = false;
		}
	}
}
