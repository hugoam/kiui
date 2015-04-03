//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INDEXER_H_INCLUDED
#define MK_INDEXER_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Iterable/mkIterable.h>
#include <Object/mkTyped.h>

/* Standard */
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace mk
{
#ifndef OBJECT_EXPORT
	template class MK_OBJECT_EXPORT Store<TypeObject>;
#endif

	class MK_OBJECT_EXPORT Indexer : public Store<TypeObject>
	{
	public:
		Indexer(Type* type) : mType(type), mCount(0), mObjects() { mType->setupIndexer(this); mObjects.emplace_back(nullptr); }
		~Indexer() {}

		std::vector<IdObject*>& objects() { return mObjects; }

		size_t vsize() const { return size(); }
		void vclear() { clear(); }
		Type* sequenceType() const { return mType; }
		void vadd(TypeObject* object) { this->add(object->as<IdObject>()); }
		size_t vindex(Object* object) { return object->as<IdObject>()->id(); }
		size_t vindex(TypeObject* object) { return object->as<IdObject>()->id(); }

		void add(IdObject* object) { if(object->id() >= mObjects.size()) mObjects.resize(object->id() + 1); mObjects[object->id()] = object; ++mCount; }
		void insert(IdObject* object, Id id) { if(id >= mObjects.size()) mObjects.resize(id + 1); mObjects[id] = object; ++mCount; }
		void remove(IdObject* object) { mObjects[object->id()] = nullptr; --mCount; }
		IdObject* at(Id id) { if(id < mObjects.size()) return mObjects[id]; else return nullptr; }
		Id alloc() { return mObjects.size(); }

		size_t size() const { return mCount; }
		void viterateobj(const std::function<void(Object*)>& callback) { for(Object* object : mObjects) callback(object); }
		void clear() { mObjects.clear(); mCount = 0; }

		void viterate(const std::function<void(TypeObject*)>& callback) { for(TypeObject* object : mObjects) callback(object); }
		TypeObject* vat(size_t pos) { return at(pos); }

		void addObserver(StoreObserver<TypeObject>* observer)
		{
			mObservers.push_back(observer);
			for(TypeObject* object : mObjects)
				if(object)
					observer->handleAdd(object);
		}

		void removeObserver(StoreObserver<TypeObject>* observer)
		{
			mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
		}

	protected:
		Type* mType;
		std::vector<IdObject*> mObjects;
		size_t mCount;
		std::vector<StoreObserver<TypeObject>*> mObservers;
	};

	template <class T, class I = void>
	class Indexed : public Typed<T, I>
	{
	public:
		static inline Indexer* indexer() { static Indexer ind(T::cls()); return &ind; } //return &sIndexer; }
	};
}

#endif // MK_INDEXER_H_INCLUDED
