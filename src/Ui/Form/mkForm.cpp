//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkForm.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Store/mkReverse.h>

#include <Ui/Form/mkRootForm.h>

#include <Ui/Scheme/mkScheme.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

namespace mk
{
	string Form::sNullString;

	Form::Form(const string& cls, const string& label, SchemeMapper containerMapper, SchemeMapper elementMapper)
		: TypeObject(Form::cls())
		, mParent(nullptr)
		, mIndex(0)
		, mCls(cls)
		, mLabel(label)
		, mLastTick(0)
		, mUpdated(0)
		, mScheme(this, containerMapper, elementMapper)
		, mWidget(nullptr)
	{}

	Form::~Form()
	{}

	RootForm* Form::rootForm()
	{
		if(mParent)
			return mParent->rootForm();
		else if(mType == RootForm::cls())
			return this->as<RootForm>();
		else
			return nullptr;
	}

	UiWindow* Form::uiWindow()
	{
		return rootForm()->uiWindow();
	}

	void Form::bind(Form* parent)
	{
		mParent = parent;
		mParent->scheme()->append(this);

		for(auto& form : mContents.store())
			form->bind(this);
	}

	void Form::destroy()
	{
		mParent->scheme()->remove(this);
		mParent->mContents.remove(mIndex);
	}

	Form* Form::insert(unique_ptr<Form> pt, size_t index)
	{
		Form* form = pt.get();

		form->mParent = this;
		mContents.insert(std::move(pt), index);

		if(mWidget)
			form->bind(this);

		return form;
	}

	Form* Form::append(unique_ptr<Form> form)
	{
		return this->insert(std::move(form), mContents.size());
	}

	unique_ptr<Form> Form::release(size_t pos)
	{
		if(mContents.at(pos)->widget())
			mContents.at(pos)->widget()->detach();
		return mContents.release(pos);
	}

	void Form::remove(size_t index)
	{
		mContents.at(index)->destroy();
	}

	string Form::concatIndex()
	{
		if(mParent)
			return mParent->concatIndex() + "." + toString(mIndex);
		else
			return toString(mIndex);
	}

	void Form::setIndex(size_t index)
	{
		mIndex = index;
		this->updateIndex();
	}

	void Form::move(size_t from, size_t to)
	{
		mContents.move(from, to);
		if(mWidget)
			mWidget->frame()->as<Stripe>()->move(from, to);
	}

	void Form::clear()
	{
		for(auto& pt : reverse_adapt(mContents.store()))
			mScheme.remove(pt.get());
		mContents.clear();
	}

	void Form::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
	}

	Form* Form::prev()
	{
		return mParent->contents()->at(mIndex - 1);
	}

	Form* Form::next()
	{
		return mParent->contents()->at(mIndex + 1);
	}

	bool Form::contains(Form* form)
	{
		while(form && form != this)
			form = form->parent();

		return form == this;
	}

	Form* Form::findParent(const string& cls)
	{
		if(mCls == cls)
			return this;
		else if(mParent)
			return mParent->findParent(cls);
		else
			return 0;
	}

	Form* Form::find(const string& search)
	{
		size_t pos = search.find(".");
		if(pos != string::npos)
		{
			string id = search.substr(0, pos);
			string subsearch = search.substr(pos + 1);

			Form* next = mContents.at(fromString<size_t>(id));

			return next->find(subsearch);
		}
		else
		{
			return mContents.at(fromString<size_t>(search));
		}
	}

	/*void Form::added()
	{
	rootForm()->add(this);
	this->flagUptod();
	}

	void Form::removed()
	{
	rootForm()->remove(this);
	}

	void Form::updated()
	{
	mWidget->flagFormUpdate();
	rootForm()->update(this);
	this->flagUptod();
	}

	void Form::altered()
	{
	//rootForm()->alter(this);
	this->flagUptod();
	}*/

}
