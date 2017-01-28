//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
#ifndef TOY_DVALUEEDIT_H
#define TOY_DVALUEEDIT_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/Store/Array.h>
#include <toyobj/Reflect/Echo.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Widget/Value.h>
#include <toyui/Device/Stack.h>

#include <toyobj/Util/Dispatch.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DValueEdit : public HashDispatch<DValueEdit, Device&, unique_ptr<DValue>>
	{
	public:
		static string name() { return "DValueEdit"; };
	};

	class TOY_UI_EXPORT DValueDisplay : public HashDispatch<DValueDisplay, Device&, unique_ptr<DValue>>
	{
	public:
		static string name() { return "DValueDisplay"; };
	};

	TOY_UI_EXPORT void declareDValueEdit();
	TOY_UI_EXPORT void declareDValueDisplay();

	class TOY_UI_EXPORT DValue : public Device
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

	class TOY_UI_EXPORT DEmpty: public DValue
	{
	public:
		DEmpty(Device& parent);

		static DeviceType& cls() { static DeviceType ty("DEmpty", Device::cls()); return ty; }
	};

	class TOY_UI_EXPORT DNone : public DValue
	{
	public:
		DNone(Device& parent);

		static DeviceType& cls() { static DeviceType ty("DNone", Device::cls()); return ty; }
	};

	class TOY_UI_EXPORT DEnum : public DValue
	{
	public:
		DEnum(Device& parent, Lref& lref, bool edit = false);

		void set(const string& value);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DEnum", DValue::cls()); return ty; }
	};

	class TOY_UI_EXPORT DLink : public DValue
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

	class TOY_UI_EXPORT DElement : public Device
	{
	public:
		DElement(Device& parent, Stack& stack, Lref lref);

		void remove();

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DElement", Device::cls()); return ty; }
	};

	class TOY_UI_EXPORT DSequence : public DValue
	{
	public:
		DSequence(Device& parent, Lref& lref, bool edit = false);

		void reqAdd();
		void endAdd(Object& object);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DSequence", DValue::cls()); return ty; }
	};
}

#endif // TOY_DVALUEEDIT_H
