

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
    template <> TOY_UI_EXPORT Type& cls<Dimension>() { static Type ty("Dimension"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Direction>() { static Type ty("Direction"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Pivot>() { static Type ty("Pivot"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Align>() { static Type ty("Align"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<FrameType>() { static Type ty("FrameType"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<LayoutSolver>() { static Type ty("LayoutSolver"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<AutoLayout>() { static Type ty("AutoLayout"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Flow>() { static Type ty("Flow"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Sizing>() { static Type ty("Sizing"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<SpacePreset>() { static Type ty("SpacePreset"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Clipping>() { static Type ty("Clipping"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<Opacity>() { static Type ty("Opacity"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<WidgetState>() { static Type ty("WidgetState"); return ty; }
    template <> TOY_UI_EXPORT Type& cls<std::vector<Widget*>>() { static Type ty("std::vector<Widget*>"); return ty; }
    
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<ImageSkin>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<ImageSkin>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<LayoutStyle>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<LayoutStyle>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Style>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Style>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Widget>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Widget>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Wedge>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Wedge>>() { static Type ty; return ty; }
    



	void ImageSkin_d_image(Lref& object, Lref& val) { val.pointer<Image>() = object.ref<ImageSkin>().d_image; }
	void ImageSkin_setD_image(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_image = val.pointer<Image>(); }
	void ImageSkin_d_left(Lref& object, Lref& val) { val.value<int>() = object.ref<ImageSkin>().d_left; }
	void ImageSkin_setD_left(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_left = val.value<int>(); }
	void ImageSkin_d_top(Lref& object, Lref& val) { val.value<int>() = object.ref<ImageSkin>().d_top; }
	void ImageSkin_setD_top(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_top = val.value<int>(); }
	void ImageSkin_d_right(Lref& object, Lref& val) { val.value<int>() = object.ref<ImageSkin>().d_right; }
	void ImageSkin_setD_right(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_right = val.value<int>(); }
	void ImageSkin_d_bottom(Lref& object, Lref& val) { val.value<int>() = object.ref<ImageSkin>().d_bottom; }
	void ImageSkin_setD_bottom(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_bottom = val.value<int>(); }
	void ImageSkin_d_margin(Lref& object, Lref& val) { val.value<int>() = object.ref<ImageSkin>().d_margin; }
	void ImageSkin_setD_margin(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_margin = val.value<int>(); }
	void ImageSkin_d_stretch(Lref& object, Lref& val) { val.value<Dimension>() = object.ref<ImageSkin>().d_stretch; }
	void ImageSkin_setD_stretch(Lref& object, const Lref& val) { object.ref<ImageSkin>().d_stretch = val.value<Dimension>(); }



	void LayoutStyle_d_updated(Lref& object, Lref& val) { val.value<size_t>() = object.ref<LayoutStyle>().d_updated; }
	void LayoutStyle_setD_updated(Lref& object, const Lref& val) { object.ref<LayoutStyle>().d_updated = val.value<size_t>(); }

    void InkStyle_construct_0(Lref& ref, Lref* args) {  ref.value<InkStyle>() = InkStyle( args[0].pointer<Style>() ); }

	void Style_base(Lref& object, Lref& val) { val.pointer<Style>() = object.ref<Style>().m_base; }
	void Style_name(Lref& object, Lref& val) { val.value<string>() = object.ref<Style>().m_name; }
	void Style_layout(Lref& object, Lref& val) { val.value<LayoutStyle>() = object.ref<Style>().m_layout; }
	void Style_skin(Lref& object, Lref& val) { val.value<InkStyle>() = object.ref<Style>().m_skin; }


	void Widget_parent(Lref& object, Lref& val) { val.pointer<Wedge>() = object.ref<Widget>().m_parent; }
	void Widget_container(Lref& object, Lref& val) { val.pointer<Wedge>() = object.ref<Widget>().m_container; }
	void Widget_index(Lref& object, Lref& val) { val.value<size_t>() = object.ref<Widget>().m_index; }
	void Widget_style(Lref& object, Lref& val) { val.pointer<Style>() = object.ref<Widget>().m_style; }
	void Widget_setStyle(Lref& object, const Lref& val) { object.ref<Widget>().setStyle(val.pointer<Style>()); }
	void Widget_state(Lref& object, Lref& val) { val.value<WidgetState>() = object.ref<Widget>().m_state; }



	void Wedge_contents(Lref& object, Lref& val) { val.value<std::vector<Widget*>>() = object.ref<Wedge>().m_contents; }
















































    


    void toyuiCarbon(Module& module)
    {
        // Base Types
    
        // Enums
        cls<Dimension>().imprint().name = "Dimension";
        cls<Dimension>().imprint().typeClass = ENUM;
        cls<Dimension>().imprint().enumIds = { "DIM_X", "DIM_Y", "DIM_XX", "DIM_YY", "DIM_NULL" };
        cls<Dimension>().imprint().initRefMethods<Dimension>();
        cls<Dimension>().imprint().setup();
        
        cls<Direction>().imprint().name = "Direction";
        cls<Direction>().imprint().typeClass = ENUM;
        cls<Direction>().imprint().enumIds = { "DIRECTION_NONE", "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL" };
        cls<Direction>().imprint().initRefMethods<Direction>();
        cls<Direction>().imprint().setup();
        
        cls<Pivot>().imprint().name = "Pivot";
        cls<Pivot>().imprint().typeClass = ENUM;
        cls<Pivot>().imprint().enumIds = { "FORWARD", "REVERSE" };
        cls<Pivot>().imprint().initRefMethods<Pivot>();
        cls<Pivot>().imprint().setup();
        
        cls<Align>().imprint().name = "Align";
        cls<Align>().imprint().typeClass = ENUM;
        cls<Align>().imprint().enumIds = { "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" };
        cls<Align>().imprint().initRefMethods<Align>();
        cls<Align>().imprint().setup();
        
        cls<FrameType>().imprint().name = "FrameType";
        cls<FrameType>().imprint().typeClass = ENUM;
        cls<FrameType>().imprint().enumIds = { "FRAME", "LAYER", "MASTER_LAYER", "SPACE_LAYER" };
        cls<FrameType>().imprint().initRefMethods<FrameType>();
        cls<FrameType>().imprint().setup();
        
        cls<LayoutSolver>().imprint().name = "LayoutSolver";
        cls<LayoutSolver>().imprint().typeClass = ENUM;
        cls<LayoutSolver>().imprint().enumIds = { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" };
        cls<LayoutSolver>().imprint().initRefMethods<LayoutSolver>();
        cls<LayoutSolver>().imprint().setup();
        
        cls<AutoLayout>().imprint().name = "AutoLayout";
        cls<AutoLayout>().imprint().typeClass = ENUM;
        cls<AutoLayout>().imprint().enumIds = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" };
        cls<AutoLayout>().imprint().initRefMethods<AutoLayout>();
        cls<AutoLayout>().imprint().setup();
        
        cls<Flow>().imprint().name = "Flow";
        cls<Flow>().imprint().typeClass = ENUM;
        cls<Flow>().imprint().enumIds = { "FLOW", "OVERLAY", "ALIGN", "FREE" };
        cls<Flow>().imprint().initRefMethods<Flow>();
        cls<Flow>().imprint().setup();
        
        cls<Sizing>().imprint().name = "Sizing";
        cls<Sizing>().imprint().typeClass = ENUM;
        cls<Sizing>().imprint().enumIds = { "FIXED", "SHRINK", "WRAP", "EXPAND" };
        cls<Sizing>().imprint().initRefMethods<Sizing>();
        cls<Sizing>().imprint().setup();
        
        cls<SpacePreset>().imprint().name = "SpacePreset";
        cls<SpacePreset>().imprint().typeClass = ENUM;
        cls<SpacePreset>().imprint().enumIds = { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD" };
        cls<SpacePreset>().imprint().initRefMethods<SpacePreset>();
        cls<SpacePreset>().imprint().setup();
        
        cls<Clipping>().imprint().name = "Clipping";
        cls<Clipping>().imprint().typeClass = ENUM;
        cls<Clipping>().imprint().enumIds = { "NOCLIP", "CLIP" };
        cls<Clipping>().imprint().initRefMethods<Clipping>();
        cls<Clipping>().imprint().setup();
        
        cls<Opacity>().imprint().name = "Opacity";
        cls<Opacity>().imprint().typeClass = ENUM;
        cls<Opacity>().imprint().enumIds = { "OPAQUE", "CLEAR", "HOLLOW" };
        cls<Opacity>().imprint().initRefMethods<Opacity>();
        cls<Opacity>().imprint().setup();
        
        cls<WidgetState>().imprint().name = "WidgetState";
        cls<WidgetState>().imprint().typeClass = ENUM;
        cls<WidgetState>().imprint().enumIds = { "NOSTATE", "FOCUSED", "TRIGGERED", "ACTIVATED", "SELECTED", "DRAGGED", "DISABLED", "ACTIVE", "CONTROL", "MODAL" };
        cls<WidgetState>().imprint().initRefMethods<WidgetState>();
        cls<WidgetState>().imprint().setup();
        
    
        // Sequences
        cls<std::vector<Widget*>>().imprint().name = "std::vector<Widget*>";
        cls<std::vector<Widget*>>().imprint().typeClass = SEQUENCE;
        cls<std::vector<Widget*>>().imprint().initRefMethods<std::vector<Widget*>>();
        cls<std::vector<Widget*>>().imprint().initVector<Widget*>();
        cls<std::vector<Widget*>>().imprint().setup();
        
    
        // Stores
    
    
        // BoxFloat
        cls<BoxFloat>().imprint().inherit();
        cls<BoxFloat>().imprint().name = "BoxFloat";
        cls<BoxFloat>().imprint().typeClass = STRUCT;
        cls<BoxFloat>().imprint().serializable = false;
        cls<BoxFloat>().imprint().isTypeObject = false;
        cls<BoxFloat>().imprint().initRefMethods<BoxFloat>();
        cls<BoxFloat>().imprint().setup();
        
        
        // Image
        cls<Image>().imprint().inherit();
        cls<Image>().imprint().name = "Image";
        cls<Image>().imprint().typeClass = STRUCT;
        cls<Image>().imprint().serializable = false;
        cls<Image>().imprint().isTypeObject = false;
        cls<Image>().imprint().initRefMethods<Image>();
        cls<Image>().imprint().setup();
        
        
        // ImageSkin
        cls<ImageSkin>().imprint().inherit();
        cls<ImageSkin>().imprint().name = "ImageSkin";
        cls<ImageSkin>().imprint().typeClass = STRUCT;
        cls<ImageSkin>().imprint().serializable = false;
        cls<ImageSkin>().imprint().isTypeObject = false;
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_image), cls<Image>(), "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_left), cls<int>(), "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_top), cls<int>(), "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_right), cls<int>(), "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_bottom), cls<int>(), "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_margin), cls<int>(), "d_margin", &ImageSkin_d_margin, &ImageSkin_setD_margin, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().members.push_back(Member(cls<ImageSkin>(), member_var(&ImageSkin::d_stretch), cls<Dimension>(), "d_stretch", &ImageSkin_d_stretch, &ImageSkin_setD_stretch, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<ImageSkin>().imprint().initRefMethods<ImageSkin>();
        cls<ImageSkin>().imprint().setup();
        
        
        // Shadow
        cls<Shadow>().imprint().inherit();
        cls<Shadow>().imprint().name = "Shadow";
        cls<Shadow>().imprint().typeClass = STRUCT;
        cls<Shadow>().imprint().serializable = false;
        cls<Shadow>().imprint().isTypeObject = false;
        cls<Shadow>().imprint().initRefMethods<Shadow>();
        cls<Shadow>().imprint().setup();
        
        
        // Paint
        cls<Paint>().imprint().inherit();
        cls<Paint>().imprint().name = "Paint";
        cls<Paint>().imprint().typeClass = STRUCT;
        cls<Paint>().imprint().serializable = false;
        cls<Paint>().imprint().isTypeObject = false;
        cls<Paint>().imprint().initRefMethods<Paint>();
        cls<Paint>().imprint().setup();
        
        
        // LayoutStyle
        cls<LayoutStyle>().imprint().inherit();
        cls<LayoutStyle>().imprint().name = "LayoutStyle";
        cls<LayoutStyle>().imprint().typeClass = STRUCT;
        cls<LayoutStyle>().imprint().serializable = false;
        cls<LayoutStyle>().imprint().isTypeObject = false;
        cls<LayoutStyle>().imprint().members.push_back(Member(cls<LayoutStyle>(), member_var(&LayoutStyle::d_updated), cls<unsigned int>(), "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<LayoutStyle>().imprint().initRefMethods<LayoutStyle>();
        cls<LayoutStyle>().imprint().setup();
        
        
        // InkStyle
        cls<InkStyle>().imprint().inherit();
        cls<InkStyle>().imprint().name = "InkStyle";
        cls<InkStyle>().imprint().typeClass = STRUCT;
        cls<InkStyle>().imprint().serializable = false;
        cls<InkStyle>().imprint().isTypeObject = false;
        cls<InkStyle>().imprint().constructors.push_back(Constructor(cls<InkStyle>(), &InkStyle_construct_0, ParamVector({ Param("style", ref(cls<Style>()), true, INPUT_PARAM) })));
        cls<InkStyle>().imprint().initRefMethods<InkStyle>();
        cls<InkStyle>().imprint().setup();
        
        
        // Style
        cls<Style>().imprint().inherit();
        cls<Style>().imprint().name = "Style";
        cls<Style>().imprint().typeClass = OBJECT;
        cls<Style>().imprint().serializable = false;
        cls<Style>().imprint().isTypeObject = true;
        cls<Style>().imprint().members.push_back(Member(cls<Style>(), member_var(&Style::m_base), cls<Style>(), "base", &Style_base, nullptr, MEMBER_VALUE));
        cls<Style>().imprint().members.push_back(Member(cls<Style>(), member_var(&Style::m_name), cls<string>(), "name", &Style_name, nullptr, MEMBER_VALUE));
        cls<Style>().imprint().members.push_back(Member(cls<Style>(), member_var(&Style::m_layout), cls<LayoutStyle>(), "layout", &Style_layout, nullptr, MEMBER_VALUE));
        cls<Style>().imprint().members.push_back(Member(cls<Style>(), member_var(&Style::m_skin), cls<InkStyle>(), "skin", &Style_skin, nullptr, MEMBER_VALUE));
        cls<Style>().imprint().setup();
        
        
        // Frame
        cls<Frame>().imprint().inherit();
        cls<Frame>().imprint().name = "Frame";
        cls<Frame>().imprint().typeClass = OBJECT;
        cls<Frame>().imprint().serializable = false;
        cls<Frame>().imprint().isTypeObject = false;
        cls<Frame>().imprint().setup();
        
        
        // Widget
        cls<Widget>().imprint().inherit();
        cls<Widget>().imprint().name = "Widget";
        cls<Widget>().imprint().typeClass = OBJECT;
        cls<Widget>().imprint().serializable = false;
        cls<Widget>().imprint().isTypeObject = true;
        cls<Widget>().imprint().members.push_back(Member(cls<Widget>(), member_var(&Widget::m_parent), cls<Wedge>(), "parent", &Widget_parent, nullptr, MEMBER_VALUE));
        cls<Widget>().imprint().members.push_back(Member(cls<Widget>(), member_var(&Widget::m_container), cls<Wedge>(), "container", &Widget_container, nullptr, MEMBER_VALUE));
        cls<Widget>().imprint().members.push_back(Member(cls<Widget>(), member_var(&Widget::m_index), cls<unsigned int>(), "index", &Widget_index, nullptr, MEMBER_VALUE));
        cls<Widget>().imprint().members.push_back(Member(cls<Widget>(), member_var(&Widget::m_style), cls<Style>(), "style", &Widget_style, &Widget_setStyle, MEMBER_VALUE|MEMBER_MUTABLE));
        cls<Widget>().imprint().members.push_back(Member(cls<Widget>(), member_var(&Widget::m_state), cls<WidgetState>(), "state", &Widget_state, nullptr, MEMBER_VALUE));
        cls<Widget>().imprint().setup();
        
        
        // RenderSystem
        cls<RenderSystem>().imprint().inherit();
        cls<RenderSystem>().imprint().name = "RenderSystem";
        cls<RenderSystem>().imprint().typeClass = OBJECT;
        cls<RenderSystem>().imprint().serializable = false;
        cls<RenderSystem>().imprint().isTypeObject = false;
        cls<RenderSystem>().imprint().setup();
        
        
        // Item
        cls<Item>().imprint().inherit();
        cls<Item>().imprint().name = "Item";
        cls<Item>().imprint().typeClass = OBJECT;
        cls<Item>().imprint().serializable = false;
        cls<Item>().imprint().isTypeObject = false;
        cls<Item>().imprint().setup();
        
        
        // Wedge
        cls<Wedge>().imprint().inherit();
        cls<Wedge>().imprint().name = "Wedge";
        cls<Wedge>().imprint().typeClass = OBJECT;
        cls<Wedge>().imprint().serializable = false;
        cls<Wedge>().imprint().isTypeObject = false;
        cls<Wedge>().imprint().members.push_back(Member(cls<Wedge>(), member_var(&Wedge::m_contents), cls<std::vector<Widget*>>(), "contents", &Wedge_contents, nullptr, MEMBER_VALUE|MEMBER_STRUCTURE));
        cls<Wedge>().imprint().setup();
        
        
        // GridSheet
        cls<GridSheet>().imprint().inherit();
        cls<GridSheet>().imprint().name = "GridSheet";
        cls<GridSheet>().imprint().typeClass = OBJECT;
        cls<GridSheet>().imprint().serializable = false;
        cls<GridSheet>().imprint().isTypeObject = false;
        cls<GridSheet>().imprint().setup();
        
        
        // Tooltip
        cls<Tooltip>().imprint().inherit();
        cls<Tooltip>().imprint().name = "Tooltip";
        cls<Tooltip>().imprint().typeClass = OBJECT;
        cls<Tooltip>().imprint().serializable = false;
        cls<Tooltip>().imprint().isTypeObject = false;
        cls<Tooltip>().imprint().setup();
        
        
        // Rectangle
        cls<Rectangle>().imprint().inherit();
        cls<Rectangle>().imprint().name = "Rectangle";
        cls<Rectangle>().imprint().typeClass = OBJECT;
        cls<Rectangle>().imprint().serializable = false;
        cls<Rectangle>().imprint().isTypeObject = false;
        cls<Rectangle>().imprint().setup();
        
        
        // Cursor
        cls<Cursor>().imprint().inherit();
        cls<Cursor>().imprint().name = "Cursor";
        cls<Cursor>().imprint().typeClass = OBJECT;
        cls<Cursor>().imprint().serializable = false;
        cls<Cursor>().imprint().isTypeObject = false;
        cls<Cursor>().imprint().setup();
        
        
        // RootSheet
        cls<RootSheet>().imprint().inherit();
        cls<RootSheet>().imprint().name = "RootSheet";
        cls<RootSheet>().imprint().typeClass = OBJECT;
        cls<RootSheet>().imprint().serializable = false;
        cls<RootSheet>().imprint().isTypeObject = false;
        cls<RootSheet>().imprint().setup();
        
        
        // Label
        cls<Label>().imprint().inherit();
        cls<Label>().imprint().name = "Label";
        cls<Label>().imprint().typeClass = OBJECT;
        cls<Label>().imprint().serializable = false;
        cls<Label>().imprint().isTypeObject = false;
        cls<Label>().imprint().setup();
        
        
        // Button
        cls<Button>().imprint().inherit();
        cls<Button>().imprint().name = "Button";
        cls<Button>().imprint().typeClass = OBJECT;
        cls<Button>().imprint().serializable = false;
        cls<Button>().imprint().isTypeObject = false;
        cls<Button>().imprint().setup();
        
        
        // WrapButton
        cls<WrapButton>().imprint().inherit();
        cls<WrapButton>().imprint().name = "WrapButton";
        cls<WrapButton>().imprint().typeClass = OBJECT;
        cls<WrapButton>().imprint().serializable = false;
        cls<WrapButton>().imprint().isTypeObject = false;
        cls<WrapButton>().imprint().setup();
        
        
        // Toggle
        cls<Toggle>().imprint().inherit();
        cls<Toggle>().imprint().name = "Toggle";
        cls<Toggle>().imprint().typeClass = OBJECT;
        cls<Toggle>().imprint().serializable = false;
        cls<Toggle>().imprint().isTypeObject = false;
        cls<Toggle>().imprint().setup();
        
        
        // Slider
        cls<Slider>().imprint().inherit();
        cls<Slider>().imprint().name = "Slider";
        cls<Slider>().imprint().typeClass = OBJECT;
        cls<Slider>().imprint().serializable = false;
        cls<Slider>().imprint().isTypeObject = false;
        cls<Slider>().imprint().setup();
        
        
        // Scrollbar
        cls<Scrollbar>().imprint().inherit();
        cls<Scrollbar>().imprint().name = "Scrollbar";
        cls<Scrollbar>().imprint().typeClass = OBJECT;
        cls<Scrollbar>().imprint().serializable = false;
        cls<Scrollbar>().imprint().isTypeObject = false;
        cls<Scrollbar>().imprint().setup();
        
        
        // ScrollSheet
        cls<ScrollSheet>().imprint().inherit();
        cls<ScrollSheet>().imprint().name = "ScrollSheet";
        cls<ScrollSheet>().imprint().typeClass = OBJECT;
        cls<ScrollSheet>().imprint().serializable = false;
        cls<ScrollSheet>().imprint().isTypeObject = false;
        cls<ScrollSheet>().imprint().setup();
        
        
        // TypeIn
        cls<TypeIn>().imprint().inherit();
        cls<TypeIn>().imprint().name = "TypeIn";
        cls<TypeIn>().imprint().typeClass = OBJECT;
        cls<TypeIn>().imprint().serializable = false;
        cls<TypeIn>().imprint().isTypeObject = false;
        cls<TypeIn>().imprint().setup();
        
        
        // Input<bool>
        cls<Input<bool>>().imprint().inherit();
        cls<Input<bool>>().imprint().name = "Input<bool>";
        cls<Input<bool>>().imprint().typeClass = OBJECT;
        cls<Input<bool>>().imprint().serializable = false;
        cls<Input<bool>>().imprint().isTypeObject = false;
        cls<Input<bool>>().imprint().setup();
        
        
        // Input<toy::Colour>
        cls<Input<toy::Colour>>().imprint().inherit();
        cls<Input<toy::Colour>>().imprint().name = "Input<toy::Colour>";
        cls<Input<toy::Colour>>().imprint().typeClass = OBJECT;
        cls<Input<toy::Colour>>().imprint().serializable = false;
        cls<Input<toy::Colour>>().imprint().isTypeObject = false;
        cls<Input<toy::Colour>>().imprint().setup();
        
        
        // Expandbox
        cls<Expandbox>().imprint().inherit();
        cls<Expandbox>().imprint().name = "Expandbox";
        cls<Expandbox>().imprint().typeClass = OBJECT;
        cls<Expandbox>().imprint().serializable = false;
        cls<Expandbox>().imprint().isTypeObject = false;
        cls<Expandbox>().imprint().setup();
        
        
        // Tree
        cls<Tree>().imprint().inherit();
        cls<Tree>().imprint().name = "Tree";
        cls<Tree>().imprint().typeClass = OBJECT;
        cls<Tree>().imprint().serializable = false;
        cls<Tree>().imprint().isTypeObject = false;
        cls<Tree>().imprint().setup();
        
        
        // Table
        cls<Table>().imprint().inherit();
        cls<Table>().imprint().name = "Table";
        cls<Table>().imprint().typeClass = OBJECT;
        cls<Table>().imprint().serializable = false;
        cls<Table>().imprint().isTypeObject = false;
        cls<Table>().imprint().setup();
        
        
        // Tab
        cls<Tab>().imprint().inherit();
        cls<Tab>().imprint().name = "Tab";
        cls<Tab>().imprint().typeClass = OBJECT;
        cls<Tab>().imprint().serializable = false;
        cls<Tab>().imprint().isTypeObject = false;
        cls<Tab>().imprint().setup();
        
        
        // Tabber
        cls<Tabber>().imprint().inherit();
        cls<Tabber>().imprint().name = "Tabber";
        cls<Tabber>().imprint().typeClass = OBJECT;
        cls<Tabber>().imprint().serializable = false;
        cls<Tabber>().imprint().isTypeObject = false;
        cls<Tabber>().imprint().setup();
        
        
        // Directory
        cls<Directory>().imprint().inherit();
        cls<Directory>().imprint().name = "Directory";
        cls<Directory>().imprint().typeClass = OBJECT;
        cls<Directory>().imprint().serializable = false;
        cls<Directory>().imprint().isTypeObject = false;
        cls<Directory>().imprint().setup();
        
        
        // FileBrowser
        cls<FileBrowser>().imprint().inherit();
        cls<FileBrowser>().imprint().name = "FileBrowser";
        cls<FileBrowser>().imprint().typeClass = OBJECT;
        cls<FileBrowser>().imprint().serializable = false;
        cls<FileBrowser>().imprint().isTypeObject = false;
        cls<FileBrowser>().imprint().setup();
        
        
        // Dockspace
        cls<Dockspace>().imprint().inherit();
        cls<Dockspace>().imprint().name = "Dockspace";
        cls<Dockspace>().imprint().typeClass = OBJECT;
        cls<Dockspace>().imprint().serializable = false;
        cls<Dockspace>().imprint().isTypeObject = false;
        cls<Dockspace>().imprint().setup();
        
        
        // WindowHeader
        cls<WindowHeader>().imprint().inherit();
        cls<WindowHeader>().imprint().name = "WindowHeader";
        cls<WindowHeader>().imprint().typeClass = OBJECT;
        cls<WindowHeader>().imprint().serializable = false;
        cls<WindowHeader>().imprint().isTypeObject = false;
        cls<WindowHeader>().imprint().setup();
        
        
        // WindowSizer
        cls<WindowSizer>().imprint().inherit();
        cls<WindowSizer>().imprint().name = "WindowSizer";
        cls<WindowSizer>().imprint().typeClass = OBJECT;
        cls<WindowSizer>().imprint().serializable = false;
        cls<WindowSizer>().imprint().isTypeObject = false;
        cls<WindowSizer>().imprint().setup();
        
        
        // WindowFooter
        cls<WindowFooter>().imprint().inherit();
        cls<WindowFooter>().imprint().name = "WindowFooter";
        cls<WindowFooter>().imprint().typeClass = OBJECT;
        cls<WindowFooter>().imprint().serializable = false;
        cls<WindowFooter>().imprint().isTypeObject = false;
        cls<WindowFooter>().imprint().setup();
        
        
        // Window
        cls<Window>().imprint().inherit();
        cls<Window>().imprint().name = "Window";
        cls<Window>().imprint().typeClass = OBJECT;
        cls<Window>().imprint().serializable = false;
        cls<Window>().imprint().isTypeObject = false;
        cls<Window>().imprint().setup();
        
        
        // Menubar
        cls<Menubar>().imprint().inherit();
        cls<Menubar>().imprint().name = "Menubar";
        cls<Menubar>().imprint().typeClass = OBJECT;
        cls<Menubar>().imprint().serializable = false;
        cls<Menubar>().imprint().isTypeObject = false;
        cls<Menubar>().imprint().setup();
        
        
        // Tooldock
        cls<Tooldock>().imprint().inherit();
        cls<Tooldock>().imprint().name = "Tooldock";
        cls<Tooldock>().imprint().typeClass = OBJECT;
        cls<Tooldock>().imprint().serializable = false;
        cls<Tooldock>().imprint().isTypeObject = false;
        cls<Tooldock>().imprint().setup();
        
        
        // Toolbar
        cls<Toolbar>().imprint().inherit();
        cls<Toolbar>().imprint().name = "Toolbar";
        cls<Toolbar>().imprint().typeClass = OBJECT;
        cls<Toolbar>().imprint().serializable = false;
        cls<Toolbar>().imprint().isTypeObject = false;
        cls<Toolbar>().imprint().setup();
        
        
        // MultiButton
        cls<MultiButton>().imprint().inherit();
        cls<MultiButton>().imprint().name = "MultiButton";
        cls<MultiButton>().imprint().typeClass = OBJECT;
        cls<MultiButton>().imprint().serializable = false;
        cls<MultiButton>().imprint().isTypeObject = false;
        cls<MultiButton>().imprint().setup();
        
        
        // Checkbox
        cls<Checkbox>().imprint().inherit();
        cls<Checkbox>().imprint().name = "Checkbox";
        cls<Checkbox>().imprint().typeClass = OBJECT;
        cls<Checkbox>().imprint().serializable = false;
        cls<Checkbox>().imprint().isTypeObject = false;
        cls<Checkbox>().imprint().setup();
        
        
        // ScrollPlan
        cls<ScrollPlan>().imprint().inherit();
        cls<ScrollPlan>().imprint().name = "ScrollPlan";
        cls<ScrollPlan>().imprint().typeClass = OBJECT;
        cls<ScrollPlan>().imprint().serializable = false;
        cls<ScrollPlan>().imprint().isTypeObject = false;
        cls<ScrollPlan>().imprint().setup();
        
        
        // SelectList
        cls<SelectList>().imprint().inherit();
        cls<SelectList>().imprint().name = "SelectList";
        cls<SelectList>().imprint().typeClass = OBJECT;
        cls<SelectList>().imprint().serializable = false;
        cls<SelectList>().imprint().isTypeObject = false;
        cls<SelectList>().imprint().setup();
        
        
        // Dropdown
        cls<Dropdown>().imprint().inherit();
        cls<Dropdown>().imprint().name = "Dropdown";
        cls<Dropdown>().imprint().typeClass = OBJECT;
        cls<Dropdown>().imprint().serializable = false;
        cls<Dropdown>().imprint().isTypeObject = false;
        cls<Dropdown>().imprint().setup();
        
        
        // Textbox
        cls<Textbox>().imprint().inherit();
        cls<Textbox>().imprint().name = "Textbox";
        cls<Textbox>().imprint().typeClass = OBJECT;
        cls<Textbox>().imprint().serializable = false;
        cls<Textbox>().imprint().isTypeObject = false;
        cls<Textbox>().imprint().setup();
        
        
        // Input<string>
        cls<Input<string>>().imprint().inherit();
        cls<Input<string>>().imprint().name = "Input<string>";
        cls<Input<string>>().imprint().typeClass = OBJECT;
        cls<Input<string>>().imprint().serializable = false;
        cls<Input<string>>().imprint().isTypeObject = false;
        cls<Input<string>>().imprint().setup();
        
        
        // TreeNode
        cls<TreeNode>().imprint().inherit();
        cls<TreeNode>().imprint().name = "TreeNode";
        cls<TreeNode>().imprint().typeClass = OBJECT;
        cls<TreeNode>().imprint().serializable = false;
        cls<TreeNode>().imprint().isTypeObject = false;
        cls<TreeNode>().imprint().setup();
        
        
        // Docksection
        cls<Docksection>().imprint().inherit();
        cls<Docksection>().imprint().name = "Docksection";
        cls<Docksection>().imprint().typeClass = OBJECT;
        cls<Docksection>().imprint().serializable = false;
        cls<Docksection>().imprint().isTypeObject = false;
        cls<Docksection>().imprint().setup();
        
        
        // Dockline
        cls<Dockline>().imprint().inherit();
        cls<Dockline>().imprint().name = "Dockline";
        cls<Dockline>().imprint().typeClass = OBJECT;
        cls<Dockline>().imprint().serializable = false;
        cls<Dockline>().imprint().isTypeObject = false;
        cls<Dockline>().imprint().setup();
        
        
        // DropdownInput
        cls<DropdownInput>().imprint().inherit();
        cls<DropdownInput>().imprint().name = "DropdownInput";
        cls<DropdownInput>().imprint().typeClass = OBJECT;
        cls<DropdownInput>().imprint().serializable = false;
        cls<DropdownInput>().imprint().isTypeObject = false;
        cls<DropdownInput>().imprint().setup();
        
        
        // Dir
        cls<Dir>().imprint().inherit();
        cls<Dir>().imprint().name = "Dir";
        cls<Dir>().imprint().typeClass = OBJECT;
        cls<Dir>().imprint().serializable = false;
        cls<Dir>().imprint().isTypeObject = false;
        cls<Dir>().imprint().setup();
        
        
        // File
        cls<File>().imprint().inherit();
        cls<File>().imprint().name = "File";
        cls<File>().imprint().typeClass = OBJECT;
        cls<File>().imprint().serializable = false;
        cls<File>().imprint().isTypeObject = false;
        cls<File>().imprint().setup();
        
        
        // FileNode
        cls<FileNode>().imprint().inherit();
        cls<FileNode>().imprint().name = "FileNode";
        cls<FileNode>().imprint().typeClass = OBJECT;
        cls<FileNode>().imprint().serializable = false;
        cls<FileNode>().imprint().isTypeObject = false;
        cls<FileNode>().imprint().setup();
        
        
        // DirectoryNode
        cls<DirectoryNode>().imprint().inherit();
        cls<DirectoryNode>().imprint().name = "DirectoryNode";
        cls<DirectoryNode>().imprint().typeClass = OBJECT;
        cls<DirectoryNode>().imprint().serializable = false;
        cls<DirectoryNode>().imprint().isTypeObject = false;
        cls<DirectoryNode>().imprint().setup();
        
        
        // Menu
        cls<Menu>().imprint().inherit();
        cls<Menu>().imprint().name = "Menu";
        cls<Menu>().imprint().typeClass = OBJECT;
        cls<Menu>().imprint().serializable = false;
        cls<Menu>().imprint().isTypeObject = false;
        cls<Menu>().imprint().setup();
        
        
        // ToolButton
        cls<ToolButton>().imprint().inherit();
        cls<ToolButton>().imprint().name = "ToolButton";
        cls<ToolButton>().imprint().typeClass = OBJECT;
        cls<ToolButton>().imprint().serializable = false;
        cls<ToolButton>().imprint().isTypeObject = false;
        cls<ToolButton>().imprint().setup();
        
        
        
        module.types.push_back(&cls<Dimension>());
        module.types.push_back(&cls<Direction>());
        module.types.push_back(&cls<Pivot>());
        module.types.push_back(&cls<Align>());
        module.types.push_back(&cls<FrameType>());
        module.types.push_back(&cls<LayoutSolver>());
        module.types.push_back(&cls<AutoLayout>());
        module.types.push_back(&cls<Flow>());
        module.types.push_back(&cls<Sizing>());
        module.types.push_back(&cls<SpacePreset>());
        module.types.push_back(&cls<Clipping>());
        module.types.push_back(&cls<Opacity>());
        module.types.push_back(&cls<BoxFloat>());
        module.types.push_back(&cls<Image>());
        module.types.push_back(&cls<ImageSkin>());
        module.types.push_back(&cls<Shadow>());
        module.types.push_back(&cls<Paint>());
        module.types.push_back(&cls<LayoutStyle>());
        module.types.push_back(&cls<InkStyle>());
        module.types.push_back(&cls<Style>());
        module.types.push_back(&cls<Frame>());
        module.types.push_back(&cls<WidgetState>());
        module.types.push_back(&cls<Widget>());
        module.types.push_back(&cls<Item>());
        module.types.push_back(&cls<Wedge>());
        module.types.push_back(&cls<std::vector<Widget*>>());
        module.types.push_back(&cls<GridSheet>());
        module.types.push_back(&cls<Tooltip>());
        module.types.push_back(&cls<Rectangle>());
        module.types.push_back(&cls<Cursor>());
        module.types.push_back(&cls<RootSheet>());
        module.types.push_back(&cls<Label>());
        module.types.push_back(&cls<Button>());
        module.types.push_back(&cls<WrapButton>());
        module.types.push_back(&cls<MultiButton>());
        module.types.push_back(&cls<Toggle>());
        module.types.push_back(&cls<Slider>());
        module.types.push_back(&cls<Scrollbar>());
        module.types.push_back(&cls<Checkbox>());
        module.types.push_back(&cls<ScrollSheet>());
        module.types.push_back(&cls<ScrollPlan>());
        module.types.push_back(&cls<SelectList>());
        module.types.push_back(&cls<Dropdown>());
        module.types.push_back(&cls<DropdownInput>());
        module.types.push_back(&cls<TypeIn>());
        module.types.push_back(&cls<Textbox>());
        module.types.push_back(&cls<Input<bool>>());
        module.types.push_back(&cls<Input<string>>());
        module.types.push_back(&cls<Input<toy::Colour>>());
        module.types.push_back(&cls<Expandbox>());
        module.types.push_back(&cls<TreeNode>());
        module.types.push_back(&cls<Tree>());
        module.types.push_back(&cls<Table>());
        module.types.push_back(&cls<Tab>());
        module.types.push_back(&cls<Tabber>());
        module.types.push_back(&cls<Dir>());
        module.types.push_back(&cls<File>());
        module.types.push_back(&cls<Directory>());
        module.types.push_back(&cls<FileBrowser>());
        module.types.push_back(&cls<FileNode>());
        module.types.push_back(&cls<DirectoryNode>());
        module.types.push_back(&cls<Docksection>());
        module.types.push_back(&cls<Dockline>());
        module.types.push_back(&cls<Dockspace>());
        module.types.push_back(&cls<WindowHeader>());
        module.types.push_back(&cls<WindowSizer>());
        module.types.push_back(&cls<WindowFooter>());
        module.types.push_back(&cls<Window>());
        module.types.push_back(&cls<Menu>());
        module.types.push_back(&cls<Menubar>());
        module.types.push_back(&cls<ToolButton>());
        module.types.push_back(&cls<Tooldock>());
        module.types.push_back(&cls<Toolbar>());
        module.types.push_back(&cls<RenderSystem>());
    
    }

}
#endif

#endif // TOYUI_IMPRINTS_H
