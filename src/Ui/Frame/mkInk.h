//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INK_H
#define MK_INK_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Style/mkStyle.h>

namespace mk
{
	struct TextGlyph
	{
		const char* position;
		BoxFloat rect;
	};

	struct TextRow
	{
		const char* start;
		const char* end;
		BoxFloat rect;
		BoxFloat selected;

		std::vector<TextGlyph> glyphs;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() {}

#ifdef KIUI_DRAW_CACHE
		virtual void createCache(void*& cache, size_t size) = 0;
		virtual void drawCache(void* cache, float x, float y) = 0;
		virtual void destroyCache(void* cache) = 0;

		virtual void beginUpdate(void* cache) = 0;
		virtual void endUpdate(void* cache) = 0;
#else
		virtual void beginUpdate(float x, float y) = 0;
		virtual void endUpdate() = 0;
#endif

		virtual void clipRect(BoxFloat& rect) = 0;
		virtual void unclipRect() = 0;

		virtual void clipFrame(BoxFloat& rect, BoxFloat& corners) = 0;
		virtual void clipShape() = 0;
		virtual void unclipShape() = 0;

		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) = 0;
		virtual void pathRect(BoxFloat& rect, BoxFloat& corners, float border) = 0;

		virtual void fill(InkStyle& skin, BoxFloat& rect) = 0;
		virtual void stroke(InkStyle& skin) = 0;

