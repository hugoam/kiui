//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOGL2_H
#define MK_NANOGL2_H

/* mk Og */
#include <Ui/mkUiForward.h>
#include <Ui/Nano/mkNanoWindow.h>
#include <Ui/mkRenderWindow.h>
#include <Ui/Input/mkInputDispatcher.h>

namespace mk
{
	class MK_UI_EXPORT GlWindow : public RenderWindow, public InputWindow
	{
	public:
		GlWindow(size_t width, size_t height, string title, string ressourcePath);
		~GlWindow();

		UiWindow* uiWindow() { return mUiWindow.get(); }

		void initContext();
		void initInput(InputDispatcher* dispatcher, size_t windowHnd);

		bool renderFrame();

		void injectMouseMove(double x, double y);
		void injectMouseButton(int button, int action, int mods);
		void injectKey(int key, int scancode, int action, int mods);
		void injectChar(int codepoint, int mods);

		void updateSize();

		void resize(size_t width, size_t height);

	protected:
		string mRessourcePath;
		unique_ptr<NanoWindow> mNanoWindow;
		unique_ptr<UiWindow> mUiWindow;

		GLFWwindow* mGlWindow;
		int mFbWidth;
		int mFbHeight;

		float mMouseX;
		float mMouseY;

		InputDispatcher* mInput;
	};



}

#endif
