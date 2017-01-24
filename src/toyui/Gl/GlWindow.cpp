//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Gl/GlWindow.h>

#include <toyui/Gl/GlRenderer.h>

#include <toyui/UiWindow.h>

#ifdef NANOVG_GLEW
#include <GL/glew.h>
#elif defined(KIUI_EMSCRIPTEN)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <GLFW/glfw3.h>

#include <iostream>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#undef max
#undef min

#define TOY_PLATFORM_WINDOWS

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

namespace toy
{
	MouseButtonCode convertGlfwButton(int button)
	{
		switch(button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			return LEFT_BUTTON;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return RIGHT_BUTTON;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			return MIDDLE_BUTTON;
		default:
			return LEFT_BUTTON;
		}
	}

	KeyCode convertGlfwKey(int key)
	{
		switch(key)
		{
		case GLFW_KEY_UNKNOWN: return KC_UNASSIGNED;
		case GLFW_KEY_SPACE: return KC_SPACE;
		case GLFW_KEY_APOSTROPHE: return KC_APOSTROPHE;
		case GLFW_KEY_COMMA: return KC_COMMA;
		case GLFW_KEY_MINUS: return KC_MINUS;
		case GLFW_KEY_PERIOD: return KC_PERIOD;
		case GLFW_KEY_SLASH: return KC_SLASH;
		case GLFW_KEY_0: return KC_0;
		case GLFW_KEY_1: return KC_1;
		case GLFW_KEY_2: return KC_2;
		case GLFW_KEY_3: return KC_3;
		case GLFW_KEY_4: return KC_4;
		case GLFW_KEY_5: return KC_5;
		case GLFW_KEY_6: return KC_6;
		case GLFW_KEY_7: return KC_7;
		case GLFW_KEY_8: return KC_8;
		case GLFW_KEY_9: return KC_9;
		case GLFW_KEY_SEMICOLON: return KC_SEMICOLON;
		case GLFW_KEY_EQUAL: return KC_EQUALS;
		case GLFW_KEY_A: return KC_A;
		case GLFW_KEY_B: return KC_B;
		case GLFW_KEY_C: return KC_C;
		case GLFW_KEY_D: return KC_D;
		case GLFW_KEY_E: return KC_E;
		case GLFW_KEY_F: return KC_F;
		case GLFW_KEY_G: return KC_G;
		case GLFW_KEY_H: return KC_H;
		case GLFW_KEY_I: return KC_I;
		case GLFW_KEY_J: return KC_J;
		case GLFW_KEY_K: return KC_K;
		case GLFW_KEY_L: return KC_L;
		case GLFW_KEY_M: return KC_M;
		case GLFW_KEY_N: return KC_N;
		case GLFW_KEY_O: return KC_O;
		case GLFW_KEY_P: return KC_P;
		case GLFW_KEY_Q: return KC_Q;
		case GLFW_KEY_R: return KC_R;
		case GLFW_KEY_S: return KC_S;
		case GLFW_KEY_T: return KC_T;
		case GLFW_KEY_U: return KC_U;
		case GLFW_KEY_V: return KC_V;
		case GLFW_KEY_W: return KC_W;
		case GLFW_KEY_X: return KC_X;
		case GLFW_KEY_Y: return KC_Y;
		case GLFW_KEY_Z: return KC_Z;
		case GLFW_KEY_LEFT_BRACKET: return KC_LBRACKET;
		case GLFW_KEY_BACKSLASH: return KC_BACKSLASH;
		case GLFW_KEY_RIGHT_BRACKET: return KC_RBRACKET;
		//case GLFW_KEY_GRAVE_ACCENT: 
		//case GLFW_KEY_WORLD_1: 
		//case GLFW_KEY_WORLD_2: 

		case GLFW_KEY_ESCAPE: return KC_ESCAPE;
		case GLFW_KEY_ENTER: return KC_RETURN;
		case GLFW_KEY_TAB: return KC_TAB;
		case GLFW_KEY_BACKSPACE: return KC_BACK;
		case GLFW_KEY_INSERT: return KC_INSERT;
		case GLFW_KEY_DELETE: return KC_DELETE;
		case GLFW_KEY_RIGHT: return KC_RIGHT;
		case GLFW_KEY_LEFT: return KC_LEFT;
		case GLFW_KEY_DOWN: return KC_DOWN;
		case GLFW_KEY_UP: return KC_UP;
		case GLFW_KEY_PAGE_UP: return KC_PGUP;
		case GLFW_KEY_PAGE_DOWN: return KC_PGDOWN;
		case GLFW_KEY_HOME: return KC_HOME;
		case GLFW_KEY_END: return KC_END;
		case GLFW_KEY_CAPS_LOCK: return KC_CAPITAL;
		//case GLFW_KEY_SCROLL_LOCK:
		case GLFW_KEY_NUM_LOCK: return KC_NUMLOCK;
		//case GLFW_KEY_PRINT_SCREEN:
		case GLFW_KEY_PAUSE: return KC_PAUSE;
		case GLFW_KEY_F1: return KC_F1;
		case GLFW_KEY_F2: return KC_F2;
		case GLFW_KEY_F3: return KC_F3;
		case GLFW_KEY_F4: return KC_F4;
		case GLFW_KEY_F5: return KC_F5;
		case GLFW_KEY_F6: return KC_F6;
		case GLFW_KEY_F7: return KC_F7;
		case GLFW_KEY_F8: return KC_F8;
		case GLFW_KEY_F9: return KC_F9;
		case GLFW_KEY_F10: return KC_F10;
		case GLFW_KEY_F11: return KC_F11;
		case GLFW_KEY_F12: return KC_F12;
		case GLFW_KEY_F13: return KC_F13;
		case GLFW_KEY_F14: return KC_F14;
		case GLFW_KEY_F15: return KC_F15;
		case GLFW_KEY_KP_0: return KC_NUMPAD0;
		case GLFW_KEY_KP_1: return KC_NUMPAD1;
		case GLFW_KEY_KP_2: return KC_NUMPAD2;
		case GLFW_KEY_KP_3: return KC_NUMPAD3;
		case GLFW_KEY_KP_4: return KC_NUMPAD4;
		case GLFW_KEY_KP_5: return KC_NUMPAD5;
		case GLFW_KEY_KP_6: return KC_NUMPAD6;
		case GLFW_KEY_KP_7: return KC_NUMPAD7;
		case GLFW_KEY_KP_8: return KC_NUMPAD8;
		case GLFW_KEY_KP_9: return KC_NUMPAD9;
		case GLFW_KEY_KP_DECIMAL: return KC_NUMPADCOMMA;
		case GLFW_KEY_KP_DIVIDE: return KC_DIVIDE;
		case GLFW_KEY_KP_MULTIPLY: return KC_MULTIPLY;
		case GLFW_KEY_KP_SUBTRACT: return KC_SUBTRACT;
		case GLFW_KEY_KP_ADD: return KC_ADD;
		case GLFW_KEY_KP_ENTER: return KC_NUMPADENTER;
		case GLFW_KEY_KP_EQUAL: return KC_NUMPADENTER;
		case GLFW_KEY_LEFT_SHIFT: return KC_LSHIFT;
		case GLFW_KEY_LEFT_CONTROL: return KC_LCONTROL;
		case GLFW_KEY_LEFT_ALT: return KC_LMENU;
		case GLFW_KEY_LEFT_SUPER: return KC_LWIN;
		case GLFW_KEY_RIGHT_SHIFT: return KC_RSHIFT;
		case GLFW_KEY_RIGHT_CONTROL: return KC_RCONTROL;
		case GLFW_KEY_RIGHT_ALT: return KC_RMENU;
		case GLFW_KEY_RIGHT_SUPER: return KC_RWIN;
		//case GLFW_KEY_MENU:
		default: return KC_UNASSIGNED;
		}
	}

