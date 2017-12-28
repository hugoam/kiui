//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_STYLE_H
#define TOY_STYLE_H

/* toy */
#include <toyobj/Object.h>
#include <toyobj/Indexer.h>
#include <toyobj/Util/Colour.h>
#include <toyobj/Util/NonCopy.h>
#include <toyui/Types.h>
#include <toyui/Frame/Dim.h>
#include <toyui/Style/ImageSkin.h>

/* std */
#include <vector>

namespace toy
{
	struct WidgetStates { int value = 0; int& operator()() { return value; } };

	using CustomRenderer = std::function<bool (const Frame&, Renderer&)>;

	class _refl_ TOY_UI_EXPORT Shadow : public Struct
	{
	public:
		_constr_ Shadow(float xpos, float ypos, float blur, float spread, Colour colour = Colour::AlphaBlack)
			: d_xpos(xpos), d_ypos(ypos), d_blur(blur), d_spread(spread), d_radius(spread + blur), d_colour(colour), d_null(false)
		{}

		_constr_ Shadow()
			: d_null(true)
		{}

		_attr_ _mut_ float d_xpos;
		_attr_ _mut_ float d_ypos;
		_attr_ _mut_ float d_blur;
		_attr_ _mut_ float d_spread;
		_attr_ _mut_ Colour d_colour;

		bool d_null;
		float d_radius;
	};

	class _refl_ TOY_UI_EXPORT Paint : public Struct
	{
	public:
		Paint() : Struct() {}
		Paint(const Colour& colour) : Struct(), m_colour(colour) {}
		Paint(const Colour& first, const Colour& second) : Struct(), m_colour(), m_gradient{ first, second } {}

		bool m_empty;
		float m_width;
		Colour m_colour;
		std::vector<Colour> m_gradient;
		Image* m_image;
	};

	class TOY_UI_EXPORT Options
	{
	public:
		std::vector<Var> m_fields;

		void set(size_t index, Var value) { if(index >= m_fields.size()) m_fields.resize(index+1); m_fields[index] = value; }

		void merge(const Options& other)
		{
			for(size_t i = 0; i < other.m_fields.size(); ++i)
				if(!other.m_fields[i].none())
					set(i, other.m_fields[i]);
		}
	};

	class _refl_ TOY_UI_EXPORT Layout : public Struct
	{
	public:
		_constr_ Layout(const string& name = "")
			: m_name(name), m_solver(FRAME_SOLVER), m_layout(Dim<AutoLayout>(AUTO_LAYOUT, AUTO_LAYOUT)), m_flow(FLOW), m_space(Space::preset(SHEET))
			, m_clipping(NOCLIP), m_opacity(CLEAR), m_align(Dim<Align>(LEFT, LEFT))
			, m_span(DimFloat(1.f, 1.f)), m_pivot(Dim<Pivot>(FORWARD, FORWARD)), m_zorder(0), m_updated(0)
		{}

		_attr_ _mut_ string m_name;
		_attr_ _mut_ LayoutSolver m_solver;
		_attr_ _mut_ Dim<AutoLayout> m_layout;
		_attr_ _mut_ Flow m_flow;
		_attr_ _mut_ Space m_space;
		_attr_ _mut_ Clipping m_clipping;
		_attr_ _mut_ Opacity m_opacity;
		_attr_ _mut_ Dim<Align> m_align;
		_attr_ _mut_ DimFloat m_span;
		_attr_ _mut_ DimFloat m_size;
		_attr_ _mut_ BoxFloat m_padding;
		_attr_ _mut_ DimFloat m_margin;
		_attr_ _mut_ DimFloat m_spacing;
		_attr_ _mut_ Dim<Pivot> m_pivot;
		_attr_ _mut_ int m_zorder;

		_attr_ _mut_ size_t m_updated;
	};

	class _refl_ TOY_UI_EXPORT InkStyle : public Struct
	{
	public:
		_constr_ InkStyle(const string& name = "")
			: m_name(name), m_empty(true), m_background_colour(Colour::None), m_border_colour(Colour::None), m_image_colour(Colour::None), m_text_colour(Colour::None)
			, m_text_font("dejavu"), m_text_size(14.f), m_text_break(true), m_text_wrap(false)
			, m_border_width(0.f), m_corner_radius(), m_weak_corners(false), m_padding(0.f), m_margin(0.f)
			, m_align(Dim<Align>(LEFT, LEFT)), m_linear_gradient(DimFloat(0.f, 0.f)), m_linear_gradient_dim(DIM_Y)
			, m_image(nullptr), m_overlay(nullptr), m_tile(nullptr), m_hover_cursor(nullptr)
		{}

