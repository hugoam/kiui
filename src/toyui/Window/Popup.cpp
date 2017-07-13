//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Popup.h>

#include <toyui/Frame/Layer.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Popup::Popup(Wedge& parent, Callback onClose, bool open, Type& type)
		: Wedge(parent, type, LAYER)
		, m_onClose(onClose)
	{
		DimFloat local = m_parent->frame().localPosition(this->rootSheet().mouse().lastPos());
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
		this->frame().as<Layer>().moveToTop();
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
