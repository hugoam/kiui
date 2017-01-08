#ifndef MK_DVALUEEDIT_H
#define MK_DVALUEEDIT_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
#include <Object/Reflect/mkEcho.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>
#include <Ui/Widget/mkValue.h>
#include <Ui/Device/mkStack.h>

#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT DValueEdit : public HashDispatch<DValueEdit, Device&, unique_ptr<DValue>>
	{};

	class MK_UI_EXPORT DValueDisplay : public HashDispatch<DValueDisplay, Device&, unique_ptr<DValue>>
	{};

	MK_UI_EXPORT void declareDValueEdit();
	MK_UI_EXPORT void declareDValueDisplay();

	class MK_UI_EXPORT DValue : public Device
	{
	public:
		typedef std::function<void(Lref&)> OnChange;

	public:
		DValue(Device& parent, Lref& lref, OnChange onChange = nullptr);
		DValue(Device& parent, Lref&& lref, OnChange onChange = nullptr);
		DValue(Device& parent, DeviceType& type);
		DValue(Device& parent, Lref& lref, DeviceType& type);
		DValue(Device& parent, Object& object, Type& type, DeviceType& deviceType);

		Lref& value() { return m_value; }

		virtual void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DValue", Device::cls()); return ty; }

	protected:
		Lref m_instance;
		Lref& m_value;

		OnChange m_onChange;
	};

	class MK_UI_EXPORT DEmpty: public DValue
	{
	public:
		DEmpty(Device& parent);

		static DeviceType& cls() { static DeviceType ty("DEmpty", Device::cls()); return ty; }
	};

	class MK_UI_EXPORT DNone : public DValue
	{
	public:
		DNone(Device& parent);

		static DeviceType& cls() { static DeviceType ty("DNone", Device::cls()); return ty; }
	};

	class MK_UI_EXPORT DEnum : public DValue
	{
	public:
		DEnum(Device& parent, Lref& lref, bool edit = false);

		void set(const string& value);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DEnum", DValue::cls()); return ty; }
	};

	class MK_UI_EXPORT DLink : public DValue
	{
	public:
		DLink(Device& parent, Lref& lref, bool edit = false);

		void reqPick();
		void endPick(Object& object);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DLink", DValue::cls()); return ty; }

	protected:
		Hook* m_linkHook;
	};

	class MK_UI_EXPORT DElement : public Device
	{
	public:
		DElement(Device& parent, Stack& stack, Lref lref);

		void remove();

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DElement", Device::cls()); return ty; }
	};

	class MK_UI_EXPORT DSequence : public DValue
	{
	public:
		DSequence(Device& parent, Lref& lref, bool edit = false);

		void reqAdd();
		void endAdd(Object& object);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DSequence", DValue::cls()); return ty; }
	};
}

#endif // MK_DVALUEEDIT_H
