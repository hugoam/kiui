//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ROOTFORM_H_INCLUDED
#define MK_ROOTFORM_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkMake.h>
#include <Ui/Form/mkForm.h>
#include <Ui/mkUiForward.h>

#include <map>

namespace mk
{
	class MK_UI_EXPORT FormUpdateObserver
	{
	public:
		virtual void formAdded(Form* form) = 0;
		virtual void formRemoved(Form* form) = 0;
		virtual void formUpdated(Form* form) = 0;
		virtual void formAltered(Form* form) = 0;
	};

	class MK_UI_EXPORT RootForm : public Form, public Typed<RootForm>
	{
	public:
		RootForm(UiWindow* window);
		~RootForm();

		RootForm* rootForm() { return this; }

		UiWindow* uiWindow() { return mWindow; }
		RootSheet* rootSheet() { return mRootSheet; }

		size_t lastTick() { return mLastTick; }

		void add(Form* form);
		void schemeRemove(Form* form);
		void update(Form* form);
		void alter(Form* form);

		void addObserver(FormUpdateObserver* observer);
		void removeObserver(FormUpdateObserver* observer);

		void nextFrame(size_t tick, size_t delta);

		using Typed<RootForm>::cls;

	protected:
		User* mUser;
		UiWindow* mWindow;
		size_t mLastTick;
		RootSheet* mRootSheet;
		std::vector<FormUpdateObserver*> mObservers;
	};
}

#endif // MK_FORM_H_INCLUDED
