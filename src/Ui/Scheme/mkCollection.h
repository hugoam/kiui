//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_COLLECTION_H_INCLUDED
#define MK_COLLECTION_H_INCLUDED

/* mk headers */
#include <Object/Util/mkMake.h>
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>
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

		void add(Object& object, Type& type, size_t index);
		void remove(Object& object, Type& type);
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

		void handleAdd(Object& object, Type& type);
		void handleRemove(Object& object, Type& type);
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

		void handleAdd(TypeObject& object);
		void handleRemove(TypeObject& object);
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
			, GenericObserver<T>(tstore, this)
		{}
	};

	template <class T, class R>
	struct ResPointer { static inline T* pointer(const R& r) { return r; } };

	template <class T>
	struct ResPointer<T, unique_ptr<T>> { static inline T* pointer(const unique_ptr<T>& r) { return r.get(); } };


	template <class R, class T>
	class VectorObserver
	{
	public:
		VectorObserver(const std::vector<R>& vector) : mVector(vector) {}

		void update(size_t tick)
		{
			bool modified = false;

			for(size_t i = 0; i < mVector.size(); ++i)
			{
				if(i >= mCopy.size())
				{
					for(; i < mVector.size(); ++i)
						this->handleAdd(ResPointer<T, R>::pointer(mVector[i]), i);
					modified = true;
					break;
				}

				if(ResPointer<T, R>::pointer(mVector[i]) == mCopy[i])
					continue;

				size_t j = i;
				while(j < mVector.size()-1 && j < mCopy.size()-1 && ResPointer<T, R>::pointer(mVector[i]) != mCopy[j] && ResPointer<T, R>::pointer(mVector[j]) != mCopy[i])
					++j;

				if(ResPointer<T, R>::pointer(mVector[i]) == mCopy[j])
					for(; i < j; ++i)
						this->handleAdd(ResPointer<T, R>::pointer(mVector[i]), i);
				else if(ResPointer<T, R>::pointer(mVector[j]) == mCopy[i])
					for(; i < j; ++i)
						this->handleRemove(mCopy[i], i);
				else
				{
					this->handleAdd(ResPointer<T, R>::pointer(mVector[i]), i);
					this->handleRemove(mCopy[i], i);
				}

				modified = true;
			}

			if(modified)
			{
				mCopy.clear();
				mCopy.resize(mVector.size());
				for(size_t i = 0; i < mVector.size(); ++i)
					mCopy[i] = ResPointer<T, R>::pointer(mVector[i]);
			}
		}

		virtual void handleAdd(T* object, size_t index) = 0;
		virtual void handleRemove(T* object, size_t index) = 0;

	protected:
		const std::vector<R>& mVector;
		std::vector<T*> mCopy;
	};

	template <class R, class T>
	class VectorCollection : public Collection, public VectorObserver<R, T>
	{
	public:
		VectorCollection(Form* form, const std::vector<R>& vector, FormMapper mapper)
			: Collection(form, mapper)
			, VectorObserver<R, T>(vector)
		{}

		void handleAdd(T* object, size_t index)
		{
			this->add(object , T::cls(), index);
		}

		void handleRemove(T* object, size_t index)
		{
			this->remove(object, T::cls());
		}
	};
}

#endif // MK_WIDGET_H_INCLUDED
