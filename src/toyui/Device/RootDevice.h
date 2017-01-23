//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_ROOTFORM_H
#define TOY_ROOTFORM_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyobj/Util/Updatable.h>
#include <toyobj/Util/Unique.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Device/DeviceMapper.h>

#include <map>

namespace toy
{
	class TOY_UI_EXPORT RootDevice : public Device
	{
	public:
		RootDevice(UiWindow& window, Sheet& rootSheet);
		~RootDevice();

		UiWindow& uiWindow() { return m_window; }
		Sheet& rootSheet() { return m_rootSheet; }

		User& user() { return *m_user; }

		size_t lastTick() { return m_lastTick; }

		void nextFrame(size_t tick, size_t delta);

		void declareDefaultMappings();

		void insertionSheet(Sheet& sheet);

		static DeviceType& cls() { static DeviceType ty("RootDevice", Device::cls()); return ty; }

	protected:
		UiWindow& m_window;
		Sheet& m_rootSheet;

		User* m_user;
		size_t m_lastTick;
	};
}

#endif // TOY_FORM_H
