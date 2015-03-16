//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INDEXSTORE_H_INCLUDED
#define MK_INDEXSTORE_H_INCLUDED

namespace mk
{
	// @todo : rewrite these and Registry functions using index directly since we have random access (vector) as underlying storage
	
	template <class T_Array>
	class Index : public T_Array
	{
	public:
		typedef typename T_Array::T T;
		typedef typename T_Array::R R;

	public:
		Index() : T_Array() {}

		void reindex(size_t index)
		{
			for(size_t i = index; i < this->mStore.size(); ++i)
				this->mStore[i]->setIndex(index++);
		}

		bool checkIndexes()
		{
			size_t index = 0;
			for(auto& obj : this->mStore)
				if(obj->index() != index++)
					return false;

			return true;
		}

		void move(size_t from, size_t to)
		{
			T_Array::move(from, to);
			reindex(from < to ? from : to);
		}

		void add(R object)
		{
			object->setIndex(this->mStore.size());
			T_Array::add(std::forward<R>(object));
		}

		void insert(R object, size_t index)
		{
			object->setIndex(index);
			T_Array::insert(std::forward<R>(object), index);
			reindex(index);
		}

		void remove(T* object)
		{
			Id index = object->index();
			T_Array::remove(index);
			reindex(index);
		}

		void remove(size_t index)
		{
			T_Array::remove(index);
			reindex(index);
		}

		R release(size_t index)
		{
			R res = T_Array::release(index);
			reindex(index);
			return res;
		}

		void swap(size_t from, size_t to)
		{
			auto fromit = this->mStore.begin() + from;
			auto toit = this->mStore.begin() + to;

			(*toit).swap(*fromit);

			(*toit)->setIndex(to);
			(*fromit)->setIndex(from);
		}

		size_t vindex(Object* object)
		{
			return object->as<T>()->index();
		}
	};
}

#endif // MK_INDEXSTORE_H_INCLUDED
