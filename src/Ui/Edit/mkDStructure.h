#ifndef MK_DSTRUCTURE_H
#define MK_DSTRUCTURE_H

/* EditorApp */
#include <Object/Iterable/mkStoreObserver.h>
#include <Object/Reflect/mkEcho.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkStack.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT DStructureNode : public Device
	{
	public:
		DStructureNode(Device& parent, Object& object, Type& type);

		Echobject& echobject() { return *m_object; }

		static DeviceType& cls() { static DeviceType ty("DStructureNode", Device::cls()); return ty; }

	protected:
		unique_ptr<Echobject> m_object;
	};

	class MK_UI_EXPORT DStructure : public Device
	{
	public:
		DStructure(Device& parent);
		~DStructure();

		void setRoot(Object& object, Type& type);

		static DeviceType& cls() { static DeviceType ty("DStructure", Device::cls()); return ty; }

	public:
		DStructureNode* m_root;
	};
}
#endif // MK_DSTRUCTURE_H
