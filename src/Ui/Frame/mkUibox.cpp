//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkUibox.h>

namespace mk
{
	Uibox::Uibox(LayoutStyle* style)
		: d_position(0.f, 0.f)
		, d_size(0.f, 0.f)
		, d_span(style->d_span)
		, d_sizing(style->d_sizing)
		, d_opacity(style->d_opacity)
		, d_style(style)
	{}

	Uibox::Uibox()
		: d_position(0.f, 0.f)
		, d_size(0.f, 0.f)
		, d_span(0.f, 0.f)
		, d_sizing(SHRINK, SHRINK)
		, d_opacity(VOID)
		, d_style(nullptr)
	{}

	Uibox::~Uibox()
	{}

	void Uibox::setStyle(LayoutStyle* style)
	{
		d_style = style;
		//d_size = style->d_size; // Caused a bug because we don't set the size through setSize, so the layout isn't updated
		d_span = style->d_span;
		d_sizing = style->d_sizing;
		d_opacity = style->d_opacity;
		d_style = style;
	}
}
