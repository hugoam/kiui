//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DRAWFRAME_H
#define TOY_DRAWFRAME_H

/* toy Front */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Render/Caption.h>
#include <toyui/Render/Stencil.h>

namespace toy
{
	class TOY_UI_EXPORT DrawFrame
	{
	public:
		DrawFrame(Frame& frame);

		DrawFrame(const DrawFrame&) = default;
		DrawFrame& operator=(const DrawFrame&) = default;

		inline Frame& frame() { return *d_frame; }
		inline Stencil& stencil() { return d_stencil; }
		inline Caption& caption() { return d_caption; }

		void setEmpty() { this->setText(""); this->setImage(nullptr); }
		bool empty();

		const string& text() { return m_text; }
		void setText(const string& text);

		Image* image() { return m_image; }
		void setImage(Image* image);

		void setTextLines(size_t lines);

		inline InkStyle& inkstyle() { return *d_inkstyle; }

		void beginDraw(Renderer& renderer, bool force);
		void draw(Renderer& renderer, bool force);
		void endDraw(Renderer& renderer);

		void updateInkstyle(InkStyle& inkstyle);
		void resetInkstyle(InkStyle& inkstyle);

		void updateContentSize();
		void updateFrameSize();
		void updateTextLineBreaks();

		float extentSize(Dimension dim);
		float contentSize(Dimension dim);
		void contentPos(const BoxFloat& paddedRect, const DimFloat& size, Dimension dim, DimFloat& pos);

	protected:
		Frame* d_frame;

		Stencil d_stencil;
		Caption d_caption;
		//Image d_image;

		string m_text;
		size_t m_textLines;
		Image* m_image;

		InkStyle* d_inkstyle;

	public:
		static Renderer* sRenderer;

		static string sDebugPrintFilter;
		static bool sDebugPrint;
		static string sDebugDrawFilter;
		static bool sDebugDrawFrameRect;
		static bool sDebugDrawPaddedRect;
		static bool sDebugDrawContentRect;
		static bool sDebugDrawClipRect;
	};
}

#endif
