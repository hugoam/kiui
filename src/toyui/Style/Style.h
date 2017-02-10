//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_STYLE_H
#define TOY_STYLE_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/Indexer.h>
#include <toyobj/Util/Colour.h>
#include <toyobj/Util/NonCopy.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Style/ImageSkin.h>

/* Standards */
#include <array>
#include <map>

namespace toy
{
	class _I_ TOY_UI_EXPORT Shadow : public IdStruct
	{
	public:
		Shadow(float xpos, float ypos, float blur, float spread, Colour colour = Colour::Black)
			: IdStruct(cls())
			, d_xpos(xpos), d_ypos(ypos), d_blur(blur), d_spread(spread), d_radius(spread + blur), d_colour(colour), d_null(false)
		{}

		Shadow()
			: IdStruct(cls())
			, d_null(true)
		{}

		float d_xpos;
		float d_ypos;
		float d_blur;
		float d_spread;
		float d_radius;
		Colour d_colour;
		bool d_null;

		static Type& cls() { static Type ty(INDEXED); return ty; }
	};

	template <class T>
	class StyleAttr
	{
	public:
		StyleAttr() : val(), set(false) {}
		StyleAttr(const T& v) : val(v), set(false) {}
		StyleAttr(const StyleAttr& other) : val(other.val), set(other.set) {}

		operator const T&() const { return val; }
		StyleAttr& operator=(const T& v) { val = v; set = true; return *this; }
		StyleAttr& operator=(const StyleAttr& other) { val = other.val; set = other.set; return *this; }

		void copy(const StyleAttr& other, bool inherit) { if(set && (inherit || !other.set)) return; val = other.val; if(!inherit) set = other.set; }

		T val;
		bool set;
	};

	class _I_ TOY_UI_EXPORT LayoutStyle : public IdStruct
	{
	public:
		LayoutStyle()
			: IdStruct(cls())
			, d_layout(DimLayout(AUTOLAYOUT, AUTOLAYOUT)), d_flow(FLOW), d_clipping(NOCLIP), d_opacity(CLEAR), d_space(AUTO), d_layoutDim(DIM_Y), d_align(DimAlign(LEFT, LEFT))
			, d_span(DimFloat(1.f, 1.f)), d_pivot(DimPivot(FORWARD, FORWARD)), d_updated(0)
		{}

		LayoutStyle(const LayoutStyle& other)
			: IdStruct(cls())
		{
			this->copy(other);
		}

		LayoutStyle& operator=(const LayoutStyle&) = default;

		void copy(const LayoutStyle& other, bool inherit = false)
		{
			d_layout.copy(other.d_layout, inherit);
			d_flow.copy(other.d_flow, inherit);
			d_clipping.copy(other.d_clipping, inherit);
			d_opacity.copy(other.d_opacity, inherit);
			d_space.copy(other.d_space, inherit);
			d_layoutDim.copy(other.d_layoutDim, inherit);
			d_align.copy(other.d_align, inherit);
			d_span.copy(other.d_span, inherit);
			d_size.copy(other.d_size, inherit);
			d_padding.copy(other.d_padding, inherit);
			d_margin.copy(other.d_margin, inherit);
			d_spacing.copy(other.d_spacing, inherit);
			d_pivot.copy(other.d_pivot, inherit);
			d_sizing.copy(other.d_sizing, inherit);
		}

		_A_ DimLayout layout() const { return d_layout.val; }
		_A_ Flow flow() const { return d_flow.val; }
		_A_ Clipping clipping() const { return d_clipping.val; }
		_A_ Opacity opacity() const { return d_opacity.val; }
		_A_ Space div() const { return d_space.val; }
		_A_ Dimension layoutDim() const { return d_layoutDim.val; }
		_A_ DimAlign& align() { return d_align.val; }
		_A_ DimFloat& span() { return d_span.val; }
		_A_ DimFloat& size() { return d_size.val; }
		_A_ BoxFloat& padding() { return d_padding.val; }
		_A_ DimFloat& margin() { return d_margin.val; }
		_A_ DimFloat& spacing() { return d_spacing.val; }
		_A_ DimSizing& sizing() { return d_sizing.val; }
		_A_ DimPivot& pivot() { return d_pivot.val; }

