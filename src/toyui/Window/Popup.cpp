//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Popup.h>

#include <toyui/Frame/Layer.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Popup::Popup(const Params& params, const Callback& onClose, bool open)
		: Wedge({ params, &cls<Popup>(), LAYER })
		, m_onClose(onClose)
	{
		DimFloat local = m_parent->frame().localPosition(this->rootSheet().m_mouse.m_lastPos);
		m_frame->setPosition(local);

		open ? this->open(true) : this->hide();
	}

	bool Popup::leftClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->close();
		return true;
	}

	bool Popup::rightClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->close();
		return true;
	}

	void Popup::open(bool modal)
	{
		this->show();
		as<Layer>(this->frame()).moveToTop();
		if(modal)
			this->takeControl(CM_MODAL);
	}

	void Popup::close()
	{
		this->hide();
		this->yieldControl();
		if(m_onClose)
			m_onClose(*this);
	}

}
