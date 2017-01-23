#ifndef TOY_DSTRUCTURE_H
#define TOY_DSTRUCTURE_H

/* EditorApp */
#include <toyobj/Iterable/StoreObserver.h>
#include <toyobj/Reflect/Echo.h>
#include <toyui/Forward.h>
#include <toyui/Device/Stack.h>

/* Standard */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DStructureNode : public Device
	{
	public:
		DStructureNode(Device& parent, Object& object, Type& type);

		Echobject& echobject() { return *m_object; }

		static DeviceType& cls() { static DeviceType ty("DStructureNode", Device::cls()); return ty; }

	protected:
		unique_ptr<Echobject> m_object;
	};

	class TOY_UI_EXPORT DStructure : public Device
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
#endif // TOY_DSTRUCTURE_H