		StyleAttr<DimLayout> d_layout;
		StyleAttr<Flow> d_flow;
		StyleAttr<Clipping> d_clipping;
		StyleAttr<Opacity> d_opacity;
		StyleAttr<Space> d_space;
		StyleAttr<Dimension> d_layoutDim;
		StyleAttr<DimAlign> d_align;
		StyleAttr<DimFloat> d_span;
		StyleAttr<DimFloat> d_size;
		StyleAttr<BoxFloat> d_padding;
		StyleAttr<DimFloat> d_margin;
		StyleAttr<DimFloat> d_spacing;
		StyleAttr<DimSizing> d_sizing;
		StyleAttr<DimPivot> d_pivot;

		_A_ _M_ size_t d_updated;

		static Type& cls() { static Type ty(INDEXED); return ty; }
	};

	class _I_ TOY_UI_EXPORT InkStyle : public IdStruct
	{
	public:
		_C_ InkStyle(const string& name)
			: IdStruct(cls())
			, m_name(name)
			, m_empty(true), m_backgroundColour(Colour::Transparent), m_borderColour(Colour::Transparent), m_imageColour(Colour::Transparent), m_textColour(Colour::Transparent)
			, m_textFont("dejavu"), m_textSize(14.f), m_textBreak(true), m_textWrap(false)
			, m_borderWidth(0.f), m_cornerRadius(), m_weakCorners(false)
			, m_padding(0.f), m_margin(0.f)
			, m_align(DimAlign(LEFT, LEFT)), m_linearGradient(DimFloat(0.f, 0.f)), m_linearGradientDim(DIM_Y)
			, m_image(nullptr), m_overlay(nullptr), m_tile(nullptr)
		{}

		InkStyle(const InkStyle& other)
			: IdStruct(cls())
			, m_name(other.m_name)
		{
			this->copy(other);
		}

		InkStyle& operator=(const InkStyle&) = default;

		void copy(const InkStyle& other, bool inherit = false)
		{
			m_backgroundColour.copy(other.m_backgroundColour, inherit);
			m_borderColour.copy(other.m_borderColour, inherit);
			m_imageColour.copy(other.m_imageColour, inherit);
			m_textColour.copy(other.m_textColour, inherit);
			m_textFont.copy(other.m_textFont, inherit);
			m_textSize.copy(other.m_textSize, inherit);
			m_textBreak.copy(other.m_textBreak, inherit);
			m_textWrap.copy(other.m_textWrap, inherit);
			m_borderWidth.copy(other.m_borderWidth, inherit);
			m_cornerRadius.copy(other.m_cornerRadius, inherit);
			m_weakCorners.copy(other.m_weakCorners, inherit);
			m_padding.copy(other.m_padding, inherit);
			m_margin.copy(other.m_margin, inherit);
			m_align.copy(other.m_align, inherit);
			m_linearGradient.copy(other.m_linearGradient, inherit);
			m_linearGradientDim.copy(other.m_linearGradientDim, inherit);
			m_image.copy(other.m_image, inherit);
			m_overlay.copy(other.m_overlay, inherit);
			m_tile.copy(other.m_tile, inherit);
			m_imageSkin.copy(other.m_imageSkin, inherit);
			m_shadow.copy(other.m_shadow, inherit);
		}

		void setEmpty(bool empty) { m_empty = empty; }

