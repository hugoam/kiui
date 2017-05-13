//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Context/Emscripten/EmscriptenContext.h>

#include <toyui/UiWindow.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <cassert>

namespace toy
{
	MouseButtonCode convertHtml5MouseButton(unsigned short button)
	{
		if(button == 0) return LEFT_BUTTON;
		if(button == 1) return MIDDLE_BUTTON;
		if(button == 2) return RIGHT_BUTTON;
	}

	KeyCode convertHtml5Key(const string& string)
	{
		/*else if(string == GLFW_KEY_UNKNOWN) return KC_UNASSIGNED;
		else if(string == GLFW_KEY_APOSTROPHE) return KC_APOSTROPHE;
		else if(string == GLFW_KEY_COMMA) return KC_COMMA;
		else if(string == GLFW_KEY_MINUS) return KC_MINUS;
		else if(string == GLFW_KEY_PERIOD) return KC_PERIOD;
		else if(string == GLFW_KEY_SLASH) return KC_SLASH;*/
		if(string == "Space") return KC_SPACE;
		else if(string == "Enter") return KC_RETURN;
		else if(string == "Escape") return KC_ESCAPE;
		else if(string == "ShiftLeft") return KC_LSHIFT;
		else if(string == "ShiftRight") return KC_RSHIFT;
		else if(string == "ControlLeft") return KC_LCONTROL;
		else if(string == "ControlRight") return KC_RCONTROL;
		else if(string == "AltLeft") return KC_LMENU;
		else if(string == "AltRight") return KC_RMENU;
		else if(string == "MetaLeft") return KC_LWIN;
		else if(string == "MetaRight") return KC_RWIN;
		else if(string == "CapsLock") return KC_CAPITAL;
		else if(string == "Tab") return KC_TAB;
		else if(string == "Digit0") return KC_0;
		else if(string == "Digit1") return KC_1;
		else if(string == "Digit2") return KC_2;
		else if(string == "Digit3") return KC_3;
		else if(string == "Digit4") return KC_4;
		else if(string == "Digit5") return KC_5;
		else if(string == "Digit6") return KC_6;
		else if(string == "Digit7") return KC_7;
		else if(string == "Digit8") return KC_8;
		else if(string == "Digit9") return KC_9;
		/*
		else if(string == GLFW_KEY_SEMICOLON) return KC_SEMICOLON;
		else if(string == GLFW_KEY_EQUAL) return KC_EQUALS;
		*/
		else if(string == "KeyA") return KC_A;
		else if(string == "KeyB") return KC_B;
		else if(string == "KeyC") return KC_C;
		else if(string == "KeyD") return KC_D;
		else if(string == "KeyE") return KC_E;
		else if(string == "KeyF") return KC_F;
		else if(string == "KeyG") return KC_G;
		else if(string == "KeyH") return KC_H;
		else if(string == "KeyI") return KC_I;
		else if(string == "KeyJ") return KC_J;
		else if(string == "KeyK") return KC_K;
		else if(string == "KeyL") return KC_L;
		else if(string == "KeyM") return KC_M;
		else if(string == "KeyN") return KC_N;
		else if(string == "KeyO") return KC_O;
		else if(string == "KeyP") return KC_P;
		else if(string == "KeyQ") return KC_Q;
		else if(string == "KeyR") return KC_R;
		else if(string == "KeyS") return KC_S;
		else if(string == "KeyT") return KC_T;
		else if(string == "KeyU") return KC_U;
		else if(string == "KeyV") return KC_V;
		else if(string == "KeyW") return KC_W;
		else if(string == "KeyX") return KC_X;
		else if(string == "KeyY") return KC_Y;
		else if(string == "KeyZ") return KC_Z;
		else if(string == "BracketLeft") return KC_LBRACKET;
		else if(string == "BracketRight") return KC_RBRACKET;
		else if(string == "Backslash") return KC_BACKSLASH;
		else if(string == "Backspace") return KC_BACK;
		else if(string == "Insert") return KC_INSERT;
		else if(string == "Delete") return KC_DELETE;
		else if(string == "ArrowDown") return KC_DOWN;
		else if(string == "ArrowLeft") return KC_LEFT;
		else if(string == "ArrowRight") return KC_RIGHT;
		else if(string == "ArrowUp") return KC_UP;
		else if(string == "End") return KC_END;
		else if(string == "Home") return KC_HOME;
		else if(string == "PageUp") return KC_PGUP;
		else if(string == "PageDown") return KC_PGDOWN;
		/*
		else if(string == GLFW_KEY_SCROLL_LOCK:
		else if(string == GLFW_KEY_NUM_LOCK) return KC_NUMLOCK;
		else if(string == GLFW_KEY_PRINT_SCREEN:
		else if(string == GLFW_KEY_PAUSE) return KC_PAUSE;
		*/
		else if(string == "F1") return KC_F1;
		else if(string == "F2") return KC_F2;
		else if(string == "F3") return KC_F3;
		else if(string == "F4") return KC_F4;
		else if(string == "F5") return KC_F5;
		else if(string == "F6") return KC_F6;
		else if(string == "F7") return KC_F7;
		else if(string == "F8") return KC_F8;
		else if(string == "F9") return KC_F9;
		else if(string == "F10") return KC_F10;
		else if(string == "F11") return KC_F11;
		else if(string == "F12") return KC_F12;
		else if(string == "Numpad0") return KC_NUMPAD0;
		else if(string == "Numpad1") return KC_NUMPAD1;
		else if(string == "Numpad2") return KC_NUMPAD2;
		else if(string == "Numpad3") return KC_NUMPAD3;
		else if(string == "Numpad4") return KC_NUMPAD4;
		else if(string == "Numpad5") return KC_NUMPAD5;
		else if(string == "Numpad6") return KC_NUMPAD6;
		else if(string == "Numpad7") return KC_NUMPAD7;
		else if(string == "Numpad8") return KC_NUMPAD8;
		else if(string == "Numpad9") return KC_NUMPAD9;
		else if(string == "NumpadComma") return KC_NUMPADCOMMA;
		else if(string == "NumpadDivide") return KC_DIVIDE;
		else if(string == "NumpadMultiply") return KC_MULTIPLY;
		else if(string == "NumpadSubtract") return KC_SUBTRACT;
		else if(string == "NumpadAdd") return KC_ADD;
		else if(string == "NumpadEqual") return KC_NUMPADENTER;
		else return KC_UNASSIGNED;
	}

