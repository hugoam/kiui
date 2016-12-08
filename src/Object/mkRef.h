//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_OBJECTREF_H
#define MK_OBJECTREF_H

/* mk headers */
#include <Object/mkObjectForward.h>
#include <Object/mkTyped.h>
#include <Object/mkTypeUtils.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUnique.h>

/* Standard */
#include <memory>
#include <vector>
#include <map>
#include <array>

namespace mk
{
	template <class T>
	class Any;

	class MK_OBJECT_EXPORT None
	{
	public:
		template <class T>
		operator T() { return T(); }

		static Type& cls() { static Type ty; return ty; }
	};

	class MK_OBJECT_EXPORT Ref
	{
	public:
		Ref(Type& type) : m_type(type), m_object(nullptr), m_update(0) {}
		Ref(Object& object, Type& type) : m_type(type), m_object(&object), m_update(0) {}
		virtual ~Ref() {}

		inline Object* object() const { return m_object; }
		inline Type& type() const { return m_type; }
		inline Imprint& imprint() const { return m_type.imprint(); }
		inline bool null() const { return &m_type == &None::cls(); }
		inline void setobject(Object& object) { m_object = &object; ++m_update; }
		inline void setpointer(Object* object) { m_object = object; ++m_update; }
		inline size_t update() { return m_update; }

		virtual unique_ptr<Ref> clone() const { return make_unique<Ref>(*m_object, m_type); };

		virtual void setString(const string& value) { UNUSED(value); }
		virtual string getString() { return ""; }

		template <class T>
		inline Any<T>* any() { return static_cast<Any<T>*>(this); }

		template <class T>
		inline const Any<T>* any() const { return static_cast<const Any<T>*>(this); }

		template <class T>
		inline T& ref() { return this->any<T>()->ref(); }

		template <class T>
		inline const T& get() const { return this->any<T>()->get(); }

		template <class T>
		inline void set(typename Pass<T>::ctype val) { this->any<T>()->set(std::forward<typename Pass<T>::ctype>(val)); }

		template <class T>
		inline T& as() const { return m_object->as<T>(); }

		template <class T>
		inline T copy() { return this->any<T>()->copy(); }

		template <class T>
		inline T copy() const { return this->any<T>()->copy(); }

		Ref(const Ref& ref) = delete;
		Ref& operator=(const Ref& ref) = delete;

	protected:
		Object* m_object;
		Type& m_type;
		size_t m_update;
	};

	template <class T>
	class Allocator
	{};

	template <class T>
	class Any : public Ref, public Allocator<T>
	{
	public:
		Any(typename Pass<T>::forward value) : Ref(typecls<T>()), m_content(Copy<T>::copy(value)) { m_object = RefObject<T>::get(m_content); }
		Any() : Ref(typecls<T>()), m_content() { m_object = RefObject<T>::get(m_content); }

		unique_ptr<Ref> clone() const { return make_unique<Any<T>>(this->copy()); }

		void setString(const string& value) { fromString<T>(value, m_content); ++m_update; }
		string getString() { return toString<T>(m_content); }

		T& ref() { return m_content; }
		const T& get() const { return m_content; }
		T copy() { return Copy<T>::copy(m_content); }
		T copy() const { return Copy<T>::copy(m_content); }

		void assign(typename Pass<T>::forward val) { Assign<typename Pass<T>::forward>::set(m_content, std::forward<typename Pass<T>::forward>(val)); ++m_update; }
		void set(typename Pass<T>::ctype val) { Assign<typename Pass<T>::ctype>::set(m_content, std::forward<typename Pass<T>::ctype>(val)); ++m_update;  }

	public:
		T m_content;
	};

	template <>
	class MK_OBJECT_EXPORT Any<None> : public Ref
	{
	public:
		Any() : Ref(None::cls()) {}

		unique_ptr<Ref> clone() const { return make_unique<Any<None>>(); }
	};

	template <class T, bool isobj = std::is_base_of<Object, typename BareType<T>::type>::value, bool isstruct = std::is_base_of<Struct, typename BareType<T>::type>::value>
	struct MakeRef
	{
		static unique_ptr<Ref> make(typename Pass<T>::forward val) { return make_unique<Any<T>>(std::forward<typename Pass<T>::forward>(val)); };
	};

	template <class T>
	struct MakeRef<T, true, false>
	{
		static unique_ptr<Ref> make(T& obj) { return make_unique<Ref>(obj, T::cls()); };
	};

	template <class T>
	struct MakeRef<T*, true, false>
	{
		static unique_ptr<Ref> make(T* obj) { return obj ? make_unique<Ref>(*obj, T::cls()) : make_unique<Ref>(T::cls()); };
	};

	class MK_OBJECT_EXPORT Lref
	{
	public:
		Lref(unique_ptr<Ref> ref) : m_ref(std::move(ref)) {}
		Lref(TypeObject& object) : m_ref(make_unique<Ref>(object, object.type())) {}
		Lref(Object& object, Type& type) : m_ref(make_unique<Ref>(object, type)) {}
		Lref(Type& type) : m_ref(make_unique<Ref>(type)) {}
		Lref() : m_ref(make_unique<Any<None>>()) {}

		Lref(Lref&& ref) : m_ref(std::move(ref.m_ref)) {}
		Lref(const Lref& ref) : m_ref(ref.m_ref ? ref->clone() : nullptr) {}
		Lref& operator=(const Lref& rhs) { Lref(rhs).swap(*this); return *this; }

		Lref& swap(Lref& rhs) { std::swap(m_ref, rhs.m_ref); return *this; }

		Ref* operator->() { return m_ref.get(); }
		const Ref* operator->() const { return m_ref.get(); }

	protected:
		unique_ptr<Ref> m_ref;
	};

	template <class T>
	inline Lref lref(T&& val) { return Lref(MakeRef<typename UnrefType<T>::type>::make(std::forward<typename Pass<T>::forward>(val))); }

	typedef std::map<string, Lref> LrefDict;
	typedef std::vector<Lref> LrefVector;

	template <class T>
	inline int packLref(LrefVector& vec, T&& val)
	{
		vec.push_back(lref(std::forward<T>(val)));
		return 0;
	}

	template <class... Args>
	inline LrefVector packLrefs(Args&&... args)
	{
		LrefVector ret;
		std::array<int, sizeof...(Args)> pass { packLref<Args>(ret, std::forward<Args>(args))... };
		return ret;
	}
}

#endif // MK_OBJECTREF_H
