//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkTyped.h>

#include <Object/Store/mkArray.h>
#include <Object/Store/mkStoreObserver.h>

namespace mk
{
	template class __declspec(dllexport) Typed<bool>;
	template class __declspec(dllexport) Typed<int>;
	template class __declspec(dllexport) Typed<unsigned int>;
	template class __declspec(dllexport) Typed<float>;
	template class __declspec(dllexport) Typed<double>;
	template class __declspec(dllexport) Typed<string>;

	template class __declspec(dllexport) Typed<Array<Object>>;
	template class __declspec(dllexport) StoreObserver<Object>;
}