		virtual void drawShadow(BoxFloat& rect, BoxFloat& corner, Shadow& shadows) = 0;
		virtual void drawRect(BoxFloat& rect, BoxFloat& corners, InkStyle& skin) = 0;
		virtual void drawRectClipped(BoxFloat& rect, BoxFloat& corners, InkStyle& skin, BoxFloat& clipRect, BoxFloat& clipCorners) = 0;
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin) = 0;

		virtual void drawImage(const Image& image, BoxFloat& rect) = 0;
		virtual void drawImageStretch(const Image& image, BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f) = 0;

		virtual void fillText(const string& text, BoxFloat& paddedRect, InkStyle& skin, TextRow& row) = 0;
		virtual void breakText(const string& text, BoxFloat& paddedRect, InkStyle& skin, std::vector<TextRow>& rows) = 0;

		virtual float textSize(const string& text, Dimension dim, InkStyle& skin) = 0;
	};

	class MK_UI_EXPORT InkWindow : public Object
	{
	public:
		InkWindow(UiWindow& uiWindow, unique_ptr<Renderer> renderer);

		void addImage(const string& image, int width, int height);

		void draw();

		InkTarget& screenTarget() { return *m_screenTarget; }
		//virtual InkTarget* spaceTarget(Camera* camera, int width, int height) = 0;

		static Type& cls() { static Type ty; return ty; }

	protected:
		UiWindow& m_uiWindow;
		unique_ptr<Renderer> m_renderer;
		unique_ptr<InkTarget> m_screenTarget;
		std::vector<Image> m_images;
	};

	class MK_UI_EXPORT InkTarget : public Object
	{
	public:
		InkTarget(Renderer& renderer, size_t layers);

		Renderer& renderer() { return d_renderer; }
		size_t ztop() { return d_layers; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		Renderer& d_renderer;
		size_t d_layers;
		Layer* d_rootLayer;
	};
	
	class MK_UI_EXPORT InkLayer : public Object
	{
	public:
		InkLayer(Layer& layer, InkTarget& target, size_t z);
		virtual ~InkLayer() {}

		Layer& layer() { return m_layer; }
		InkTarget& target() { return m_target; }
		size_t z() { return m_z; }
		size_t index() { return m_index; }
		void setIndex(size_t index, size_t z) { m_index = index; m_z = z; this->move(index, z); }

		void show();
		void hide();

		void move(size_t index, size_t z);

		void draw();
		void drawImage(Frame& frame);
		void drawText(Frame& frame);

		static Type& cls() { static Type ty; return ty; }

	protected:
		Layer& m_layer;
		Frame& m_frame;
		InkTarget& m_target;
		size_t m_z;
		size_t m_index;
	};

	class MK_UI_EXPORT Inkbox : public NonCopy
	{
	public:
		Inkbox(Frame& frame);
		~Inkbox();

		Frame& frame() { return m_frame; }
		bool visible() { return m_visible; }
		BoxFloat& corners() { return m_frame.inkstyle().cornerRadius(); }
		size_t selectStart() { return m_selectFirst < m_selectSecond ? m_selectFirst : m_selectSecond; }
		size_t selectEnd() { return m_selectSecond > m_selectFirst ? m_selectSecond : m_selectFirst; }

		Renderer& renderer() { return m_render; }

		inline float left() { return floor(m_frame.inkstyle().margin().x0()); }
		inline float top() { return floor(m_frame.inkstyle().margin().y0()); }
		inline float width() { return floor(m_frame.width() - m_frame.inkstyle().margin().x0() - m_frame.inkstyle().margin().x1()); }
		inline float height() { return floor(m_frame.height() - m_frame.inkstyle().margin().y0() - m_frame.inkstyle().margin().y1()); }

		inline float cleft() { return floor(m_frame.dclippos(DIM_X) + m_frame.inkstyle().margin().x0()); }
		inline float ctop() { return floor(m_frame.dclippos(DIM_Y) + m_frame.inkstyle().margin().y0()); }
		inline float cwidth() { return floor(m_frame.dclipsize(DIM_X) - m_frame.inkstyle().margin().x0() - m_frame.inkstyle().margin().x1()); }
		inline float cheight() { return floor(m_frame.dclipsize(DIM_Y) - m_frame.inkstyle().margin().y0() - m_frame.inkstyle().margin().y1()); }

		inline float pleft() { return floor(m_frame.inkstyle().padding().x0()); }
		inline float ptop() { return floor(m_frame.inkstyle().padding().y0()); }
		inline float pwidth() { return floor(m_frame.width() - m_frame.inkstyle().padding().x0() - m_frame.inkstyle().padding().x1()); }
		inline float pheight() { return floor(m_frame.height() - m_frame.inkstyle().padding().y0() - m_frame.inkstyle().padding().y1()); }

		float contentWidth() { return contentSize(DIM_X); }
		float contentHeight() { return contentSize(DIM_Y); }

		inline float contentLeft()
		{
			float left = pleft();
			if(skin().align()[DIM_X] == CENTER)
				left = pleft() + pwidth() / 2.f - contentWidth() / 2.f;
			else if(skin().align()[DIM_X] == RIGHT)
				left = pleft() + pwidth() - contentWidth();
			return left;
		}

		inline float contentTop()
		{
			float top = ptop();
			if(skin().align()[DIM_Y] == CENTER)
				top = ptop() + pheight() / 2.f - contentHeight() / 2.f;
			else if(skin().align()[DIM_Y] == RIGHT)
				top = ptop() + pheight() - contentHeight();
			return top;
		}

		inline InkStyle& skin() { return m_frame.inkstyle(); }

		void show();
		void hide();

		void drawText();
		void drawImage();

		void redrawText();
		void redrawImage();

		void drawSkinImage(ImageSkin::Section section, int left, int top, int width, int height);

		void updateContent();
		void updateStyle();
		void updateFrame();

		void selectCaret(size_t index) { m_selectFirst = index; m_selectSecond = index; this->updateSelection(); }
		void selectFirst(size_t start) { m_selectFirst = start; m_selectSecond = start; this->updateSelection(); }
		void selectSecond(size_t end) { m_selectSecond = end; this->updateSelection(); }

		void updateSelection();

		float contentSize(Dimension dim);

		size_t caretIndex(float x, float y);
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight);

	protected:
		Frame& m_frame;
		bool m_visible;

		size_t m_selectFirst;
		size_t m_selectSecond;

		bool m_textUpdate;
		bool m_imageUpdate;

		bool m_moved;

		Image* m_image;
		Image* m_overlay;
		Image* m_tile;
		Image* m_skin;

		Renderer& m_render;

		std::vector<TextRow> m_textRows;

#ifdef KIUI_DRAW_CACHE
		void* m_imageCache;
		void* m_textCache;
#endif

	public:
		static bool sDebugDraw;
		static int sDebugBatch;
	};
}

#endif
