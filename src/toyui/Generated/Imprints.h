

#ifndef TOYUI_IMPRINTS_H
#define TOYUI_IMPRINTS_H

#include <toyui/Config.h>
#include <toyui/Forward.h>
#include <toyui/Bundle.h>
#include <toyui/Types.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Reflect/Member.h>
#include <toyobj/Reflect/Injector.h>
#include <toyobj/Reflect/Method.h>
#include <toyobj/Module/Module.h>
#include <toyobj/Util/Unique.h>

#ifdef TOYUI_REFLECTION_IMPL

namespace toy
{
    // Exported types
    template <> TOY_UI_EXPORT Type& typecls<Dimension>() { static Type ty("Dimension"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Direction>() { static Type ty("Direction"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Pivot>() { static Type ty("Pivot"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Align>() { static Type ty("Align"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<FrameType>() { static Type ty("FrameType"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<LayoutSolver>() { static Type ty("LayoutSolver"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<AutoLayout>() { static Type ty("AutoLayout"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Flow>() { static Type ty("Flow"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Sizing>() { static Type ty("Sizing"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<SpacePreset>() { static Type ty("SpacePreset"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Clipping>() { static Type ty("Clipping"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Opacity>() { static Type ty("Opacity"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<WidgetState>() { static Type ty("WidgetState"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<std::vector<Widget*>>() { static Type ty("std::vector<Widget*>"); return ty; }
    
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<ImageSkin>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<ImageSkin>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<LayoutStyle>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<LayoutStyle>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Style>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Style>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Widget>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Widget>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Wedge>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Wedge>>() { static Type ty; return ty; }
    



	void ImageSkin_d_image(Object& object, Lref& ref) { ref.pointer<Image>() = object.as<ImageSkin>().d_image; }
	void ImageSkin_setD_image(Object& object, const Lref& ref) { object.as<ImageSkin>().d_image = ref.pointer<Image>(); }
	void ImageSkin_d_left(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_left; }
	void ImageSkin_setD_left(Object& object, const Lref& ref) { object.as<ImageSkin>().d_left = ref.value<int>(); }
	void ImageSkin_d_top(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_top; }
	void ImageSkin_setD_top(Object& object, const Lref& ref) { object.as<ImageSkin>().d_top = ref.value<int>(); }
	void ImageSkin_d_right(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_right; }
	void ImageSkin_setD_right(Object& object, const Lref& ref) { object.as<ImageSkin>().d_right = ref.value<int>(); }
	void ImageSkin_d_bottom(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_bottom; }
	void ImageSkin_setD_bottom(Object& object, const Lref& ref) { object.as<ImageSkin>().d_bottom = ref.value<int>(); }
	void ImageSkin_d_margin(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_margin; }
	void ImageSkin_setD_margin(Object& object, const Lref& ref) { object.as<ImageSkin>().d_margin = ref.value<int>(); }
	void ImageSkin_d_stretch(Object& object, Lref& ref) { ref.value<Dimension>() = object.as<ImageSkin>().d_stretch; }
	void ImageSkin_setD_stretch(Object& object, const Lref& ref) { object.as<ImageSkin>().d_stretch = ref.value<Dimension>(); }



	void LayoutStyle_d_updated(Object& object, Lref& ref) { ref.value<size_t>() = object.as<LayoutStyle>().d_updated; }
	void LayoutStyle_setD_updated(Object& object, const Lref& ref) { object.as<LayoutStyle>().d_updated = ref.value<size_t>(); }

    Object& InkStyle_construct_0(Lref& ref, Lref* args) {  ref.value<InkStyle>() = InkStyle( args[0].pointer<Style>() ); return ref.value<InkStyle>(); }

	void Style_m_base(Object& object, Lref& ref) { ref.pointer<Style>() = object.as<Style>().m_base; }
	void Style_m_name(Object& object, Lref& ref) { ref.value<string>() = object.as<Style>().m_name; }
	void Style_m_layout(Object& object, Lref& ref) { ref.value<LayoutStyle>() = object.as<Style>().m_layout; }
	void Style_m_skin(Object& object, Lref& ref) { ref.value<InkStyle>() = object.as<Style>().m_skin; }


	void Widget_m_parent(Object& object, Lref& ref) { ref.pointer<Wedge>() = object.as<Widget>().m_parent; }
	void Widget_m_container(Object& object, Lref& ref) { ref.pointer<Wedge>() = object.as<Widget>().m_container; }
	void Widget_m_index(Object& object, Lref& ref) { ref.value<size_t>() = object.as<Widget>().m_index; }
	void Widget_m_style(Object& object, Lref& ref) { ref.pointer<Style>() = object.as<Widget>().m_style; }
	void Widget_setM_style(Object& object, const Lref& ref) { object.as<Widget>().m_style = ref.pointer<Style>(); }
	void Widget_m_state(Object& object, Lref& ref) { ref.value<WidgetState>() = object.as<Widget>().m_state; }








	void Wedge_contents(Object& object, Lref& ref) { ref.pointer<std::vector<Widget*>>() = &object.as<Wedge>().contents(); }

















































    


    void toyuiCarbon(Module& module)
    {
        // Base Types
    
        // Enums
        typecls<Dimension>().imprint().name = "Dimension";
        typecls<Dimension>().imprint().typeClass = ENUM;
        typecls<Dimension>().imprint().enumIds = { "DIM_X", "DIM_Y", "DIM_XX", "DIM_YY", "DIM_NULL" };
        typecls<Dimension>().imprint().initRefMethods<Dimension>();
        typecls<Dimension>().imprint().setup();
        
        typecls<Direction>().imprint().name = "Direction";
        typecls<Direction>().imprint().typeClass = ENUM;
        typecls<Direction>().imprint().enumIds = { "DIRECTION_NONE", "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL" };
        typecls<Direction>().imprint().initRefMethods<Direction>();
        typecls<Direction>().imprint().setup();
        
        typecls<Pivot>().imprint().name = "Pivot";
        typecls<Pivot>().imprint().typeClass = ENUM;
        typecls<Pivot>().imprint().enumIds = { "FORWARD", "REVERSE" };
        typecls<Pivot>().imprint().initRefMethods<Pivot>();
        typecls<Pivot>().imprint().setup();
        
        typecls<Align>().imprint().name = "Align";
        typecls<Align>().imprint().typeClass = ENUM;
        typecls<Align>().imprint().enumIds = { "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" };
        typecls<Align>().imprint().initRefMethods<Align>();
        typecls<Align>().imprint().setup();
        
        typecls<FrameType>().imprint().name = "FrameType";
        typecls<FrameType>().imprint().typeClass = ENUM;
        typecls<FrameType>().imprint().enumIds = { "FRAME", "LAYER", "MASTER_LAYER", "SPACE_LAYER" };
        typecls<FrameType>().imprint().initRefMethods<FrameType>();
        typecls<FrameType>().imprint().setup();
        
        typecls<LayoutSolver>().imprint().name = "LayoutSolver";
        typecls<LayoutSolver>().imprint().typeClass = ENUM;
        typecls<LayoutSolver>().imprint().enumIds = { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" };
        typecls<LayoutSolver>().imprint().initRefMethods<LayoutSolver>();
        typecls<LayoutSolver>().imprint().setup();
        
        typecls<AutoLayout>().imprint().name = "AutoLayout";
        typecls<AutoLayout>().imprint().typeClass = ENUM;
        typecls<AutoLayout>().imprint().enumIds = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" };
        typecls<AutoLayout>().imprint().initRefMethods<AutoLayout>();
        typecls<AutoLayout>().imprint().setup();
        
        typecls<Flow>().imprint().name = "Flow";
        typecls<Flow>().imprint().typeClass = ENUM;
        typecls<Flow>().imprint().enumIds = { "FLOW", "OVERLAY", "ALIGN", "FREE" };
        typecls<Flow>().imprint().initRefMethods<Flow>();
        typecls<Flow>().imprint().setup();
        
        typecls<Sizing>().imprint().name = "Sizing";
        typecls<Sizing>().imprint().typeClass = ENUM;
        typecls<Sizing>().imprint().enumIds = { "FIXED", "SHRINK", "WRAP", "EXPAND" };
        typecls<Sizing>().imprint().initRefMethods<Sizing>();
        typecls<Sizing>().imprint().setup();
        
        typecls<SpacePreset>().imprint().name = "SpacePreset";
        typecls<SpacePreset>().imprint().typeClass = ENUM;
        typecls<SpacePreset>().imprint().enumIds = { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD" };
        typecls<SpacePreset>().imprint().initRefMethods<SpacePreset>();
        typecls<SpacePreset>().imprint().setup();
        
        typecls<Clipping>().imprint().name = "Clipping";
        typecls<Clipping>().imprint().typeClass = ENUM;
        typecls<Clipping>().imprint().enumIds = { "NOCLIP", "CLIP" };
        typecls<Clipping>().imprint().initRefMethods<Clipping>();
        typecls<Clipping>().imprint().setup();
        
        typecls<Opacity>().imprint().name = "Opacity";
        typecls<Opacity>().imprint().typeClass = ENUM;
        typecls<Opacity>().imprint().enumIds = { "OPAQUE", "CLEAR", "HOLLOW" };
        typecls<Opacity>().imprint().initRefMethods<Opacity>();
        typecls<Opacity>().imprint().setup();
        
        typecls<WidgetState>().imprint().name = "WidgetState";
        typecls<WidgetState>().imprint().typeClass = ENUM;
        typecls<WidgetState>().imprint().enumIds = { "NOSTATE", "FOCUSED", "TRIGGERED", "ACTIVATED", "SELECTED", "DRAGGED", "DISABLED", "ACTIVE", "CONTROL", "MODAL" };
        typecls<WidgetState>().imprint().initRefMethods<WidgetState>();
        typecls<WidgetState>().imprint().setup();
        
    
        // Sequences
        typecls<std::vector<Widget*>>().imprint().name = "std::vector<Widget*>";
        typecls<std::vector<Widget*>>().imprint().typeClass = SEQUENCE;
        typecls<std::vector<Widget*>>().imprint().initRefMethods<std::vector<Widget*>>();
        typecls<std::vector<Widget*>>().imprint().initObjectVector<Widget*>();
        typecls<std::vector<Widget*>>().imprint().setup();
        
    
        // Stores
    
    
        // BoxFloat
        BoxFloat::cls().imprint().inherit();
        BoxFloat::cls().imprint().name = "BoxFloat";
        BoxFloat::cls().imprint().typeClass = STRUCT;
        BoxFloat::cls().imprint().serializable = false;
        BoxFloat::cls().imprint().isTypeObject = false;
        BoxFloat::cls().imprint().initRefMethods<BoxFloat>();
        BoxFloat::cls().imprint().setup();
        
        
        // Image
        Image::cls().imprint().inherit();
        Image::cls().imprint().name = "Image";
        Image::cls().imprint().typeClass = STRUCT;
        Image::cls().imprint().serializable = false;
        Image::cls().imprint().isTypeObject = false;
        Image::cls().imprint().initRefMethods<Image>();
        Image::cls().imprint().setup();
        
        
        // ImageSkin
        ImageSkin::cls().imprint().inherit();
        ImageSkin::cls().imprint().name = "ImageSkin";
        ImageSkin::cls().imprint().typeClass = STRUCT;
        ImageSkin::cls().imprint().serializable = false;
        ImageSkin::cls().imprint().isTypeObject = false;
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_image), Image::cls(), "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_left), typecls<int>(), "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_top), typecls<int>(), "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_right), typecls<int>(), "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_bottom), typecls<int>(), "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_margin), typecls<int>(), "d_margin", &ImageSkin_d_margin, &ImageSkin_setD_margin, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_stretch), typecls<Dimension>(), "d_stretch", &ImageSkin_d_stretch, &ImageSkin_setD_stretch, true, true, false, false));
        ImageSkin::cls().imprint().initRefMethods<ImageSkin>();
        ImageSkin::cls().imprint().setup();
        
        
        // Shadow
        Shadow::cls().imprint().inherit();
        Shadow::cls().imprint().name = "Shadow";
        Shadow::cls().imprint().typeClass = STRUCT;
        Shadow::cls().imprint().serializable = false;
        Shadow::cls().imprint().isTypeObject = false;
        Shadow::cls().imprint().initRefMethods<Shadow>();
        Shadow::cls().imprint().setup();
        
        
        // Paint
        Paint::cls().imprint().inherit();
        Paint::cls().imprint().name = "Paint";
        Paint::cls().imprint().typeClass = STRUCT;
        Paint::cls().imprint().serializable = false;
        Paint::cls().imprint().isTypeObject = false;
        Paint::cls().imprint().initRefMethods<Paint>();
        Paint::cls().imprint().setup();
        
        
        // LayoutStyle
        LayoutStyle::cls().imprint().inherit();
        LayoutStyle::cls().imprint().name = "LayoutStyle";
        LayoutStyle::cls().imprint().typeClass = STRUCT;
        LayoutStyle::cls().imprint().serializable = false;
        LayoutStyle::cls().imprint().isTypeObject = false;
        LayoutStyle::cls().imprint().members.push_back(Member(LayoutStyle::cls(), member_var(&LayoutStyle::d_updated), typecls<unsigned int>(), "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, true, true, false, false));
        LayoutStyle::cls().imprint().initRefMethods<LayoutStyle>();
        LayoutStyle::cls().imprint().setup();
        
        
        // InkStyle
        InkStyle::cls().imprint().inherit();
        InkStyle::cls().imprint().name = "InkStyle";
        InkStyle::cls().imprint().typeClass = STRUCT;
        InkStyle::cls().imprint().serializable = false;
        InkStyle::cls().imprint().isTypeObject = false;
        InkStyle::cls().imprint().constructors.push_back(Constructor(InkStyle::cls(), &InkStyle_construct_0, ParamVector({ Param("style", ref(Style::cls()), true, INPUT_PARAM) })));
        InkStyle::cls().imprint().initRefMethods<InkStyle>();
        InkStyle::cls().imprint().setup();
        
        
        // Style
        Style::cls().imprint().inherit();
        Style::cls().imprint().name = "Style";
        Style::cls().imprint().typeClass = OBJECT;
        Style::cls().imprint().serializable = false;
        Style::cls().imprint().isTypeObject = true;
        Style::cls().imprint().members.push_back(Member(Style::cls(), member_var(&Style::m_base), Style::cls(), "m_base", &Style_m_base, nullptr, true, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), member_var(&Style::m_name), typecls<string>(), "m_name", &Style_m_name, nullptr, true, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), member_var(&Style::m_layout), LayoutStyle::cls(), "m_layout", &Style_m_layout, nullptr, true, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), member_var(&Style::m_skin), InkStyle::cls(), "m_skin", &Style_m_skin, nullptr, true, false, false, false));
        Style::cls().imprint().setup();
        
        
        // Frame
        Frame::cls().imprint().inherit();
        Frame::cls().imprint().name = "Frame";
        Frame::cls().imprint().typeClass = OBJECT;
        Frame::cls().imprint().serializable = false;
        Frame::cls().imprint().isTypeObject = false;
        Frame::cls().imprint().setup();
        
        
        // Widget
        Widget::cls().imprint().inherit();
        Widget::cls().imprint().name = "Widget";
        Widget::cls().imprint().typeClass = OBJECT;
        Widget::cls().imprint().serializable = false;
        Widget::cls().imprint().isTypeObject = true;
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), member_var(&Widget::m_parent), Wedge::cls(), "m_parent", &Widget_m_parent, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), member_var(&Widget::m_container), Wedge::cls(), "m_container", &Widget_m_container, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), member_var(&Widget::m_index), typecls<unsigned int>(), "m_index", &Widget_m_index, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), member_var(&Widget::m_style), Style::cls(), "m_style", &Widget_m_style, &Widget_setM_style, true, true, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), member_var(&Widget::m_state), typecls<WidgetState>(), "m_state", &Widget_m_state, nullptr, true, false, false, false));
        Widget::cls().imprint().setup();
        
        
        // StatSlider<float>
        StatSlider<float>::cls().imprint().inherit();
        StatSlider<float>::cls().imprint().name = "StatSlider<float>";
        StatSlider<float>::cls().imprint().typeClass = OBJECT;
        StatSlider<float>::cls().imprint().serializable = false;
        StatSlider<float>::cls().imprint().isTypeObject = false;
        StatSlider<float>::cls().imprint().setup();
        
        
        // StatSlider<int>
        StatSlider<int>::cls().imprint().inherit();
        StatSlider<int>::cls().imprint().name = "StatSlider<int>";
        StatSlider<int>::cls().imprint().typeClass = OBJECT;
        StatSlider<int>::cls().imprint().serializable = false;
        StatSlider<int>::cls().imprint().isTypeObject = false;
        StatSlider<int>::cls().imprint().setup();
        
        
        // Input<unsigned int>
        Input<unsigned int>::cls().imprint().inherit();
        Input<unsigned int>::cls().imprint().name = "Input<unsigned int>";
        Input<unsigned int>::cls().imprint().typeClass = OBJECT;
        Input<unsigned int>::cls().imprint().serializable = false;
        Input<unsigned int>::cls().imprint().isTypeObject = false;
        Input<unsigned int>::cls().imprint().setup();
        
        
        // Input<int>
        Input<int>::cls().imprint().inherit();
        Input<int>::cls().imprint().name = "Input<int>";
        Input<int>::cls().imprint().typeClass = OBJECT;
        Input<int>::cls().imprint().serializable = false;
        Input<int>::cls().imprint().isTypeObject = false;
        Input<int>::cls().imprint().setup();
        
        
        // Input<float>
        Input<float>::cls().imprint().inherit();
        Input<float>::cls().imprint().name = "Input<float>";
        Input<float>::cls().imprint().typeClass = OBJECT;
        Input<float>::cls().imprint().serializable = false;
        Input<float>::cls().imprint().isTypeObject = false;
        Input<float>::cls().imprint().setup();
        
        
        // Input<double>
        Input<double>::cls().imprint().inherit();
        Input<double>::cls().imprint().name = "Input<double>";
        Input<double>::cls().imprint().typeClass = OBJECT;
        Input<double>::cls().imprint().serializable = false;
        Input<double>::cls().imprint().isTypeObject = false;
        Input<double>::cls().imprint().setup();
        
        
        // Item
        Item::cls().imprint().inherit();
        Item::cls().imprint().name = "Item";
        Item::cls().imprint().typeClass = OBJECT;
        Item::cls().imprint().serializable = false;
        Item::cls().imprint().isTypeObject = false;
        Item::cls().imprint().setup();
        
        
        // Wedge
        Wedge::cls().imprint().inherit();
        Wedge::cls().imprint().name = "Wedge";
        Wedge::cls().imprint().typeClass = OBJECT;
        Wedge::cls().imprint().serializable = false;
        Wedge::cls().imprint().isTypeObject = false;
        Wedge::cls().imprint().members.push_back(Member(Wedge::cls(), method_var(&Wedge::contents), typecls<std::vector<Widget*>>(), "contents", &Wedge_contents, nullptr, false, false, true, false));
        Wedge::cls().imprint().setup();
        
        
        // GridSheet
        GridSheet::cls().imprint().inherit();
        GridSheet::cls().imprint().name = "GridSheet";
        GridSheet::cls().imprint().typeClass = OBJECT;
        GridSheet::cls().imprint().serializable = false;
        GridSheet::cls().imprint().isTypeObject = false;
        GridSheet::cls().imprint().setup();
        
        
        // Tooltip
        Tooltip::cls().imprint().inherit();
        Tooltip::cls().imprint().name = "Tooltip";
        Tooltip::cls().imprint().typeClass = OBJECT;
        Tooltip::cls().imprint().serializable = false;
        Tooltip::cls().imprint().isTypeObject = false;
        Tooltip::cls().imprint().setup();
        
        
        // Rectangle
        Rectangle::cls().imprint().inherit();
        Rectangle::cls().imprint().name = "Rectangle";
        Rectangle::cls().imprint().typeClass = OBJECT;
        Rectangle::cls().imprint().serializable = false;
        Rectangle::cls().imprint().isTypeObject = false;
        Rectangle::cls().imprint().setup();
        
        
        // Cursor
        Cursor::cls().imprint().inherit();
        Cursor::cls().imprint().name = "Cursor";
        Cursor::cls().imprint().typeClass = OBJECT;
        Cursor::cls().imprint().serializable = false;
        Cursor::cls().imprint().isTypeObject = false;
        Cursor::cls().imprint().setup();
        
        
        // RootSheet
        RootSheet::cls().imprint().inherit();
        RootSheet::cls().imprint().name = "RootSheet";
        RootSheet::cls().imprint().typeClass = OBJECT;
        RootSheet::cls().imprint().serializable = false;
        RootSheet::cls().imprint().isTypeObject = false;
        RootSheet::cls().imprint().setup();
        
        
        // Label
        Label::cls().imprint().inherit();
        Label::cls().imprint().name = "Label";
        Label::cls().imprint().typeClass = OBJECT;
        Label::cls().imprint().serializable = false;
        Label::cls().imprint().isTypeObject = false;
        Label::cls().imprint().setup();
        
        
        // Button
        Button::cls().imprint().inherit();
        Button::cls().imprint().name = "Button";
        Button::cls().imprint().typeClass = OBJECT;
        Button::cls().imprint().serializable = false;
        Button::cls().imprint().isTypeObject = false;
        Button::cls().imprint().setup();
        
        
        // WrapButton
        WrapButton::cls().imprint().inherit();
        WrapButton::cls().imprint().name = "WrapButton";
        WrapButton::cls().imprint().typeClass = OBJECT;
        WrapButton::cls().imprint().serializable = false;
        WrapButton::cls().imprint().isTypeObject = false;
        WrapButton::cls().imprint().setup();
        
        
        // Toggle
        Toggle::cls().imprint().inherit();
        Toggle::cls().imprint().name = "Toggle";
        Toggle::cls().imprint().typeClass = OBJECT;
        Toggle::cls().imprint().serializable = false;
        Toggle::cls().imprint().isTypeObject = false;
        Toggle::cls().imprint().setup();
        
        
        // Slider
        Slider::cls().imprint().inherit();
        Slider::cls().imprint().name = "Slider";
        Slider::cls().imprint().typeClass = OBJECT;
        Slider::cls().imprint().serializable = false;
        Slider::cls().imprint().isTypeObject = false;
        Slider::cls().imprint().setup();
        
        
        // Scrollbar
        Scrollbar::cls().imprint().inherit();
        Scrollbar::cls().imprint().name = "Scrollbar";
        Scrollbar::cls().imprint().typeClass = OBJECT;
        Scrollbar::cls().imprint().serializable = false;
        Scrollbar::cls().imprint().isTypeObject = false;
        Scrollbar::cls().imprint().setup();
        
        
        // ScrollSheet
        ScrollSheet::cls().imprint().inherit();
        ScrollSheet::cls().imprint().name = "ScrollSheet";
        ScrollSheet::cls().imprint().typeClass = OBJECT;
        ScrollSheet::cls().imprint().serializable = false;
        ScrollSheet::cls().imprint().isTypeObject = false;
        ScrollSheet::cls().imprint().setup();
        
        
        // TypeIn
        TypeIn::cls().imprint().inherit();
        TypeIn::cls().imprint().name = "TypeIn";
        TypeIn::cls().imprint().typeClass = OBJECT;
        TypeIn::cls().imprint().serializable = false;
        TypeIn::cls().imprint().isTypeObject = false;
        TypeIn::cls().imprint().setup();
        
        
        // Input<bool>
        Input<bool>::cls().imprint().inherit();
        Input<bool>::cls().imprint().name = "Input<bool>";
        Input<bool>::cls().imprint().typeClass = OBJECT;
        Input<bool>::cls().imprint().serializable = false;
        Input<bool>::cls().imprint().isTypeObject = false;
        Input<bool>::cls().imprint().setup();
        
        
        // Input<toy::Colour>
        Input<toy::Colour>::cls().imprint().inherit();
        Input<toy::Colour>::cls().imprint().name = "Input<toy::Colour>";
        Input<toy::Colour>::cls().imprint().typeClass = OBJECT;
        Input<toy::Colour>::cls().imprint().serializable = false;
        Input<toy::Colour>::cls().imprint().isTypeObject = false;
        Input<toy::Colour>::cls().imprint().setup();
        
        
        // Expandbox
        Expandbox::cls().imprint().inherit();
        Expandbox::cls().imprint().name = "Expandbox";
        Expandbox::cls().imprint().typeClass = OBJECT;
        Expandbox::cls().imprint().serializable = false;
        Expandbox::cls().imprint().isTypeObject = false;
        Expandbox::cls().imprint().setup();
        
        
        // Tree
        Tree::cls().imprint().inherit();
        Tree::cls().imprint().name = "Tree";
        Tree::cls().imprint().typeClass = OBJECT;
        Tree::cls().imprint().serializable = false;
        Tree::cls().imprint().isTypeObject = false;
        Tree::cls().imprint().setup();
        
        
        // Table
        Table::cls().imprint().inherit();
        Table::cls().imprint().name = "Table";
        Table::cls().imprint().typeClass = OBJECT;
        Table::cls().imprint().serializable = false;
        Table::cls().imprint().isTypeObject = false;
        Table::cls().imprint().setup();
        
        
        // Tab
        Tab::cls().imprint().inherit();
        Tab::cls().imprint().name = "Tab";
        Tab::cls().imprint().typeClass = OBJECT;
        Tab::cls().imprint().serializable = false;
        Tab::cls().imprint().isTypeObject = false;
        Tab::cls().imprint().setup();
        
        
        // Tabber
        Tabber::cls().imprint().inherit();
        Tabber::cls().imprint().name = "Tabber";
        Tabber::cls().imprint().typeClass = OBJECT;
        Tabber::cls().imprint().serializable = false;
        Tabber::cls().imprint().isTypeObject = false;
        Tabber::cls().imprint().setup();
        
        
        // Directory
        Directory::cls().imprint().inherit();
        Directory::cls().imprint().name = "Directory";
        Directory::cls().imprint().typeClass = OBJECT;
        Directory::cls().imprint().serializable = false;
        Directory::cls().imprint().isTypeObject = false;
        Directory::cls().imprint().setup();
        
        
        // FileBrowser
        FileBrowser::cls().imprint().inherit();
        FileBrowser::cls().imprint().name = "FileBrowser";
        FileBrowser::cls().imprint().typeClass = OBJECT;
        FileBrowser::cls().imprint().serializable = false;
        FileBrowser::cls().imprint().isTypeObject = false;
        FileBrowser::cls().imprint().setup();
        
        
        // Dockspace
        Dockspace::cls().imprint().inherit();
        Dockspace::cls().imprint().name = "Dockspace";
        Dockspace::cls().imprint().typeClass = OBJECT;
        Dockspace::cls().imprint().serializable = false;
        Dockspace::cls().imprint().isTypeObject = false;
        Dockspace::cls().imprint().setup();
        
        
        // WindowHeader
        WindowHeader::cls().imprint().inherit();
        WindowHeader::cls().imprint().name = "WindowHeader";
        WindowHeader::cls().imprint().typeClass = OBJECT;
        WindowHeader::cls().imprint().serializable = false;
        WindowHeader::cls().imprint().isTypeObject = false;
        WindowHeader::cls().imprint().setup();
        
        
        // WindowSizer
        WindowSizer::cls().imprint().inherit();
        WindowSizer::cls().imprint().name = "WindowSizer";
        WindowSizer::cls().imprint().typeClass = OBJECT;
        WindowSizer::cls().imprint().serializable = false;
        WindowSizer::cls().imprint().isTypeObject = false;
        WindowSizer::cls().imprint().setup();
        
        
        // WindowFooter
        WindowFooter::cls().imprint().inherit();
        WindowFooter::cls().imprint().name = "WindowFooter";
        WindowFooter::cls().imprint().typeClass = OBJECT;
        WindowFooter::cls().imprint().serializable = false;
        WindowFooter::cls().imprint().isTypeObject = false;
        WindowFooter::cls().imprint().setup();
        
        
        // Window
        Window::cls().imprint().inherit();
        Window::cls().imprint().name = "Window";
        Window::cls().imprint().typeClass = OBJECT;
        Window::cls().imprint().serializable = false;
        Window::cls().imprint().isTypeObject = false;
        Window::cls().imprint().setup();
        
        
        // Menubar
        Menubar::cls().imprint().inherit();
        Menubar::cls().imprint().name = "Menubar";
        Menubar::cls().imprint().typeClass = OBJECT;
        Menubar::cls().imprint().serializable = false;
        Menubar::cls().imprint().isTypeObject = false;
        Menubar::cls().imprint().setup();
        
        
        // Tooldock
        Tooldock::cls().imprint().inherit();
        Tooldock::cls().imprint().name = "Tooldock";
        Tooldock::cls().imprint().typeClass = OBJECT;
        Tooldock::cls().imprint().serializable = false;
        Tooldock::cls().imprint().isTypeObject = false;
        Tooldock::cls().imprint().setup();
        
        
        // Toolbar
        Toolbar::cls().imprint().inherit();
        Toolbar::cls().imprint().name = "Toolbar";
        Toolbar::cls().imprint().typeClass = OBJECT;
        Toolbar::cls().imprint().serializable = false;
        Toolbar::cls().imprint().isTypeObject = false;
        Toolbar::cls().imprint().setup();
        
        
        // Text
        Text::cls().imprint().inherit();
        Text::cls().imprint().name = "Text";
        Text::cls().imprint().typeClass = OBJECT;
        Text::cls().imprint().serializable = false;
        Text::cls().imprint().isTypeObject = false;
        Text::cls().imprint().setup();
        
        
        // MultiButton
        MultiButton::cls().imprint().inherit();
        MultiButton::cls().imprint().name = "MultiButton";
        MultiButton::cls().imprint().typeClass = OBJECT;
        MultiButton::cls().imprint().serializable = false;
        MultiButton::cls().imprint().isTypeObject = false;
        MultiButton::cls().imprint().setup();
        
        
        // Checkbox
        Checkbox::cls().imprint().inherit();
        Checkbox::cls().imprint().name = "Checkbox";
        Checkbox::cls().imprint().typeClass = OBJECT;
        Checkbox::cls().imprint().serializable = false;
        Checkbox::cls().imprint().isTypeObject = false;
        Checkbox::cls().imprint().setup();
        
        
        // ScrollPlan
        ScrollPlan::cls().imprint().inherit();
        ScrollPlan::cls().imprint().name = "ScrollPlan";
        ScrollPlan::cls().imprint().typeClass = OBJECT;
        ScrollPlan::cls().imprint().serializable = false;
        ScrollPlan::cls().imprint().isTypeObject = false;
        ScrollPlan::cls().imprint().setup();
        
        
        // SelectList
        SelectList::cls().imprint().inherit();
        SelectList::cls().imprint().name = "SelectList";
        SelectList::cls().imprint().typeClass = OBJECT;
        SelectList::cls().imprint().serializable = false;
        SelectList::cls().imprint().isTypeObject = false;
        SelectList::cls().imprint().setup();
        
        
        // Dropdown
        Dropdown::cls().imprint().inherit();
        Dropdown::cls().imprint().name = "Dropdown";
        Dropdown::cls().imprint().typeClass = OBJECT;
        Dropdown::cls().imprint().serializable = false;
        Dropdown::cls().imprint().isTypeObject = false;
        Dropdown::cls().imprint().setup();
        
        
        // Textbox
        Textbox::cls().imprint().inherit();
        Textbox::cls().imprint().name = "Textbox";
        Textbox::cls().imprint().typeClass = OBJECT;
        Textbox::cls().imprint().serializable = false;
        Textbox::cls().imprint().isTypeObject = false;
        Textbox::cls().imprint().setup();
        
        
        // Input<string>
        Input<string>::cls().imprint().inherit();
        Input<string>::cls().imprint().name = "Input<string>";
        Input<string>::cls().imprint().typeClass = OBJECT;
        Input<string>::cls().imprint().serializable = false;
        Input<string>::cls().imprint().isTypeObject = false;
        Input<string>::cls().imprint().setup();
        
        
        // TreeNode
        TreeNode::cls().imprint().inherit();
        TreeNode::cls().imprint().name = "TreeNode";
        TreeNode::cls().imprint().typeClass = OBJECT;
        TreeNode::cls().imprint().serializable = false;
        TreeNode::cls().imprint().isTypeObject = false;
        TreeNode::cls().imprint().setup();
        
        
        // Docksection
        Docksection::cls().imprint().inherit();
        Docksection::cls().imprint().name = "Docksection";
        Docksection::cls().imprint().typeClass = OBJECT;
        Docksection::cls().imprint().serializable = false;
        Docksection::cls().imprint().isTypeObject = false;
        Docksection::cls().imprint().setup();
        
        
        // Dockline
        Dockline::cls().imprint().inherit();
        Dockline::cls().imprint().name = "Dockline";
        Dockline::cls().imprint().typeClass = OBJECT;
        Dockline::cls().imprint().serializable = false;
        Dockline::cls().imprint().isTypeObject = false;
        Dockline::cls().imprint().setup();
        
        
        // DropdownInput
        DropdownInput::cls().imprint().inherit();
        DropdownInput::cls().imprint().name = "DropdownInput";
        DropdownInput::cls().imprint().typeClass = OBJECT;
        DropdownInput::cls().imprint().serializable = false;
        DropdownInput::cls().imprint().isTypeObject = false;
        DropdownInput::cls().imprint().setup();
        
        
        // Dir
        Dir::cls().imprint().inherit();
        Dir::cls().imprint().name = "Dir";
        Dir::cls().imprint().typeClass = OBJECT;
        Dir::cls().imprint().serializable = false;
        Dir::cls().imprint().isTypeObject = false;
        Dir::cls().imprint().setup();
        
        
        // File
        File::cls().imprint().inherit();
        File::cls().imprint().name = "File";
        File::cls().imprint().typeClass = OBJECT;
        File::cls().imprint().serializable = false;
        File::cls().imprint().isTypeObject = false;
        File::cls().imprint().setup();
        
        
        // FileNode
        FileNode::cls().imprint().inherit();
        FileNode::cls().imprint().name = "FileNode";
        FileNode::cls().imprint().typeClass = OBJECT;
        FileNode::cls().imprint().serializable = false;
        FileNode::cls().imprint().isTypeObject = false;
        FileNode::cls().imprint().setup();
        
        
        // DirectoryNode
        DirectoryNode::cls().imprint().inherit();
        DirectoryNode::cls().imprint().name = "DirectoryNode";
        DirectoryNode::cls().imprint().typeClass = OBJECT;
        DirectoryNode::cls().imprint().serializable = false;
        DirectoryNode::cls().imprint().isTypeObject = false;
        DirectoryNode::cls().imprint().setup();
        
        
        // Menu
        Menu::cls().imprint().inherit();
        Menu::cls().imprint().name = "Menu";
        Menu::cls().imprint().typeClass = OBJECT;
        Menu::cls().imprint().serializable = false;
        Menu::cls().imprint().isTypeObject = false;
        Menu::cls().imprint().setup();
        
        
        // ToolButton
        ToolButton::cls().imprint().inherit();
        ToolButton::cls().imprint().name = "ToolButton";
        ToolButton::cls().imprint().typeClass = OBJECT;
        ToolButton::cls().imprint().serializable = false;
        ToolButton::cls().imprint().isTypeObject = false;
        ToolButton::cls().imprint().setup();
        
        
        
        module.types.push_back(&typecls<Dimension>());
        module.types.push_back(&typecls<Direction>());
        module.types.push_back(&typecls<Pivot>());
        module.types.push_back(&typecls<Align>());
        module.types.push_back(&typecls<FrameType>());
        module.types.push_back(&typecls<LayoutSolver>());
        module.types.push_back(&typecls<AutoLayout>());
        module.types.push_back(&typecls<Flow>());
        module.types.push_back(&typecls<Sizing>());
        module.types.push_back(&typecls<SpacePreset>());
        module.types.push_back(&typecls<Clipping>());
        module.types.push_back(&typecls<Opacity>());
        module.types.push_back(&BoxFloat::cls());
        module.types.push_back(&Image::cls());
        module.types.push_back(&ImageSkin::cls());
        module.types.push_back(&Shadow::cls());
        module.types.push_back(&Paint::cls());
        module.types.push_back(&LayoutStyle::cls());
        module.types.push_back(&InkStyle::cls());
        module.types.push_back(&Style::cls());
        module.types.push_back(&Frame::cls());
        module.types.push_back(&typecls<WidgetState>());
        module.types.push_back(&Widget::cls());
        module.types.push_back(&Item::cls());
        module.types.push_back(&Wedge::cls());
        module.types.push_back(&typecls<std::vector<Widget*>>());
        module.types.push_back(&GridSheet::cls());
        module.types.push_back(&Tooltip::cls());
        module.types.push_back(&Rectangle::cls());
        module.types.push_back(&Cursor::cls());
        module.types.push_back(&RootSheet::cls());
        module.types.push_back(&Label::cls());
        module.types.push_back(&Text::cls());
        module.types.push_back(&Button::cls());
        module.types.push_back(&WrapButton::cls());
        module.types.push_back(&MultiButton::cls());
        module.types.push_back(&Toggle::cls());
        module.types.push_back(&Slider::cls());
        module.types.push_back(&Scrollbar::cls());
        module.types.push_back(&Checkbox::cls());
        module.types.push_back(&ScrollSheet::cls());
        module.types.push_back(&ScrollPlan::cls());
        module.types.push_back(&SelectList::cls());
        module.types.push_back(&Dropdown::cls());
        module.types.push_back(&DropdownInput::cls());
        module.types.push_back(&TypeIn::cls());
        module.types.push_back(&Textbox::cls());
        module.types.push_back(&StatSlider<float>::cls());
        module.types.push_back(&StatSlider<int>::cls());
        module.types.push_back(&Input<unsigned int>::cls());
        module.types.push_back(&Input<int>::cls());
        module.types.push_back(&Input<float>::cls());
        module.types.push_back(&Input<double>::cls());
        module.types.push_back(&Input<bool>::cls());
        module.types.push_back(&Input<string>::cls());
        module.types.push_back(&Input<toy::Colour>::cls());
        module.types.push_back(&Expandbox::cls());
        module.types.push_back(&TreeNode::cls());
        module.types.push_back(&Tree::cls());
        module.types.push_back(&Table::cls());
        module.types.push_back(&Tab::cls());
        module.types.push_back(&Tabber::cls());
        module.types.push_back(&Dir::cls());
        module.types.push_back(&File::cls());
        module.types.push_back(&Directory::cls());
        module.types.push_back(&FileBrowser::cls());
        module.types.push_back(&FileNode::cls());
        module.types.push_back(&DirectoryNode::cls());
        module.types.push_back(&Docksection::cls());
        module.types.push_back(&Dockline::cls());
        module.types.push_back(&Dockspace::cls());
        module.types.push_back(&WindowHeader::cls());
        module.types.push_back(&WindowSizer::cls());
        module.types.push_back(&WindowFooter::cls());
        module.types.push_back(&Window::cls());
        module.types.push_back(&Menu::cls());
        module.types.push_back(&Menubar::cls());
        module.types.push_back(&ToolButton::cls());
        module.types.push_back(&Tooldock::cls());
        module.types.push_back(&Toolbar::cls());
    
    }

}
#endif

#endif // TOYUI_IMPRINTS_H
