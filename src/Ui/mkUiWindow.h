//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UIWINDOW_H
#define MK_UIWINDOW_H

/* mk Front */
#include <Object/Util/mkColour.h>
#include <Object/Store/mkArray.h>
#include <Object/Store/mkRegistry.h>
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Controller/mkController.h>
#include <Ui/mkRenderWindow.h>

namespace mk
{
	template <class T_Widget, class T_Form>
	unique_ptr<Widget> createWidget(Form* form)
	{
		return make_unique<T_Widget>(form->as<T_Form>());
	}

	class MK_UI_EXPORT UiWindow : public InputDispatcher
	{
	public:
		UiWindow(User* user = nullptr);
		~UiWindow();

		void setup(RenderWindow* renderWindow, InkWindow* inkWindow, InputWindow* inputWindow);
		void init();

		RenderWindow* renderWindow() { return mRenderWindow; }
		InkWindow* inkWindow() { return mInkWindow; }
		RootSheet* rootSheet() { return mRootSheet; }
		RootForm* rootForm() { return mRootForm.get(); }

		User* user() { return mUser; }

		Styler* styler() { return mStyler.get(); }

		void resize(size_t width, size_t height);

		void setRootForm(RootForm* form);

		bool nextFrame();
		bool shutdownRequested() { return mShutdownRequested; }
		bool shiftPressed() { return mShiftPressed; }
		bool ctrlPressed() { return mCtrlPressed; }

		float width() { return mWidth; }
		float height() { return mHeight; }

		void dispatchKeyPressed(KeyCode key, char c);
		void dispatchKeyReleased(KeyCode key, char c);

		void dispatchMousePressed(float x, float y, MouseButton button);
		void dispatchMouseMoved(float x, float y, float xDif, float yDif);
		void dispatchMouseReleased(float x, float y, MouseButton button);
		void dispatchMouseWheeled(float x, float y, float amount);

		static std::map<string, std::function<unique_ptr<Widget>(Form*)>> sDispatch;

	protected:
		float mWidth;
		float mHeight;

		RenderWindow* mRenderWindow;
		InkWindow* mInkWindow;
		InputWindow* mInputWindow;

		unique_ptr<Styler> mStyler;

		unique_ptr<RootForm> mRootForm;
		RootSheet* mRootSheet;

		InputController* mController;

		bool mShiftPressed;
		bool mCtrlPressed;

		bool mShutdownRequested;

		Clock mClock;

		User* mUser;
	};
}

#endif
