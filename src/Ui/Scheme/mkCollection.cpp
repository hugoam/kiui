//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkCollection.h>

#include <Object/mkRef.h>
#include <Object/mkStem.h>

namespace mk
{
	Collection::Collection(Form* form, FormMapper mapper)
		: mMapper(mapper)
		, mForm(form)
	{}

	void Collection::bind(Form* form)
	{
		mForm = form;
		this->binded(form);
	}

	void Collection::add(Object* object, Type* type, size_t index)
	{
		Lref ref(object, type);
		unique_ptr<Form> form = mMapper(ref);
		mMapping[object] = form.get();
		if(index > mForm->contents().size())
			index = mForm->contents().size(); // @Warning, this should ultimately be removed, it's a kludge for collections with holes in their indexes
		mForm->insert(std::move(form), index);
	}

	void Collection::remove(Object* object, Type* type)
	{
		UNUSED(type);
		mForm->release(mMapping[object]->index());
		mMapping.erase(object);
	}

	void Collection::clear()
	{
		mMapping.clear();
		mForm->clear();
	}

	ObjectCollection::ObjectCollection(Form* form, Iterable<Object>* store, FormMapper mapper, bool fill)
		: Collection(form, mapper)
		, mStore(store)
		, mFill(fill)
	{
		this->bind(form);
	}

	void ObjectCollection::binded(Form* form)
	{
		UNUSED(form);
		if(mFill)
			mStore->viterateobj([this](Object* object, Type* type){ this->handleAdd(object, type); });
	}

	void ObjectCollection::handleAdd(Object* object, Type* type)
	{
		this->add(object, type, mStore->vindex(object));
	}

	void ObjectCollection::handleRemove(Object* object, Type* type)
	{
		this->remove(object, type);
	}

	bool ObjectCollection::handleClear()
	{
		this->clear();
		return true;
	}

	MetaCollection::MetaCollection(Form* form, Store<TypeObject>* store, FormMapper mapper)
		: Collection(form, mapper)
		, mStore(store)
	{
		this->bind(form);
	}

	MetaCollection::~MetaCollection()
	{
		mStore->removeObserver(this);
	}

	void MetaCollection::binded(Form* form)
	{
		UNUSED(form);
		mStore->addObserver(this);
	}

	void MetaCollection::handleAdd(TypeObject* object)
	{
		this->add(object, object->type(), mStore->vindex(object));
	}

	void MetaCollection::handleRemove(TypeObject* object)
	{
		this->remove(object, object->type());
	}

	bool MetaCollection::handleClear()
	{
		this->clear();
		return true;
	}
}
