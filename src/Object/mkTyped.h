//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPED_H_INCLUDED
#define MK_TYPED_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkType.h>
#include <Object/mkObject.h>

namespace mk
{
	template <class T>
	inline Type* typecls()
	{
		return T::cls();
	}

	template <> inline Type* typecls<void>() { return nullptr; }

	template <class T, class S = void, class I = void>
	class Typed
	{
	public:
		static inline Type* cls() { return &sType; }

	private:
		static Type sType;
	};

	template <class T, class S, class I>
	Type Typed<T, S, I>::sType(typecls<I>());

	template <class T>
	T* upcast(TypeObject* object)
	{
		if(object->type()->upcast(Typed<T>::cls()))
			return static_cast<T*>(object);

		return 0;
	}

	template <class T>
	T* downcast(TypeObject* object)
	{
		if(object->type() == Typed<T>::cls())
			return static_cast<T*>(object);

		return 0;
	}

	template <class T>
	inline Type* typeof()
	{
		return Typed<T>::cls();
	}

	template <> inline Type* typecls<bool>() { return Typed<bool>::cls(); }
	template <> inline Type* typecls<int>() { return Typed<int>::cls(); }
	template <> inline Type* typecls<unsigned int>() { return Typed<unsigned int>::cls(); }
	template <> inline Type* typecls<float>() { return Typed<float>::cls(); }
	template <> inline Type* typecls<double>() { return Typed<double>::cls(); }
	template <> inline Type* typecls<string>() { return Typed<string>::cls(); }

#ifndef OBJECT_EXPORT
	extern template class __declspec(dllimport) Typed<bool>;
	extern template class __declspec(dllimport) Typed<int>;
	extern template class __declspec(dllimport) Typed<unsigned int>;
	extern template class __declspec(dllimport) Typed<float>;
	extern template class __declspec(dllimport) Typed<double>;
	extern template class __declspec(dllimport) Typed<string>;

	extern template class __declspec(dllimport) Typed<Array<Object>>;
#endif
}

#endif // MK_TYPED_INCLUDED
