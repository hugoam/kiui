//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_COLLECTION_H_INCLUDED
#define MK_COLLECTION_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Util/mkMake.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkButton.h>
#include <Ui/Form/mkDropper.h>
#include <Ui/Form/mkHook.h>

namespace mk
{
	typedef std::function<unique_ptr<Form> (Lref&)> FormMapper;

	template <class T_Form>
	unique_ptr<Form> lrefFormMapper(Lref& lref) { return make_unique<T_Form>(lref); }

	template <class T_Form>
	unique_ptr<Form> objectFormMapper(Lref& lref) { return make_unique<T_Form>(lref->object(), lref->type()); }

	template <class T_Form, class T_Object>
	unique_ptr<Form> typedFormMapper(Lref& lref) { return make_unique<T_Form>(lref->as<T_Object>()); }

	class MK_UI_EXPORT Collection
	{
	public:
		Collection(Form* form, FormMapper mapper);

		void bind(Form* scheme);
		Form* form() { return mForm; }

		virtual void binded(Form* form) { UNUSED(form); }

		void add(Object* object, Type* type, size_t index);
		void remove(Object* object, Type* type);
		void clear();

		Form* mappedForm(Object* object) { return mMapping[object]; }

	protected:
		FormMapper mMapper;
		std::map<Object*, Form*> mMapping;
		Form* mForm;
	};

	class MK_UI_EXPORT ObjectCollection : public Collection, public StoreObserver<Object>
	{
	public:
		ObjectCollection(Form* form, Iterable<Object>* store, FormMapper mapper, bool fill = false);

		void binded(Form* form);

		void handleAdd(Object* object, Type* type);
		void handleRemove(Object* object, Type* type);
		bool handleClear();

	protected:
		Iterable<Object>* mStore;
		bool mFill;
	};

	class MK_UI_EXPORT MetaCollection : public Collection, public StoreObserver<TypeObject>
	{
	public:
		MetaCollection(Form* form, Store<TypeObject>* genstore, FormMapper mapper);
		~MetaCollection();

		void binded(Form* form);

		void handleAdd(TypeObject* object);
		void handleRemove(TypeObject* object);
		bool handleClear();

	protected:
		Store<TypeObject>* mStore;
	};

	template <class T_Form>
	class MapCollection : public ObjectCollection
	{
	public:
		MapCollection(Form* form, Iterable<Object>* store)
			: ObjectCollection(form, store, &lrefFormMapper<T_Form>)
		{}
	};

	template <class T>
	class TypedCollection : public ObjectCollection, public GenericObserver<T>
	{
	public:
		TypedCollection(Form* form, Iterable<Object>* store, Store<T>* tstore, FormMapper mapper)
			: ObjectCollection(form, store, mapper)
			, GenericObserver(tstore, this)
		{}
	};
}

#endif // MK_WIDGET_H_INCLUDED
