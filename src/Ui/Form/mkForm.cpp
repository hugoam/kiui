//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkForm.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Iterable/mkReverse.h>

#include <Ui/Form/mkRootForm.h>

#include <Ui/Scheme/mkScheme.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	Lref Form::sNullString = lref(string(""));

	Form::Form(Style* style, const string& label, SchemeMapper mapper)
		: TypeObject(Form::cls())
		, mParent(nullptr)
		, mIndex(0)
		, mStyle(style)
		, mLabel(label)
		, mUpdated(0)
		, mScheme(this, mapper)
		, mWidget(nullptr)
	{}

	Form::~Form()
	{}

	void Form::setStyle(Style* style) { mStyle = style; /*mUpdated = this->rootForm()->lastTick();*/ }

	void Form::setLabel(const string& label) { mLabel = label; /*mUpdated = this->rootForm()->lastTick();*/ }

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

		for(auto& form : mContents)
			form->bind(this);
	}

	void Form::destroy()
	{
		mParent->scheme()->remove(this);
		mParent->remove(mIndex);
	}

	Form* Form::insert(unique_ptr<Form> pt, size_t index)
	{
		Form* form = pt.get();

		form->mParent = this;
		mContents.emplace(mContents.begin() + index, std::move(pt));
		this->reindex(index);

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

		unique_ptr<Form> pointer = std::move(mContents[pos]);
		mContents.erase(mContents.begin() + pos);
		this->reindex(pos);
		return pointer;
	}

	void Form::remove(size_t index)
	{
		mContents.erase(mContents.begin() + index);
		this->reindex(index);
	}

	void Form::destroy(size_t index)
	{
		mContents.at(index)->destroy();
	}

	void Form::reindex(size_t index)
	{
		for(size_t i = index; i < mContents.size(); ++i)
			mContents[i]->setIndex(index++);
	}

	string Form::concatIndex()
	{
		if(mParent)
			return mParent->concatIndex() + "." + toString(mIndex);
		else
			return toString(mIndex);
	}

	void Form::move(size_t from, size_t to)
	{
		std::swap(mContents[from], mContents[to]);
		this->reindex(from < to ? from : to);

		if(mWidget)
			mWidget->frame()->as<Stripe>()->move(from, to);
	}

	void Form::clear()
	{
		for(auto& pt : reverse_adapt(mContents))
			mScheme.remove(pt.get());
		mContents.clear();
	}

	void Form::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
	}

	Form* Form::prev()
	{
		return mParent->child(mIndex - 1);
	}

	Form* Form::next()
	{
		return mParent->child(mIndex + 1);
	}

	bool Form::contains(Form* form)
	{
		while(form && form != this)
			form = form->parent();

		return form == this;
	}

	Form* Form::findParent(Type* type)
	{
		if(this->type() == type)
			return this;
		else if(mParent)
			return mParent->findParent(type);
		else
			return nullptr;
	}

	Form* Form::find(const string& search)
	{
		size_t pos = search.find(".");
		if(pos != string::npos)
		{
			string id = search.substr(0, pos);
			string subsearch = search.substr(pos + 1);

			Form* next = this->child(fromString<size_t>(id));

			return next->find(subsearch);
		}
		else
		{
			return this->child(fromString<size_t>(search));
		}
	}
}
