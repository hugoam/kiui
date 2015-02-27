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
	struct DispatchRef<T*> { static inline T* ref(Lref& ref) { return ref->as<T>(); } };

	template <class D, class C, class R>
	class HashDispatch
	{
	public:
		static void branch(Type* type, const std::function<R (C, Lref&)>& func)
		{
			if(mDispatcher.size() < type->id()+1)
				mDispatcher.resize(type->id()+51);
				
			mDispatcher[type->id()] = func;
		}

		static R dispatch(C context, Lref& ref)
		{
			return mDispatcher[ref->type()->id()](context, ref);
		}

		static R dispatchup(C context, Lref& ref)
		{
			// Slower dispatch, but we check the bases for relevant entries in the dispatcher
			Type* type = ref->type();
			for(; type->base() != 0; type = type->base())
				if(check(type))
					break;
			return mDispatcher[type->id()](context, ref);
		}

		static bool check(Type* type)
		{
			if(type->id() > mDispatcher.size())
				return false;
			return (bool) mDispatcher[type->id()];
		}

		static bool checkup(Type* type)
		{
			while(type->base() != 0)
			{
				if(check(type))
					return true;
				type = type->base();
			}
			return check(type);
		}

		typedef C C;
		typedef R R;

	protected:
		static std::vector<std::function<R (C, Lref&)>> mDispatcher;
	};

	template <class D, class C, class R>
	typename std::vector<std::function<R (C, Lref&)>> HashDispatch<D,C,R>::mDispatcher = std::vector<std::function<R (C, Lref&)>>();


	template <class D, class T, typename D::R(*f)(typename D::C, Lref&, T)>
	class Dispatch
	{
	public:
		Dispatch()
		{
			D::branch(typecls<typename BareType<T>::type>(), &dispatch); // @todo Here for Object types it fetches from Typed<T> which could lead to incorrect behavior
		}

		static typename D::R dispatch(typename D::C context, Lref& lref)
		{
			return f(context, lref, DispatchRef<typename UnrefType<T>::type>::ref(lref));
		}

	protected:
		static Dispatch<D,T,f> branch;
	};

	template <class D, class T, typename D::R(*f)(typename D::C, Lref&, T)>
	typename Dispatch<D,T,f> Dispatch<D,T,f>::branch = Dispatch<D,T,f>();
}

#endif // mkDISPATCH_H_INCLUDED
