//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DISPATCH_H_INCLUDED
#define MK_DISPATCH_H_INCLUDED

/* mk */
#include <Object/mkRef.h>
#include <Object/mkObject.h>

/* Standard headers */
#include <map>
#include <vector>
#include <unordered_map>
#include <functional>

namespace mk
{
	template <class T>
	struct DispatchRef { static inline T& ref(Lref& ref) { return ref->any<T>()->ref(); } };

	template <class T>
	struct DispatchRef<T*> { static inline T* ref(Lref& ref) { return &ref->as<T>(); } };

	template <class D, class C, class R>
	class HashDispatch
	{
	public:
		static void branch(Type& type, const std::function<R (C, Lref&)>& func)
		{
			m_dispatcher[type.id()] = func;
		}

		static R dispatch(C context, Lref& ref)
		{
			return m_dispatcher[ref->type().id()](context, ref);
		}

		static bool check(Lref& ref)
		{
			return m_dispatcher[ref->type().id()] != nullptr;
		}

		typedef C Context;
		typedef R Return;

	protected:
		static std::vector<std::function<R (C, Lref&)>> m_dispatcher;
	};

	template <class D, class C, class R>
	typename std::vector<std::function<R (C, Lref&)>> HashDispatch<D,C,R>::m_dispatcher = std::vector<std::function<R (C, Lref&)>>(10000);


	template <class D, class T, typename D::Return(*f)(typename D::Context, Lref&, T)>
	class Dispatch
	{
	public:
		Dispatch()
		{
			D::branch(typecls<typename BareType<T>::type>(), &dispatch);
		}

		static typename D::Return dispatch(typename D::Context context, Lref& lref)
		{
			return f(context, lref, DispatchRef<typename UnrefType<T>::type>::ref(lref));
		}

	protected:
		static Dispatch<D,T,f> branch;
	};

	template <class D, class T, typename D::Return(*f)(typename D::Context, Lref&, T)>
	Dispatch<D,T,f> Dispatch<D,T,f>::branch = Dispatch<D,T,f>();

	template <class D, typename bool(*mask)(Type&), typename D::Return(*f)(typename D::Context, Lref&)>
	class MaskDispatch
	{
	public:
		MaskDispatch()
		{
			for(IdObject* type : Type::cls().indexer().objects())
				if(type && mask(type->as<Type>()))
					D::branch(type->as<Type>(), &dispatch);
		}

		static typename D::Return dispatch(typename D::Context context, Lref& lref)
		{
			return f(context, lref);
		}

	protected:
		static MaskDispatch<D, mask, f> branch;
	};

	template <class D, typename bool(*mask)(Type&), typename D::Return(*f)(typename D::Context, Lref&)>
	MaskDispatch<D, mask, f> MaskDispatch<D, mask, f>::branch;
}

#endif // mkDISPATCH_H_INCLUDED
