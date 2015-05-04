//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkRootForm.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

namespace mk
{
	RootForm::RootForm(UiWindow& uiWindow)
		: Form(make_unique<RootSheet>(uiWindow))
		, mWindow(uiWindow)
		, mLastTick(0)
		, mRootSheet(mSheet.as<RootSheet>())
	{
		mType = &cls();
	}

	RootForm::~RootForm()
	{}

	void RootForm::nextFrame(size_t tick, size_t delta)
	{
		Form::nextFrame(tick, delta);

		mLastTick = tick;
	}

	void RootForm::add(Form* form)
	{
		for(auto& obs : mObservers)
			obs->formAdded(form);
	}

	void RootForm::schemeRemove(Form* form)
	{
		for(auto& obs : mObservers)
			obs->formRemoved(form);
	}

	void RootForm::update(Form* form)
	{
		for(auto& obs : mObservers)
			obs->formUpdated(form);
	}

	void RootForm::alter(Form* form)
	{
		for(auto& obs : mObservers)
			obs->formAltered(form);
	}

	void RootForm::addObserver(FormUpdateObserver* observer)
	{
		observer->formAltered(this);

		mObservers.push_back(observer);
	}

	void RootForm::removeObserver(FormUpdateObserver* observer)
	{
		mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
	}
}
