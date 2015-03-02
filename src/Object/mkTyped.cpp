//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkTyped.h>

#include <Object/Store/mkArray.h>
#include <Object/Store/mkStoreObserver.h>

namespace mk
{
	template class MK_OBJECT_EXPORT Typed<bool>;
	template class MK_OBJECT_EXPORT Typed<int>;
	template class MK_OBJECT_EXPORT Typed<unsigned int>;
	template class MK_OBJECT_EXPORT Typed<float>;
	template class MK_OBJECT_EXPORT Typed<double>;
	template class MK_OBJECT_EXPORT Typed<string>;

	template class MK_OBJECT_EXPORT Typed<std::vector<float>>;
	template class MK_OBJECT_EXPORT Typed<std::vector<string>>;

	template class MK_OBJECT_EXPORT Typed<std::vector<Type*>>;
	template class MK_OBJECT_EXPORT Typed<std::vector<Object*>>;

	template class MK_OBJECT_EXPORT Typed<Array<Object>>;
	template class MK_OBJECT_EXPORT StoreObserver<Object>;
}
