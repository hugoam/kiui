//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Image.h>

#include <toyui/UiWindow.h>
#include <toyobj/Util/Image.h>

namespace toy
{
	Figure::Figure(Wedge& parent, Image256& source)
		: Widget(parent, cls()) //, [this](Lref& value) { this->updateImage(); })
		, m_source(source)
		, m_image(nullptr)
	{
		this->updateImage();
	}

	void Figure::destroyed()
	{
		this->clearImage();
	}

	void Figure::updateImage()
	{
		this->clearImage();

		std::vector<uint8_t> data = m_source.read();
		m_image = &this->uiWindow().createImage("Figure", m_source.width, m_source.height, &data[0], false);

		m_frame->setIcon(m_image);
	}

	void Figure::clearImage()
	{
		if(m_image)
			this->uiWindow().removeImage(*m_image);
	}
}