	EmRenderWindow::EmRenderWindow(const string& name, int width, int height, bool autoSwap)
		: RenderWindow(name, width, height, 0)
	{
		this->initContext();
	}

	EmRenderWindow::~EmRenderWindow()
	{
	}

	void EmRenderWindow::initContext()
	{
		emscripten_set_canvas_size(m_width, m_height);

		EmscriptenWebGLContextAttributes attrs;
		emscripten_webgl_init_context_attributes(&attrs);
		attrs.depth = 1;
		attrs.stencil = 1;
		attrs.antialias = 1;
		attrs.majorVersion = 2;
		attrs.minorVersion = 0;

		assert(emscripten_webgl_get_current_context() == 0);

		m_window = emscripten_webgl_create_context("canvas", &attrs);

		emscripten_webgl_make_context_current(m_window);

#if defined TOY_PLATFORM_LINUX || defined TOY_PLATFORM_BSD
		m_nativeHandle = (void*)(uintptr_t)glfwGetX11Window(_window);
#elif defined TOY_PLATFORM_OSX
		m_nativeHandle = glfwGetCocoaWindow(_window);
#elif defined TOY_PLATFORM_WINDOWS
		m_nativeHandle = glfwGetWin32Window(m_glWindow);
#endif
	}

	bool EmRenderWindow::nextFrame()
	{
		this->resize();

		return true;
	}

	void EmRenderWindow::resize()
	{
		int width, height, fullscreen;

		emscripten_get_canvas_size(&width, &height, &fullscreen);

		m_width = width;
		m_height = height;
	}

