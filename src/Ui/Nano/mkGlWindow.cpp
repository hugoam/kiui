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

#include <GLFW/glfw3.h>

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkGlWindow.h>

#include <Ui/mkUiWindow.h>

#include <iostream>

#ifndef KIUI_EMSCRIPTEN
#define CAP_FRAMERATE
#endif

#ifdef CAP_FRAMERATE
#include <thread>
#endif

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

namespace mk
{
	MouseButton convertGlfwButton(int button)
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

	GlWindow::GlWindow(size_t width, size_t height, string title, string resourcePath)
		: RenderWindow(width, height, title, 0)
		, mResourcePath(resourcePath)
		, mUiWindow()
		, mGlWindow(nullptr)
	{}

	GlWindow::~GlWindow()
	{
		glfwTerminate();
	}

	void GlWindow::initContext()
	{
		if(!glfwInit()) {
			printf("Failed to init GLFW.");
			return;
		}

		glfwSetErrorCallback(errorcb);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		mGlWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);

		if(!mGlWindow) {
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(mGlWindow, this);
		glfwSetKeyCallback(mGlWindow, [](GLFWwindow* w, int key, int scancode, int action, int mods) { static_cast<GlWindow*>(glfwGetWindowUserPointer(w))->injectKey(key, scancode, action, mods); });
		glfwSetCharCallback(mGlWindow, [](GLFWwindow* w, unsigned int c) { static_cast<GlWindow*>(glfwGetWindowUserPointer(w))->injectChar(c); });
		glfwSetMouseButtonCallback(mGlWindow, [](GLFWwindow* w, int button, int action, int mods) { static_cast<GlWindow*>(glfwGetWindowUserPointer(w))->injectMouseButton(button, action, mods); });
		glfwSetCursorPosCallback(mGlWindow, [](GLFWwindow* w, double x, double y) { static_cast<GlWindow*>(glfwGetWindowUserPointer(w))->injectMouseMove(x, y); });
		glfwSetScrollCallback(mGlWindow, [](GLFWwindow* w, double x, double y) { static_cast<GlWindow*>(glfwGetWindowUserPointer(w))->injectWheel(x, y); });

		glfwMakeContextCurrent(mGlWindow);
		glfwSetInputMode(mGlWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#ifdef NANOVG_GLEW
		if(glewInit() != GLEW_OK) {
			printf("Could not init glew.\n");
			return;
		}
#endif

		int winWidth, winHeight;

		glfwGetWindowSize(mGlWindow, &winWidth, &winHeight);
		glfwGetFramebufferSize(mGlWindow, &mFbWidth, &mFbHeight);

		// Calculate pixel ration for hi-dpi devices.
		float pxRatio = (float)mFbWidth / (float)winWidth;

		mNanoWindow = make_unique<NanoWindow>(mWidth, mHeight, pxRatio, mResourcePath);
		mUiWindow = make_unique<UiWindow>(mResourcePath);
		mUiWindow->setup(*this, *mNanoWindow.get(), nullptr);
		this->initInput(*mUiWindow.get(), 0);

		glfwSwapInterval(0);
		glfwSetTime(0);
	}

	void GlWindow::initInput(InputDispatcher& input, size_t windowHnd)
	{
		UNUSED(windowHnd);
		mInput = &input;
	}

	bool GlWindow::renderFrame()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = glfwGetTime();
		double delta = time - prevtime;
		if(time - prevtime >= 4.f)
		{
			printf("fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		// Update and render
		glViewport(0, 0, mFbWidth, mFbHeight);

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		bool pursue = mUiWindow->nextFrame();
		mNanoWindow->nextFrame(time, delta);

#ifdef CAP_FRAMERATE
		double deltaf = 16.66666667 - ((glfwGetTime() - time) * 1000.f);

		if(deltaf > 0.f)
			std::this_thread::sleep_for(std::chrono::milliseconds(int(deltaf)));
#endif

		glfwSwapBuffers(mGlWindow);
		glfwPollEvents();

		++frames;

		return pursue;
	}

	void GlWindow::updateSize()
	{
		int width, height;
		glfwGetWindowSize(mGlWindow, &width, &height);
		mUiWindow->resize(mWidth, mHeight);
	}

	void GlWindow::resize(size_t width, size_t height)
	{
		UNUSED(width); UNUSED(height);
	}

	void GlWindow::injectMouseMove(double x, double y)
	{
		float xDif = float(x) - mMouseX;
		float yDif = float(y) - mMouseY;

		mMouseX = float(x);
		mMouseY = float(y);

		float clampedX = std::max(0.f, std::min(float(mWidth), mMouseX));
		float clampedY = std::max(0.f, std::min(float(mHeight), mMouseY));

		mUiWindow->dispatchMouseMoved(clampedX, clampedY, xDif, yDif);
	}

	void GlWindow::injectMouseButton(int button, int action, int mods)
	{
		float clampedX = std::max(0.f, std::min(float(mWidth), mMouseX));
		float clampedY = std::max(0.f, std::min(float(mHeight), mMouseY));

		UNUSED(mods);
		if(action == GLFW_PRESS)
			mInput->dispatchMousePressed(clampedX, clampedY, convertGlfwButton(button));
		else if(action == GLFW_RELEASE)
			mInput->dispatchMouseReleased(clampedX, clampedY, convertGlfwButton(button));
	}

	void GlWindow::injectKey(int key, int scancode, int action, int mods)
	{
		UNUSED(key); UNUSED(mods);
		if(action == GLFW_PRESS)
			mInput->dispatchKeyPressed(convertGlfwKey(key), (char) 0);
		else if(action == GLFW_RELEASE)
			mInput->dispatchKeyReleased(convertGlfwKey(key), (char) 0);
	}

	void GlWindow::injectChar(unsigned int codepoint, int mods)
	{
		UNUSED(codepoint); UNUSED(mods);
		mInput->dispatchKeyPressed((KeyCode) 0, (char) codepoint);
	}

	void GlWindow::injectWheel(double x, double y)
	{
		mInput->dispatchMouseWheeled(mMouseX, mMouseY, x + y);
	}
}
