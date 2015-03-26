//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPEOBJECT_H_INCLUDED
#define MK_TYPEOBJECT_H_INCLUDED

/* mk headers */
#include <Object/mkObjectForward.h>
#include <Object/mkType.h>

/* Standard */
#include <memory>
#include <vector>

namespace mk
{
	template <class T>
	struct BareType { typedef T type; };

	template <class T>
	struct BareType<const T&> { typedef T type; };

	template <class T>
	struct BareType<T&> { typedef T type; };

	template <class T>
	struct BareType<T*> { typedef T type; };

	template <class T>
	struct UnrefType : public BareType<T> {};

	template <class T>
	struct UnrefType<T*> { typedef T* type; };

	template <class T>
	struct Pass { typedef const T& ctype; typedef const T& forward; };

	template <class T>
	struct Pass<T*> { typedef T* ctype; typedef T* forward; };

	template <class T>
	struct Pass<unique_ptr<T>> { typedef const unique_ptr<T>& ctype; typedef unique_ptr<T> forward; };

	template <class T>
	struct Pass<std::vector<T>> { typedef const std::vector<T>& ctype; typedef std::vector<T>& forward; };

	template <class T>
	struct Copy
	{
		static T copy(const T& val) { return val; }
		static T copy(T& val) { return val; }
	};

	template <class T>
	struct Copy<unique_ptr<T>>
	{
		static unique_ptr<T> copy(const unique_ptr<T>& val) { UNUSED(val); return unique_ptr<T>(); }
		static unique_ptr<T> copy(unique_ptr<T>& val) { return std::move(val); }
	};

	template <class T>
	struct Copy<std::vector<T>>
	{
		static std::vector<T> copy(const std::vector<T>& val) { std::vector<T> vec; for(auto& o : val) vec.emplace_back(Copy<T>::copy(o)); return vec; }
		static std::vector<T> copy(std::vector<T>& val) { std::vector<T> vec; for(auto& o : val) vec.emplace_back(Copy<T>::copy(o)); return vec; }
	};

	template <class T>
	struct Assign
	{
		static inline void set(T& ref, T val) { ref = val; }
	};

	template <class T>
	struct Assign<const T&>
	{
		static inline void set(T& ref, const T& val) { ref = val; }
	};

	template <class T>
	struct Assign<unique_ptr<T>>
	{
		static inline void set(unique_ptr<T>& ref, unique_ptr<T> val) { ref = std::move(val); }
	};

	template <class T>
	struct Assign<std::vector<T>&>
	{
		static inline void set(std::vector<T>& ref, std::vector<T>& val) { ref.clear(); ref.resize(val.size()); for(size_t i = 0; i < val.size(); ++i) Assign<T>::set(ref[i], std::forward<T>(val[i])); }
	};

	template <class T>
	struct Assign<const std::vector<T>&>
	{
		static inline void set(std::vector<T>& ref, const std::vector<T>& val) { ref.clear(); ref.resize(val.size()); for(size_t i = 0; i < val.size(); ++i) Assign<T>::set(ref[i], val[i]); }
	};

	template <class T, bool isobject = std::is_base_of<Object, T>::value>
	struct RefObject
	{
		static inline Object* get(T& val) { return &val; }
	};

	template <class T>
	struct RefObject<T, false>
	{
		static inline Object* get(T& val) { UNUSED(val); return nullptr; }
	};
}

#endif // mkOBJECTREF_H_INCLUDED