	EmInputWindow::EmInputWindow(EmRenderWindow& renderWindow)
		: InputWindow()
		, m_renderWindow(renderWindow)
	{
		emscripten_set_mousemove_callback(0, this, true, [](int eventType, const EmscriptenMouseEvent* mouseEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectMouseMove(*mouseEvent)); });

		emscripten_set_mousedown_callback(0, this, true, [](int eventType, const EmscriptenMouseEvent* mouseEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectMouseDown(*mouseEvent)); });
		emscripten_set_mouseup_callback(0, this, true, [](int eventType, const EmscriptenMouseEvent* mouseEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectMouseUp(*mouseEvent)); });

		emscripten_set_wheel_callback(0, this, true, [](int eventType, const EmscriptenWheelEvent* wheelEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectWheel(*wheelEvent)); });

		emscripten_set_keydown_callback(0, this, true, [](int eventType, const EmscriptenKeyboardEvent* keyEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectKeyDown(*keyEvent)); });
		emscripten_set_keyup_callback(0, this, true, [](int eventType, const EmscriptenKeyboardEvent* keyEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectKeyUp(*keyEvent)); });
		emscripten_set_keypress_callback(0, this, true, [](int eventType, const EmscriptenKeyboardEvent* keyEvent, void* window) { return EM_BOOL(static_cast<EmInputWindow*>(window)->injectKeyPress(*keyEvent)); });

		//glfwSetScrollCallback(m_glWindow, [](GLFWwindow* w, double x, double y) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectWheel(x, y); });

		//glfwMakeContextCurrent(m_glWindow);
		//glfwSetInputMode(m_glWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	EmInputWindow::~EmInputWindow()
	{}

	bool EmInputWindow::nextFrame()
	{
		//glfwPollEvents();
		return true;
	}

	void EmInputWindow::initInput(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	void EmInputWindow::resize(size_t width, size_t height)
	{
		UNUSED(width); UNUSED(height);
	}

	bool EmInputWindow::injectMouseMove(const EmscriptenMouseEvent& mouseEvent)
	{
		m_mouseX = float(mouseEvent.canvasX);
		m_mouseY = float(mouseEvent.canvasY);

		float clampedX = std::max(0.f, std::min(float(m_renderWindow.width()), m_mouseX));
		float clampedY = std::max(0.f, std::min(float(m_renderWindow.height()), m_mouseY));

		m_mouse->dispatchMouseMoved(clampedX, clampedY, mouseEvent.movementX, mouseEvent.movementY);
	}

	bool EmInputWindow::injectMouseDown(const EmscriptenMouseEvent& mouseEvent)
	{
		m_mouse->dispatchMousePressed(mouseEvent.canvasX, mouseEvent.canvasY, convertHtml5MouseButton(mouseEvent.button));
		return true;
	}

	bool EmInputWindow::injectMouseUp(const EmscriptenMouseEvent& mouseEvent)
	{
		m_mouse->dispatchMouseReleased(mouseEvent.canvasX, mouseEvent.canvasY, convertHtml5MouseButton(mouseEvent.button));
		return true;
	}

	bool EmInputWindow::injectKeyDown(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->dispatchKeyPressed(convertHtml5Key(keyEvent.key), keyEvent.code[0]);
		return true;
	}

	bool EmInputWindow::injectKeyUp(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->dispatchKeyReleased(convertHtml5Key(keyEvent.key), keyEvent.code[0]);
		return true;
	}

	bool EmInputWindow::injectKeyPress(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->dispatchKeyReleased(convertHtml5Key(keyEvent.key), keyEvent.code[0]);
		return true;
	}

	bool EmInputWindow::injectWheel(const EmscriptenWheelEvent& wheelEvent)
	{
		m_mouse->dispatchMouseWheeled(m_mouseX, m_mouseY, wheelEvent.deltaY);
	}

	EmContext::EmContext(RenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
		: Context(renderSystem)
	{
		unique_ptr<EmRenderWindow> renderWindow = make_unique<EmRenderWindow>(name, width, height);
		unique_ptr<EmInputWindow> inputWindow = make_unique<EmInputWindow>(*renderWindow);

		this->init(std::move(renderWindow), std::move(inputWindow));
	}
}