		void prepare()
		{
			if(!m_background_colour.null() || !m_text_colour.null() || !m_border_colour.null() || m_image || !m_image_skin.null() || m_customRenderer)
				m_empty = false;
		}

		_attr_ _mut_ string m_name;
		_attr_ _mut_ bool m_empty;
		_attr_ _mut_ Colour m_background_colour;
		_attr_ _mut_ Colour m_border_colour;
		_attr_ _mut_ Colour m_image_colour;
		_attr_ _mut_ Colour m_text_colour;
		_attr_ _mut_ string m_text_font;
		_attr_ _mut_ float m_text_size;
		_attr_ _mut_ bool m_text_break;
		_attr_ _mut_ bool m_text_wrap;
		_attr_ _mut_ BoxFloat m_border_width;
		_attr_ _mut_ BoxFloat m_corner_radius;
		_attr_ _mut_ bool m_weak_corners;
		_attr_ _mut_ BoxFloat m_padding;
		_attr_ _mut_ BoxFloat m_margin;
		_attr_ _mut_ Dim<Align> m_align;
		_attr_ _mut_ DimFloat m_linear_gradient;
		_attr_ _mut_ Dimension m_linear_gradient_dim;
		_attr_ _mut_ Image* m_image;
		_attr_ _mut_ Image* m_overlay;
		_attr_ _mut_ Image* m_tile;
		_attr_ _mut_ ImageSkin m_image_skin;
		_attr_ _mut_ Shadow m_shadow;
		_attr_ _mut_ Colour m_shadow_colour;
		_attr_ _mut_ Style* m_hover_cursor;
		/*_attr_*/ CustomRenderer m_customRenderer;

		WidgetState m_state;
	};

	using StyleMap = std::map<string, Options>;

	class _refl_ TOY_UI_EXPORT Style : public Struct
	{
	public:
		Style(const string& name, Type* type, Style* base, Args args);

		Style() : Style("", nullptr, nullptr, {}) {}
		Style(const string& name, Style& base, Args args = {}) : Style(name, nullptr, &base, args) {}
		Style(Type& type, Style& base, Args args = {}) : Style(type.m_name, &type, &base, args) {}

		void init();
		void load(StyleMap& layout_defs, StyleMap& skin_defs);
		void define(Style& level, StyleMap& layout_defs, StyleMap& skin_defs);

		InkStyle& skin(WidgetState state);
		InkStyle& decline_skin(WidgetStates state);

	public:
		_attr_ Type* m_style_type;
		_attr_ Style* m_base;
		_attr_ string m_name;
		_attr_ Layout m_layout;
		_attr_ InkStyle m_skin;
		std::vector<InkStyle> m_skins;

		Args m_args;
		bool m_defined;
	};

	struct TOY_UI_EXPORT Styles
	{
		Styles();

		void setup(UiWindow& window);

		Style widget = { "Widget", &cls<Widget>(), nullptr, Args{ { &Layout::m_solver, FRAME_SOLVER } } };
		Style wedge = { cls<Wedge>(), widget, Args{ { &Layout::m_solver, ROW_SOLVER }, { &Layout::m_space, SHEET } } };
		Style root_sheet = { cls<RootSheet>(), wedge, Args{ { &Layout::m_space, LAYOUT }, { &Layout::m_clipping, CLIP }, { &Layout::m_opacity, OPAQUE } } };

		Style item = { "Item", widget, Args{ { &Layout::m_space, BLOCK }, { &Layout::m_align, Dim<Align>{ LEFT, CENTER } },
											 { &InkStyle::m_text_colour, Colour::White }, { &InkStyle::m_padding, BoxFloat(2.f) } } };
		Style control = { "Control", item, Args{ { &Layout::m_opacity, OPAQUE } } };

		Style spacer = { "Spacer", item, Args{ { &Layout::m_space, SPACER } } };
		Style filler = { "Filler", spacer, Args{ { &Layout::m_space, FLEX } } };

		Style div = { "Div", wedge, Args{ { &Layout::m_space, DIV } } };
		Style row = { "Row", wedge, Args{ { &Layout::m_space, LINE } } };
		Style stack = { "Stack", wedge, Args{ { &Layout::m_space, STACK } } };
		Style sheet = { "Sheet", wedge, Args{ { &Layout::m_space, SHEET } } };
		Style list = { "List", wedge };
		Style header = { "Header", row };
		Style board = { "Board", wedge, Args{ { &Layout::m_space, BOARD }, { &Layout::m_clipping, CLIP } } };
		Style layout = { "Layout", board, Args{ { &Layout::m_space, LAYOUT } } };
		Style screen = { "Screen", wedge, Args{ { &Layout::m_flow, FREE }, { &Layout::m_space, LAYOUT } } };
		Style decal = { "Decal", wedge, Args{ { &Layout::m_flow, FREE }, { &Layout::m_space, BLOCK } } };
		Style overlay = { "Overlay", wedge, Args{ { &Layout::m_flow, FREE }, { &Layout::m_space, UNIT }, { &Layout::m_opacity, OPAQUE } } };
		Style gridsheet = { cls<GridSheet>(), wedge, Args{ { &Layout::m_opacity, OPAQUE }, { &Layout::m_spacing, DimFloat(5.f) } } };

