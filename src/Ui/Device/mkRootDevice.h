//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ROOTFORM_H
#define MK_ROOTFORM_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkUnique.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>
#include <Ui/Device/mkDeviceMapper.h>

#include <map>

namespace mk
{
	class MK_UI_EXPORT RootDevice : public Device
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

#endif // MK_FORM_H
