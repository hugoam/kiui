//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
#ifndef TOY_DLIBRARY_H
#define TOY_DLIBRARY_H

/* EditorApp */
#include <toyui/Config.h>
#include <toyobj/Iterable/StoreObserver.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Device/Stack.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DPicker
	{
	public:

	};

	class TOY_UI_EXPORT DIndexer : public Device
	{
	public:
		DIndexer(Device& parent, Indexer& indexer, Store<Object>& selection);
		~DIndexer();

		Type& elementType() { return m_elementType; }
		const string& name() { return m_name; }
		Stack& picker() { return m_picker; }

		static DeviceType& cls() { static DeviceType ty("DIndexer", Device::cls()); return ty; }

	public:
		Type& m_elementType;
		string m_name;
		Stack& m_picker;
	};
}
#endif // TOY_DLIBRARY_H
