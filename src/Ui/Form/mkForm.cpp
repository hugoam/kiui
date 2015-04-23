//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkForm.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Iterable/mkReverse.h>

#include <Ui/Form/mkRootForm.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	Lref Form::sNullString = lref(string(""));

	Form::Form(unique_ptr<Sheet> sheet)
		: TypeObject(Form::cls())
		, mParent(nullptr)
		, mIndex(0)
		, mUniqueSheet(std::move(sheet))
		, mSheet(*mUniqueSheet.get())
		, mContainer(mUniqueSheet.get())
	{}

	Form::~Form()
	{}

	RootForm& Form::rootForm()
	{
		if(mParent)
			return mParent->rootForm();
		else if(mType == &RootForm::cls())
			return this->as<RootForm>();
	}

	UiWindow& Form::uiWindow()
	{
		return rootForm().uiWindow();
	}

	const string& Form::name()
	{
		return mSheet.name();
	}

	void Form::bind(Form* parent)
	{
		mParent = parent;
		mParent->container()->vappend(std::move(mUniqueSheet));
	}

	void Form::unbind()
	{
		mUniqueSheet.reset(static_cast<Sheet*>(mParent->container()->vrelease(mSheet).release()));
		mParent = nullptr;
	}
	
	void Form::destroy()
	{
		mParent->container()->vrelease(mSheet);
		mParent->remove(mIndex);
	}

	Form* Form::insert(unique_ptr<Form> pt, size_t index)
	{
		Form* form = pt.get();

		form->mParent = this;
		mContents.emplace(mContents.begin() + index, std::move(pt));
		this->reindex(index);
		form->bind(this);

		return form;
	}

	Form* Form::append(unique_ptr<Form> form)
	{
		return this->insert(std::move(form), mContents.size());
	}

	unique_ptr<Form> Form::release(size_t pos)
	{
		//if(mContents.at(pos)->widget())
		//	mContents.at(pos)->widget().detach();

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

		mSheet.stripe().move(from, to);
	}

	void Form::clear()
	{
		for(auto& form : reverse_adapt(mContents))
			mContainer->vrelease(form->sheet());
		mContents.clear();
	}

	void Form::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
	}

	Form* Form::prev()
	{
		return mParent->at(mIndex - 1);
	}

	Form* Form::next()
	{
		return mParent->at(mIndex + 1);
	}

	bool Form::contains(Form* form)
	{
		while(form && form != this)
			form = form->parent();

		return form == this;
	}

	Form* Form::findParent(Type* type)
	{
		if(&this->type() == type)
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

			Form* next = this->at(fromString<size_t>(id));

			return next->find(subsearch);
		}
		else
		{
			return this->at(fromString<size_t>(search));
		}
	}

	void Form::reset(unique_ptr<Sheet> sheet)
	{
		/*for(auto& form : mContents)
			form->unbind();

		mUniqueSheet = std::move(sheet);
		mSheet = mUniqueSheet.get();
		mContainer = mUniqueSheet.get();

		for(auto& form : mContents)
			form->bind(this);*/
	}
}
