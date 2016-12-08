//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_REVERSE_H
#define MK_REVERSE_H

namespace mk
{
	template<typename T> class reverse_adapter
	{
	public:
		reverse_adapter(T& c) : c(c) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;
		//typename T::const_reverse_iterator begin() { return c.rbegin(); }
		//typename T::const_reverse_iterator end() { return c.rend(); }
		typename T::reverse_iterator begin() { return c.rbegin(); }
		typename T::reverse_iterator end() { return c.rend(); }
	private:
		T& c;
	};

	template<typename T> reverse_adapter<T> reverse_adapt(T &c) { return reverse_adapter<T>(c); }

}

#endif // MK_REVERSE_H
