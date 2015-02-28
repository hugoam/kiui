//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkScheme.h>

#include <Object/mkStem.h>

#include <Ui/Scheme/mkCollection.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	Scheme::Scheme(Form* form, SchemeMapper mapper, SchemeMapper elementMapper)
		: mForm(form)
		, mMapper(mapper)
		, mElementMapper(elementMapper)
	{}

	unique_ptr<Widget> Scheme::makeWidget()
	{
		if(mMapper)
			return mMapper();

		std::vector<string> classes = splitString(mForm->clas(), " ");

		for(string& cls : classes)
			if(UiWindow::sDispatch.find(cls) != UiWindow::sDispatch.end())
				return UiWindow::sDispatch[cls](mForm);

		if(mForm->parent()->widget()->elementStyle(mForm->clas())->d_overflow == SCROLL)
			return make_unique<ScrollSheet>("", mForm);
		else if(mForm->container())
			return make_unique<Sheet>("", mForm);
		else
			return make_unique<Widget>("", mForm);
	}

	void Scheme::append(Form* form)
	{
		unique_ptr<Widget> widget = form->scheme()->makeWidget();

		form->setWidget(widget.get());
		form->scheme()->setSheet(widget->as<Sheet>());

		Sheet* wrapper = mSheet->vaddwrapper(widget.get());
		wrapper ? wrapper->vappend(std::move(widget)) : mSheet->vappend(std::move(widget));
	}

	void Scheme::remove(Form* form)
	{
		mSheet->vrelease(form->widget());
	}

	void Scheme::reset(SchemeMapper mapper, SchemeMapper elementMapper)
	{
		mMapper = mapper;
		mElementMapper = elementMapper;
		this->clear();
		this->apply();
	}

	void Scheme::apply()
	{
		mForm->parent()->scheme()->append(mForm);
		mSheet = mForm->widget()->as<Sheet>();

		for(auto& child : mForm->contents()->store())
			this->append(child.get());
	}

	void Scheme::clear()
	{
		mForm = nullptr;
		mSheet->destroy();

		for(auto& child : mForm->contents()->store())
			this->remove(child.get());
	}
}
