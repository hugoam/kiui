//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DRAWFRAME_H
#define MK_DRAWFRAME_H

/* mk Front */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkDim.h>
#include <Ui/Frame/mkCaption.h>
#include <Ui/Frame/mkStencil.h>

namespace mk
{
	class MK_UI_EXPORT InkWindow : public Object
	{
	public:
		InkWindow(UiWindow& uiWindow, unique_ptr<Renderer> renderer);

		void addImage(const string& image, int width, int height);

		static Type& cls() { static Type ty; return ty; }

	protected:
		UiWindow& m_uiWindow;
		unique_ptr<Renderer> m_renderer;
		std::vector<Image> m_images;
	};

	class MK_UI_EXPORT DrawFrame
	{
	public:
		DrawFrame(Frame& frame);

		inline Stencil& stencil() { return d_stencil; }
		inline Caption& caption() { return d_caption; }

		void setEmpty() { this->setText(""); this->setImage(nullptr); }

		const string& text() { return m_text; }
		void setText(const string& text);

		Image* image() { return m_image; }
		void setImage(Image* image);

		inline InkStyle& inkstyle() { return *d_inkstyle; }

		void beginDraw();
		void endDraw();

		void draw(RenderFrame& frame, Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect);

		void updateInkstyle(InkStyle& inkstyle);

		void updateSize();
		void contentSize(Dimension dim, DimFloat& size);
		void contentPos(const BoxFloat& paddedRect, const DimFloat& size, Dimension dim, DimFloat& pos);

	protected:
		Frame& d_frame;

		Stencil d_stencil;
		Caption d_caption;
		//Image d_image;

		string m_text;
		Image* m_image;

		InkStyle* d_inkstyle;

	public:
		static Renderer* sRenderer;
	};
}

#endif
