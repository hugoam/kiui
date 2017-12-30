//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Input/InputDevice.h>

#include <toyui/Input/InputEvent.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Cursor.h>

namespace toy
{
	InputDevice::InputDevice(RootSheet& rootSheet)
		: m_rootSheet(rootSheet)
		, m_rootFrame(rootSheet.m_controller)
	{}

	Keyboard::Keyboard(RootSheet& rootSheet)
		: InputDevice(rootSheet)
		, m_shiftPressed(false)
		, m_ctrlPressed(false)
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
		, m_buttons{ { MouseButton{ *this, DEVICE_MOUSE_LEFT_BUTTON },
					   MouseButton{ *this, DEVICE_MOUSE_RIGHT_BUTTON },
					   MouseButton{ *this, DEVICE_MOUSE_MIDDLE_BUTTON } } }
		, m_lastPos(0.f, 0.f)
	{}

	void Mouse::mouseFocus(DimFloat pos, std::vector<Widget*>& focused)
	{
		if(focused.size() > 0)
			m_rootSheet.m_cursor.hover(*focused.front());
		else
			m_rootSheet.m_cursor.unhover();

		MouseEnterEvent mouseEnterEvent(*this, pos);
		MouseLeaveEvent mouseLeaveEvent(*this, pos);

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
		mouseEvent.m_delta = mouseEvent.m_pos - m_lastPos;
		if(m_rootSheet.m_keyboard.m_shiftPressed)
			mouseEvent.modifiers = static_cast<InputModifier>(mouseEvent.modifiers ^ INPUT_SHIFT);
		if(m_rootSheet.m_keyboard.m_ctrlPressed)
			mouseEvent.modifiers = static_cast<InputModifier>(mouseEvent.modifiers ^ INPUT_CTRL);
	}

	void Mouse::dispatchMouseMoved(DimFloat pos)
	{
		MouseMoveEvent mouseEvent(*this, pos);

		m_lastPos = mouseEvent.m_pos;
		m_rootSheet.m_cursor.setPosition(mouseEvent.m_pos);

		m_rootFrame.dispatchEvent(mouseEvent);

		this->mouseFocus(pos, mouseEvent.visited);

		for(MouseButton& button : m_buttons)
			button.mouseMoved(mouseEvent);
	}

	void Mouse::dispatchMousePressed(DimFloat pos, MouseButtonCode button)
	{
		m_buttons[button].mousePressed(pos);
	}

	void Mouse::dispatchMouseReleased(DimFloat pos, MouseButtonCode button)
	{
		m_buttons[button].mouseReleased(pos);
	}

	void Mouse::dispatchMouseWheeled(DimFloat pos, float amount)
	{
		MouseWheelEvent mouseEvent(*this, pos, amount);
		m_rootFrame.dispatchEvent(mouseEvent);
	}

	void Mouse::handleDestroyWidget(Widget& widget)
	{
		for(int i = m_focused.size() - 1; i >= 0; --i)
			if(m_focused.at(i) == &widget)
				m_focused.erase(m_focused.begin() + i);
	}

	MouseButton::MouseButton(Mouse& mouse, DeviceType deviceType)
		: InputDevice(mouse.m_rootSheet)
		, m_mouse(mouse)
		, m_deviceType(deviceType)
		, m_pressed(nullptr)
		, m_dragging(false)
		, m_pressedPos(0.f, 0.f)
	{}

	void MouseButton::mouseMoved(MouseEvent& mouseEvent)
	{
		const float threshold = 3.f;
		DimFloat delta = mouseEvent.m_pos - m_pressedPos;

		if(m_dragging)
			this->dragMove(mouseEvent);
		else if(m_pressed && (std::abs(delta.x) > threshold || std::abs(delta.y) > threshold))
			this->dragStart(mouseEvent);
	}

	void MouseButton::mousePressed(DimFloat pos)
	{
		MousePressEvent mouseEvent(m_mouse, m_deviceType, pos);

		m_pressed = m_rootFrame.dispatchEvent(mouseEvent);
		m_pressedPos = mouseEvent.m_pos;
	}

	void MouseButton::mouseReleased(DimFloat pos)
	{
		MouseReleaseEvent mouseEvent(m_mouse, m_deviceType, pos);

		m_rootFrame.dispatchEvent(mouseEvent, m_pressed);

		if(m_dragging)
			this->dragEnd(mouseEvent);
		else
			this->click(mouseEvent);

		m_pressed = nullptr;
	}

	void MouseButton::dragStart(MouseEvent& mouseEvent)
	{
		MouseDragStartEvent dragEvent(m_mouse, m_deviceType, mouseEvent);
		dragEvent.m_pressed = m_pressedPos;
		m_rootFrame.dispatchEvent(dragEvent, m_pressed);

		this->dragMove(mouseEvent);
		m_rootSheet.m_cursor.lock();
		m_dragging = true;
	}

	void MouseButton::dragEnd(MouseEvent& mouseEvent)
	{
		m_dragging = false;
		m_rootSheet.m_cursor.unlock();

		MouseDragEndEvent dragEvent(m_mouse, m_deviceType, mouseEvent);
		m_rootFrame.dispatchEvent(dragEvent, m_pressed);
	}

	void MouseButton::dragMove(MouseEvent& mouseEvent)
	{
		MouseDragEvent dragEvent(m_mouse, m_deviceType, mouseEvent);
		dragEvent.m_pressed = m_pressedPos;
		m_rootFrame.dispatchEvent(dragEvent, m_pressed);
	}

	void MouseButton::click(MouseEvent& mouseEvent)
	{
		MouseClickEvent clickEvent(m_mouse, m_deviceType, mouseEvent);
		m_rootFrame.dispatchEvent(clickEvent, m_pressed);
	}
}