	GlRenderWindow::GlRenderWindow(const string& name, int width, int height, bool autoSwap)
		: RenderWindow(name, width, height, 0)
		, m_glWindow(nullptr)
		, m_autoSwap(autoSwap)
	{
		this->initContext();
	}

	GlRenderWindow::~GlRenderWindow()
	{
		glfwTerminate();
	}

	void GlRenderWindow::initContext()
	{
		if(!glfwInit()) {
			printf("Failed to init GLFW.");
			return;
		}

		glfwSetErrorCallback(errorcb);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		m_glWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

		if(!m_glWindow) {
			glfwTerminate();
			return;
		}

		glfwSwapInterval(0);
		glfwSetTime(0);

#if defined TOY_PLATFORM_LINUX || defined TOY_PLATFORM_BSD
		m_nativeHandle = (void*)(uintptr_t)glfwGetX11Window(_window);
#elif defined TOY_PLATFORM_OSX
		m_nativeHandle = glfwGetCocoaWindow(_window);
#elif defined TOY_PLATFORM_WINDOWS
		m_nativeHandle = glfwGetWin32Window(m_glWindow);
#endif
	}

	bool GlRenderWindow::nextFrame()
	{
		this->resize();

		if(m_autoSwap)
			glfwSwapBuffers(m_glWindow);

		return true;
	}

