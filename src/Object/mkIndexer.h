//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INDEXER_H_INCLUDED
#define MK_INDEXER_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Iterable/mkIterable.h>
#include <Object/Util/mkNonCopy.h>
#include <Object/mkTyped.h>

/* Standard */
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace mk
{
	class MK_OBJECT_EXPORT Indexer : public Store<Object>, public NonCopy
	{
	public:
		Indexer(Type& type) : m_type(type), m_count(0), m_next(0), m_objects(1, nullptr) {}
		~Indexer() {}

		std::vector<IdObject*>& objects() { return m_objects; }

		Type& elementType() const { return m_type; }

		void add(Object& object) { this->add(object.as<IdObject>()); }
		void remove(Object& object) { this->remove(object.as<IdObject>()); }

		void add(IdObject& object) { this->resize(object); m_objects[object.id()] = &object; ++m_count; notifyAdd(object); }
		void insert(IdObject& object, Id id) { this->resize(id); m_objects[id] = &object; ++m_count; notifyAdd(object); }
		void remove(IdObject& object) { m_objects[object.id()] = nullptr; --m_count; notifyRemove(object); }
		bool has(IdObject& object) { return std::find(m_objects.begin(), m_objects.end(), &object) != m_objects.end(); }
		IdObject& at(Id id) { return *m_objects[id]; }
		IdObject* atSafe(Id id) { if(id < m_objects.size()) return m_objects[id]; else return nullptr; }
		Id alloc() { return m_next++; }

		inline void resize(IdObject& object) { if(object.id() >= m_objects.size()) m_objects.resize(object.id() * 2); }
		inline void resize(Id id) { if(id >= m_objects.size()) m_objects.resize(id * 2); }

		size_t size() const { return m_count; }
		void iterate(const std::function<void(Object&)>& callback) const { for(Object* object : m_objects) if(object) callback(*object); }
		bool has(Object& object) const { return this->has(object.as<IdObject>()); }

		void clear() { m_objects.clear(); m_count = 0; }

		void notifyAdd(Object&/* object*/)
		{
			//for(StoreObserver<Object>* observer : m_observers)
			//	observer->handleAdd(object);
		}

		void notifyRemove(Object&/* object*/)
		{
			//for(StoreObserver<Object>* observer : m_observers)
			//	observer->handleRemove(object);
		}

		void observe(StoreObserver<Object>& observer)
		{
			m_observers.push_back(&observer);
			for(TypeObject* object : m_objects)
				if(object)
					observer.handleAdd(*object);
		}

		void unobserve(StoreObserver<Object>& observer)
		{
			m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());
		}

		void unobserveNotify(StoreObserver<Object>& observer)
		{
			m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());
			for(TypeObject* object : m_objects)
				if(object)
					observer.handleRemove(*object);
		}

	protected:
		Type& m_type;
		std::vector<IdObject*> m_objects;
		size_t m_count;
		size_t m_next;
		std::vector<StoreObserver<Object>*> m_observers;
	};
}

#endif // MK_INDEXER_H_INCLUDED
