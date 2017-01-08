#ifndef MK_DLIBRARY_H
#define MK_DLIBRARY_H

/* EditorApp */
#include <Ui/mkUiConfig.h>
#include <Object/Iterable/mkStoreObserver.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>
#include <Ui/Device/mkStack.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT DPicker
	{
	public:

	};

	class MK_UI_EXPORT DIndexer : public Device
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
#endif // MK_DLIBRARY_H
