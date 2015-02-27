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
	struct Copyable { static const bool value = true; };

	template <class T>
	struct Copyable<std::unique_ptr<T>> { static const bool value = false; };

	template <class T>
	struct Copyable<std::vector<T>> { static const bool value = Copyable<T>::value; };

	template <class T>
	struct PassValue { typedef T type; };

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
	struct Pass { typedef const T& ctype; typedef T type; typedef typename PassValue<T>::type forward; };

	template <class T>
	struct Pass<T*> { typedef T* ctype; typedef T* type; typedef T* forward; };

	template <class T>
	struct Pass<std::unique_ptr<T>> { typedef const std::unique_ptr<T>& ctype; typedef std::unique_ptr<T> type; typedef std::unique_ptr<T> forward; };

	template <class T>
	struct Pass<std::vector<T>> { typedef const std::vector<T>& ctype; typedef std::vector<T> type; typedef std::vector<T>& forward; };

	template <class T>
	struct Copy
	{
		static T copy(const T& val) { return val; }
		static T copy(T& val) { return val; }
	};

	template <class T>
	struct Copy<std::unique_ptr<T>>
	{
		static std::unique_ptr<T> copy(const std::unique_ptr<T>& val) { return std::unique_ptr<T>(); }
		static std::unique_ptr<T> copy(std::unique_ptr<T>& val) { return std::move(val); }
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
	struct Assign<std::unique_ptr<T>>
	{
		static inline void set(std::unique_ptr<T>& ref, std::unique_ptr<T> val) { ref = std::move(val); }
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
		static inline Object* get(T& val) { return nullptr; }
	};

	template <class T>
	struct RefMget
	{
		static inline T mget(const Ref* ref) { return ref->any<T>()->copy(); }
		typedef T type;
	};

	template <class T>
	struct RefMget<T*>
	{
		static inline T* mget(const Ref* ref) { return ref->as<T>(); }
		typedef T* type;
	};

	template <class T>
	struct RefAssign
	{
		static inline void set(Ref* ref, typename Pass<T>::forward val) { Assign<typename Pass<T>::forward>::set(ref->any<T>()->ref(), std::forward<typename Pass<T>::forward>(val)); }
	};

	template <class T>
	struct RefAssign<T*>
	{
		static inline void set(Ref* ref, T* obj) { ref->assign(obj); }
	};

	template <class T>
	struct RefSet
	{
		static inline void set(Ref* ref, typename Pass<T>::ctype val) { Assign<typename Pass<T>::ctype>::set(ref->any<T>()->ref(), std::forward<typename Pass<T>::ctype>(val)); }
	};

	template <class T>
	struct RefSet<T*>
	{
		static inline void set(Ref* ref, T* obj) { ref->assign(obj); }
	};
}

#endif // mkOBJECTREF_H_INCLUDED
