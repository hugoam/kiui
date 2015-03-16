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
	Scheme::Scheme(Form* form, SchemeMapper mapper)
		: mForm(form)
		, mMapper(mapper)
	{}

	unique_ptr<Widget> Scheme::makeWidget()
	{
		if(mMapper)
			return mMapper();

		Style* style = mForm->style();

		if(style && UiWindow::sDispatch.find(style->name()) != UiWindow::sDispatch.end())
			return UiWindow::sDispatch[style->name()](mForm);
		else if(mForm->container())
			return make_unique<Sheet>(nullptr, mForm);
		else
			return make_unique<Widget>(nullptr, mForm);
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

	void Scheme::reset(SchemeMapper mapper)
	{
		mMapper = mapper;
		this->clear();
		this->apply();
	}

	void Scheme::apply()
	{
		mForm->parent()->scheme()->append(mForm);
		mSheet = mForm->widget()->as<Sheet>();

		for(auto& child : mForm->contents())
			this->append(child.get());
	}

	void Scheme::clear()
	{
		mForm = nullptr;
		mSheet->destroy();

		for(auto& child : mForm->contents())
			this->remove(child.get());
	}
}