		Style wrap_control = { "WrapControl", wedge, Args{ { &Layout::m_space, LINE }, { &Layout::m_opacity, OPAQUE } } };

		Style label = { cls<Label>(), item, Args{ { &Layout::m_align, Dim<Align>{ LEFT, CENTER } } } };
		Style title = { "Title", item };
		Style text = { "Text", item, Args{ { &Layout::m_space, Space{ PARAGRAPH, FIXED, WRAP } }, { &InkStyle::m_text_wrap, true } } };

		Style button = { cls<Button>(), control };
		Style wrap_button = { cls<WrapButton>(), wrap_control };
		Style multi_button = { cls<MultiButton>(), wrap_button };
		Style toggle = { cls<Toggle>(), control };
		Style checkbox = { cls<Checkbox>(), toggle };

		Style tooltip = { cls<Tooltip>(), decal, Args{ { &Layout::m_zorder, -2 } } };
		Style rectangle = { cls<Rectangle>(), decal, Args{ { &Layout::m_space, BLOCK }, { &InkStyle::m_border_width, 1.f }, { &InkStyle::m_border_colour, Colour::Cyan } } };

		Style type_in = { cls<TypeIn>(), wrap_control, Args{ { &Layout::m_opacity, OPAQUE } } };
		Style textbox = { cls<Textbox>(), type_in, Args{ { &Layout::m_space, LAYOUT }, { &InkStyle::m_text_wrap, true } } };
		Style caret = { "Caret", item, Args{ { &InkStyle::m_background_colour, Colour::White } } };

		Style figure = { "Figure", item, Args{ { &InkStyle::m_empty, false} } };
		
		Style radio_switch = { cls<RadioSwitch>(), wrap_control };
		Style radio_choice = { "RadioChoice", multi_button };
		Style radio_choice_item = { "RadioChoiceItem", item };

		Style slider = { cls<Slider>(), wrap_control, Args{ { &Layout::m_space, FLEX } } };
		Style slider_knob = { "SliderKnob", item, Args{ /*{ &Layout::m_flow, OVERLAY }, { &Layout::m_space, FLEX }*/ } };
		Style slider_display = { "SliderDisplay", label, Args{ { &Layout::m_flow, OVERLAY }, { &Layout::m_align, Dim<Align>{ CENTER, CENTER } } } };

		Style progress_bar = { "Fillbar", row };

		Style number_input = { "NumberInput", row };
		Style slider_input = { "SliderInput", row };
		Style field_input = { "Field", wrap_control };
		Style input_bool = { cls<Input<bool>>(), wedge, Args{ { &Layout::m_space, UNIT } } };
		Style input_string = { cls<Input<string>>(), type_in };
		Style input_color = { cls<Input<Colour>>(), row };

		Style scrollsheet = { cls<ScrollSheet>(), wedge, Args{ { &Layout::m_solver, GRID_SOLVER }, { &Layout::m_opacity, OPAQUE } } };
		Style scroll_zone = { "ScrollZone", layout, Args{ { &Layout::m_layout, Dim<AutoLayout>{ AUTO_SIZE, AUTO_SIZE } }, { &Layout::m_clipping, CLIP } } };
		Style scroll_surface = { "ScrollSurface", wedge };
		
		Style scrollplan = { cls<ScrollPlan>(), scrollsheet };
		Style scrollplan_surface = { "ScrollplanSurface", sheet, Args{ { &Layout::m_space, BLOCK }/*, { &InkStyle::m_customRenderer, &drawGrid }*/ } };

		Style table = { cls<Table>(), stack, Args{ /*{ &Layout::m_solver, TABLE_SOLVER },*/ { &Layout::m_spacing, DimFloat(0.f, 2.f) } } };
		Style table_head = { "TableHead", gridsheet, Args{ { &Layout::m_space, DIV } } };
		Style column_header = { "ColumnHeader", row, Args{ { &Layout::m_space, LINE } } };

		Style popup = { cls<Popup>(), overlay, Args{ { &Layout::m_size, DimFloat{ 280.f, 350.f } } } };
	};
}

#endif // TOY_STYLE_H