		_A_ const string& name() const { return m_name; }
		_A_ bool empty() const { return m_empty; }
		_A_ Colour& backgroundColour() { return m_backgroundColour.val; }
		_A_ Colour& borderColour() { return m_borderColour.val; }
		_A_ Colour& imageColour() { return m_imageColour.val; }
		_A_ Colour& textColour() { return m_textColour.val; }
		_A_ const string& textFont() { return m_textFont.val; }
		_A_ float& textSize() { return m_textSize.val; }
		_A_ bool& textBreak() { return m_textBreak.val; }
		_A_ bool& textWrap() { return m_textWrap.val; }
		_A_ BoxFloat& borderWidth() { return m_borderWidth.val; }
		_A_ BoxFloat& cornerRadius() { return m_cornerRadius.val; }
		_A_ bool& weakCorners() { return m_weakCorners.val; }
		_A_ BoxFloat& padding() { return m_padding.val; }
		_A_ BoxFloat& margin() { return m_margin.val; }
		_A_ DimAlign& align() { return m_align.val; }
		_A_ DimFloat& linearGradient() { return m_linearGradient.val; }
		_A_ Dimension& linearGradientDim() { return m_linearGradientDim.val; }
		_A_ Image* image() { return m_image.val; }
		_A_ Image* overlay() { return m_overlay.val; }
		_A_ Image* tile() { return m_tile.val; }
		_A_ ImageSkin& imageSkin() { return m_imageSkin.val; }
		_A_ Shadow& shadow() { return m_shadow.val; }

		string m_name;
		bool m_empty;
		StyleAttr<Colour> m_backgroundColour;
		StyleAttr<Colour> m_borderColour;
		StyleAttr<Colour> m_imageColour;
		StyleAttr<Colour> m_textColour;
		StyleAttr<string> m_textFont;
		StyleAttr<float> m_textSize;
		StyleAttr<bool> m_textBreak;
		StyleAttr<bool> m_textWrap;
		StyleAttr<BoxFloat> m_borderWidth;
		StyleAttr<BoxFloat> m_cornerRadius;
		StyleAttr<bool> m_weakCorners;
		StyleAttr<BoxFloat> m_padding;
		StyleAttr<BoxFloat> m_margin;
		StyleAttr<DimAlign> m_align;
		StyleAttr<DimFloat> m_linearGradient;
		StyleAttr<Dimension> m_linearGradientDim;
		StyleAttr<Image*> m_image;
		StyleAttr<Image*> m_overlay;
		StyleAttr<Image*> m_tile;
		StyleAttr<ImageSkin> m_imageSkin;
		StyleAttr<Shadow> m_shadow;

		static Type& cls() { static Type ty(INDEXED); return ty; }
	};

	typedef std::vector<Style*> StyleVector;

	class TOY_UI_EXPORT SubSkin
	{
	public:
		SubSkin(WidgetState state, const string& name) : m_state(state), m_skin(name) {}
		SubSkin(WidgetState state, const InkStyle& skin) : m_state(state), m_skin(skin) {}

		WidgetState m_state;
		InkStyle m_skin;
	};

	typedef std::vector<SubSkin> StyleTable;

	class _I_ TOY_UI_EXPORT Style : public IdStruct, public NonCopy
	{
	public:
		Style(Type& type, Style* base);
		Style(const string& name);
		~Style();

		_A_ const string& name() { return m_name.empty() ? m_styleType->name() : m_name; }
		_A_ Style* base() { return m_base; }
		_A_ LayoutStyle& layout() { return m_layout; }
		_A_ InkStyle& skin() { return m_skin; }
		_A_ _M_ size_t updated() { return m_updated; }

		void markUpdate() { ++m_updated; }
		void setUpdated(size_t update) { m_updated = update; }

		Type* styleType() { return m_styleType; }
		const StyleTable& subskins() { return m_subskins; }
		
		void reset();
		InkStyle& copy(WidgetState state, InkStyle& original, bool inherit);

		InkStyle& subskin(WidgetState state);
		InkStyle& decline(WidgetState state);

		void rebase(Style& base);
		void rebaseSkins(Style& base);

		void inherit();
		void inheritLayout(Style& base);
		void inheritSkins(Style& base);
		void copySkins(Style& base);

		static Type& cls() { static Type ty(INDEXED); return ty; }

	protected:
		Type* m_styleType;
		Style* m_base;
		Style* m_baseSkin;
		string m_name;
		LayoutStyle m_layout;
		InkStyle m_skin;
		StyleTable m_subskins;
		size_t m_updated;
	};

	class TOY_UI_EXPORT StyleType : public Type, public Style
	{
	public:
		StyleType(const string& name);
		StyleType(const string& name, StyleType& base);

		using Type::name;
	};
}

#endif // TOY_STYLE_H