	void GlRenderWindow::resize()
	{
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		glfwGetWindowSize(m_glWindow, &winWidth, &winHeight);
		glfwGetFramebufferSize(m_glWindow, &fbWidth, &fbHeight);

		// Calculate pixel ration for hi-dpi devices.
		float pxRatio = (float)fbWidth / (float)winWidth;

		m_width = winWidth;
		m_height = winHeight;
	}

	GlInputWindow::GlInputWindow(GlRenderWindow& renderWindow)
		: InputWindow()
		, m_renderWindow(renderWindow)
		, m_glWindow(renderWindow.glWindow())
	{
		glfwSetWindowUserPointer(m_glWindow, this);
		glfwSetKeyCallback(m_glWindow, [](GLFWwindow* w, int key, int scancode, int action, int mods) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectKey(key, scancode, action, mods); });
		glfwSetCharCallback(m_glWindow, [](GLFWwindow* w, unsigned int c) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectChar(c); });
		glfwSetMouseButtonCallback(m_glWindow, [](GLFWwindow* w, int button, int action, int mods) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectMouseButton(button, action, mods); });
		glfwSetCursorPosCallback(m_glWindow, [](GLFWwindow* w, double x, double y) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectMouseMove(x, y); });
		glfwSetScrollCallback(m_glWindow, [](GLFWwindow* w, double x, double y) { static_cast<GlInputWindow*>(glfwGetWindowUserPointer(w))->injectWheel(x, y); });

		glfwMakeContextCurrent(m_glWindow);
		glfwSetInputMode(m_glWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	GlInputWindow::~GlInputWindow()
	{}

	bool GlInputWindow::nextFrame()
	{
		glfwPollEvents();
		return true;
	}

	void GlInputWindow::initInput(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	void GlInputWindow::resize(size_t width, size_t height)
	{
		UNUSED(width); UNUSED(height);
	}

	void GlInputWindow::injectMouseMove(double x, double y)
	{
		float xDif = float(x) - m_mouseX;
		float yDif = float(y) - m_mouseY;

		m_mouseX = float(x);
		m_mouseY = float(y);

		float clampedX = std::max(0.f, std::min(float(m_renderWindow.width()), m_mouseX));
		float clampedY = std::max(0.f, std::min(float(m_renderWindow.height()), m_mouseY));

		m_mouse->dispatchMouseMoved(clampedX, clampedY, xDif, yDif);
	}

	void GlInputWindow::injectMouseButton(int button, int action, int mods)
	{
		float clampedX = std::max(0.f, std::min(float(m_renderWindow.width()), m_mouseX));
		float clampedY = std::max(0.f, std::min(float(m_renderWindow.height()), m_mouseY));

		UNUSED(mods);
		if(action == GLFW_PRESS)
			m_mouse->dispatchMousePressed(clampedX, clampedY, convertGlfwButton(button));
		else if(action == GLFW_RELEASE)
			m_mouse->dispatchMouseReleased(clampedX, clampedY, convertGlfwButton(button));
	}

	void GlInputWindow::injectKey(int key, int scancode, int action, int mods)
	{
		UNUSED(scancode); UNUSED(mods);
		if(action == GLFW_PRESS)
			m_keyboard->dispatchKeyPressed(convertGlfwKey(key), (char) 0);
		else if(action == GLFW_RELEASE)
			m_keyboard->dispatchKeyReleased(convertGlfwKey(key), (char) 0);
	}

	void GlInputWindow::injectChar(unsigned int codepoint, int mods)
	{
		UNUSED(codepoint); UNUSED(mods);
		m_keyboard->dispatchKeyPressed((KeyCode) 0, (char) codepoint);
	}

	void GlInputWindow::injectWheel(double x, double y)
	{
		m_mouse->dispatchMouseWheeled(m_mouseX, m_mouseY, x + y);
	}

#ifdef TOY_GL
	GlContext::GlContext(const string& resourcePath)
		: UiContext(resourcePath)
	{}

	unique_ptr<RenderWindow> GlContext::createRenderWindow(const string& name, int width, int height, bool fullScreen)
	{
		return make_unique<GlRenderWindow>(name, width, height);
	}

	unique_ptr<InputWindow> GlContext::createInputWindow(RenderWindow& renderWindow)
	{
		return make_unique<GlInputWindow>(static_cast<GlRenderWindow&>(renderWindow));
	}

	unique_ptr<Renderer> GlContext::createRenderer(const string& resourcePath)
	{
		return make_unique<GlRenderer>(resourcePath);
	}

#endif

}
