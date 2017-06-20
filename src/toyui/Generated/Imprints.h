

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
    template <> TOY_UI_EXPORT Type& typecls<AutoLayout>() { static Type ty("AutoLayout"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Flow>() { static Type ty("Flow"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Sizing>() { static Type ty("Sizing"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Space>() { static Type ty("Space"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Clipping>() { static Type ty("Clipping"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<Opacity>() { static Type ty("Opacity"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<WidgetState>() { static Type ty("WidgetState"); return ty; }
    template <> TOY_UI_EXPORT Type& typecls<std::vector<Widget*>>() { static Type ty("std::vector<Widget*>"); return ty; }
    
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<BoxFloat>>() { static Type ty; return ty; }
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<BoxFloat>>() { static Type ty; return ty; }
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
    









    Object& BoxFloat_construct_0(Lref& ref, Lref* args) {  ref.value<BoxFloat>() = BoxFloat( args[0].any<float>(), args[1].any<float>(), args[2].any<float>(), args[3].any<float>() ); return ref.value<BoxFloat>(); }
	void BoxFloat_x0(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().x0(); }
	void BoxFloat_setX0(Object& object, const Lref& ref) { object.as<BoxFloat>().setX0(ref.value<float>()); }
	void BoxFloat_y0(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().y0(); }
	void BoxFloat_setY0(Object& object, const Lref& ref) { object.as<BoxFloat>().setY0(ref.value<float>()); }
	void BoxFloat_x1(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().x1(); }
	void BoxFloat_setX1(Object& object, const Lref& ref) { object.as<BoxFloat>().setX1(ref.value<float>()); }
	void BoxFloat_y1(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().y1(); }
	void BoxFloat_setY1(Object& object, const Lref& ref) { object.as<BoxFloat>().setY1(ref.value<float>()); }
	void BoxFloat_x(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().x(); }
	void BoxFloat_y(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().y(); }
	void BoxFloat_w(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().w(); }
	void BoxFloat_h(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().h(); }
	void BoxFloat_v0(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().v0(); }
	void BoxFloat_v1(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().v1(); }
	void BoxFloat_v2(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().v2(); }
	void BoxFloat_v3(Object& object, Lref& ref) { ref.value<float>() = object.as<BoxFloat>().v3(); }

	void ImageSkin_d_image(Object& object, Lref& ref) { ref.pointer<Image>() = object.as<ImageSkin>().d_image; }
	void ImageSkin_setD_image(Object& object, const Lref& ref) { object.as<ImageSkin>().d_image = ref.pointer<Image>(); }
	void ImageSkin_d_filetype(Object& object, Lref& ref) { ref.value<string>() = object.as<ImageSkin>().d_filetype; }
	void ImageSkin_setD_filetype(Object& object, const Lref& ref) { object.as<ImageSkin>().d_filetype = ref.value<string>(); }
	void ImageSkin_d_top(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_top; }
	void ImageSkin_setD_top(Object& object, const Lref& ref) { object.as<ImageSkin>().d_top = ref.value<int>(); }
	void ImageSkin_d_right(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_right; }
	void ImageSkin_setD_right(Object& object, const Lref& ref) { object.as<ImageSkin>().d_right = ref.value<int>(); }
	void ImageSkin_d_bottom(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_bottom; }
	void ImageSkin_setD_bottom(Object& object, const Lref& ref) { object.as<ImageSkin>().d_bottom = ref.value<int>(); }
	void ImageSkin_d_left(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_left; }
	void ImageSkin_setD_left(Object& object, const Lref& ref) { object.as<ImageSkin>().d_left = ref.value<int>(); }
	void ImageSkin_d_margin(Object& object, Lref& ref) { ref.value<int>() = object.as<ImageSkin>().d_margin; }
	void ImageSkin_setD_margin(Object& object, const Lref& ref) { object.as<ImageSkin>().d_margin = ref.value<int>(); }
	void ImageSkin_d_stretch(Object& object, Lref& ref) { ref.value<Dimension>() = object.as<ImageSkin>().d_stretch; }
	void ImageSkin_setD_stretch(Object& object, const Lref& ref) { object.as<ImageSkin>().d_stretch = ref.value<Dimension>(); }



	void LayoutStyle_d_updated(Object& object, Lref& ref) { ref.value<size_t>() = object.as<LayoutStyle>().d_updated; }
	void LayoutStyle_setD_updated(Object& object, const Lref& ref) { object.as<LayoutStyle>().d_updated = ref.value<size_t>(); }

    Object& InkStyle_construct_0(Lref& ref, Lref* args) {  ref.value<InkStyle>() = InkStyle( args[0].pointer<Style>() ); return ref.value<InkStyle>(); }

	void Style_name(Object& object, Lref& ref) { ref.value<string>() = object.as<Style>().name(); }
	void Style_base(Object& object, Lref& ref) { ref.pointer<Style>() = object.as<Style>().base(); }
	void Style_layout(Object& object, Lref& ref) { ref.pointer<LayoutStyle>() = &object.as<Style>().layout(); }
	void Style_skin(Object& object, Lref& ref) { ref.pointer<InkStyle>() = &object.as<Style>().skin(); }
	void Style_updated(Object& object, Lref& ref) { ref.value<size_t>() = object.as<Style>().updated(); }
	void Style_setUpdated(Object& object, const Lref& ref) { object.as<Style>().setUpdated(ref.value<size_t>()); }

	void Widget_parent(Object& object, Lref& ref) { ref.pointer<Wedge>() = object.as<Widget>().parent(); }
	void Widget_container(Object& object, Lref& ref) { ref.pointer<Container>() = object.as<Widget>().container(); }
	void Widget_index(Object& object, Lref& ref) { ref.value<size_t>() = object.as<Widget>().index(); }
	void Widget_frame(Object& object, Lref& ref) { ref.pointer<Frame>() = &object.as<Widget>().frame(); }
	void Widget_state(Object& object, Lref& ref) { ref.value<WidgetState>() = object.as<Widget>().state(); }
	void Widget_style(Object& object, Lref& ref) { ref.pointer<Style>() = &object.as<Widget>().style(); }
	void Widget_setStyle(Object& object, const Lref& ref) { object.as<Widget>().setStyle(ref.ref<Style>()); }
	void Widget_label(Object& object, Lref& ref) { ref.value<string>() = object.as<Widget>().label(); }
	void Widget_setLabel(Object& object, const Lref& ref) { object.as<Widget>().setLabel(ref.value<string>()); }
	void Widget_image(Object& object, Lref& ref) { ref.pointer<Image>() = object.as<Widget>().image(); }
	void Widget_setImage(Object& object, const Lref& ref) { object.as<Widget>().setImage(ref.pointer<Image>()); }


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
        typecls<Direction>().imprint().enumIds = { "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "DIMENSION", "DIRECTION_AUTO" };
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
        typecls<FrameType>().imprint().enumIds = { "FRAME", "STRIPE", "GRID", "TABLE", "LAYER", "MASTER_LAYER", "SPACE_LAYER" };
        typecls<FrameType>().imprint().initRefMethods<FrameType>();
        typecls<FrameType>().imprint().setup();
        
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
        typecls<Sizing>().imprint().enumIds = { "FIXED", "MANUAL", "SHRINK", "WRAP", "EXPAND" };
        typecls<Sizing>().imprint().initRefMethods<Sizing>();
        typecls<Sizing>().imprint().setup();
        
        typecls<Space>().imprint().name = "Space";
        typecls<Space>().imprint().typeClass = ENUM;
        typecls<Space>().imprint().enumIds = { "MANUAL_SPACE", "SHEET", "ITEM", "BLOCK", "FIXED_BLOCK", "LINE", "STACK", "DIV", "SPACE", "BOARD", "PARALLEL_FLEX" };
        typecls<Space>().imprint().initRefMethods<Space>();
        typecls<Space>().imprint().setup();
        
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
    
    
        // Image
        Image::cls().imprint().inherit();
        Image::cls().imprint().name = "Image";
        Image::cls().imprint().typeClass = STRUCT;
        Image::cls().imprint().serializable = false;
        Image::cls().imprint().isTypeObject = false;
        Image::cls().imprint().initRefMethods<Image>();
        Image::cls().imprint().setup();
        
        
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
        
        
        // Frame
        Frame::cls().imprint().inherit();
        Frame::cls().imprint().name = "Frame";
        Frame::cls().imprint().typeClass = OBJECT;
        Frame::cls().imprint().serializable = false;
        Frame::cls().imprint().isTypeObject = false;
        Frame::cls().imprint().setup();
        
        
        // BoxFloat
        BoxFloat::cls().imprint().inherit();
        BoxFloat::cls().imprint().name = "BoxFloat";
        BoxFloat::cls().imprint().typeClass = STRUCT;
        BoxFloat::cls().imprint().serializable = false;
        BoxFloat::cls().imprint().isTypeObject = false;
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::x0), typecls<float>(), "x0", &BoxFloat_x0, &BoxFloat_setX0, true, true, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::y0), typecls<float>(), "y0", &BoxFloat_y0, &BoxFloat_setY0, true, true, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::x1), typecls<float>(), "x1", &BoxFloat_x1, &BoxFloat_setX1, true, true, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::y1), typecls<float>(), "y1", &BoxFloat_y1, &BoxFloat_setY1, true, true, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::x), typecls<float>(), "x", &BoxFloat_x, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::y), typecls<float>(), "y", &BoxFloat_y, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::w), typecls<float>(), "w", &BoxFloat_w, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::h), typecls<float>(), "h", &BoxFloat_h, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::v0), typecls<float>(), "v0", &BoxFloat_v0, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::v1), typecls<float>(), "v1", &BoxFloat_v1, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::v2), typecls<float>(), "v2", &BoxFloat_v2, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().members.push_back(Member(BoxFloat::cls(), method_var(&BoxFloat::v3), typecls<float>(), "v3", &BoxFloat_v3, nullptr, true, false, false, false));
        BoxFloat::cls().imprint().constructors.push_back(Constructor(BoxFloat::cls(), &BoxFloat_construct_0, ParamVector({ Param("x0", var(float()), false, INPUT_PARAM), Param("y0", var(float()), false, INPUT_PARAM), Param("x1", var(float()), false, INPUT_PARAM), Param("y1", var(float()), false, INPUT_PARAM) })));
        BoxFloat::cls().imprint().initRefMethods<BoxFloat>();
        BoxFloat::cls().imprint().setup();
        
        
        // ImageSkin
        ImageSkin::cls().imprint().inherit();
        ImageSkin::cls().imprint().name = "ImageSkin";
        ImageSkin::cls().imprint().typeClass = STRUCT;
        ImageSkin::cls().imprint().serializable = false;
        ImageSkin::cls().imprint().isTypeObject = false;
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_image), Image::cls(), "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_filetype), typecls<string>(), "d_filetype", &ImageSkin_d_filetype, &ImageSkin_setD_filetype, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_top), typecls<int>(), "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_right), typecls<int>(), "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_bottom), typecls<int>(), "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, true, true, false, false));
        ImageSkin::cls().imprint().members.push_back(Member(ImageSkin::cls(), member_var(&ImageSkin::d_left), typecls<int>(), "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, true, true, false, false));
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
        Style::cls().imprint().members.push_back(Member(Style::cls(), method_var(&Style::name), typecls<string>(), "name", &Style_name, nullptr, true, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), method_var(&Style::base), Style::cls(), "base", &Style_base, nullptr, true, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), method_var(&Style::layout), LayoutStyle::cls(), "layout", &Style_layout, nullptr, false, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), method_var(&Style::skin), InkStyle::cls(), "skin", &Style_skin, nullptr, false, false, false, false));
        Style::cls().imprint().members.push_back(Member(Style::cls(), method_var(&Style::updated), typecls<unsigned int>(), "updated", &Style_updated, &Style_setUpdated, true, true, false, false));
        Style::cls().imprint().setup();
        
        
        // Widget
        Widget::cls().imprint().inherit();
        Widget::cls().imprint().name = "Widget";
        Widget::cls().imprint().typeClass = OBJECT;
        Widget::cls().imprint().serializable = false;
        Widget::cls().imprint().isTypeObject = true;
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::parent), Wedge::cls(), "parent", &Widget_parent, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::container), Container::cls(), "container", &Widget_container, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::index), typecls<unsigned int>(), "index", &Widget_index, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::frame), Frame::cls(), "frame", &Widget_frame, nullptr, false, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::state), typecls<WidgetState>(), "state", &Widget_state, nullptr, true, false, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::style), Style::cls(), "style", &Widget_style, &Widget_setStyle, false, true, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::label), typecls<string>(), "label", &Widget_label, &Widget_setLabel, true, true, false, false));
        Widget::cls().imprint().members.push_back(Member(Widget::cls(), method_var(&Widget::image), Image::cls(), "image", &Widget_image, &Widget_setImage, true, true, false, false));
        Widget::cls().imprint().setup();
        
        
        // DockTab
        DockTab::cls().imprint().inherit();
        DockTab::cls().imprint().name = "DockTab";
        DockTab::cls().imprint().typeClass = OBJECT;
        DockTab::cls().imprint().serializable = false;
        DockTab::cls().imprint().isTypeObject = false;
        DockTab::cls().imprint().setup();
        
        
        // Wedge
        Wedge::cls().imprint().inherit();
        Wedge::cls().imprint().name = "Wedge";
        Wedge::cls().imprint().typeClass = OBJECT;
        Wedge::cls().imprint().serializable = false;
        Wedge::cls().imprint().isTypeObject = false;
        Wedge::cls().imprint().members.push_back(Member(Wedge::cls(), method_var(&Wedge::contents), typecls<std::vector<Widget*>>(), "contents", &Wedge_contents, nullptr, false, false, true, false));
        Wedge::cls().imprint().setup();
        
        
        // Spacer
        Spacer::cls().imprint().inherit();
        Spacer::cls().imprint().name = "Spacer";
        Spacer::cls().imprint().typeClass = OBJECT;
        Spacer::cls().imprint().serializable = false;
        Spacer::cls().imprint().isTypeObject = false;
        Spacer::cls().imprint().setup();
        
        
        // Item
        Item::cls().imprint().inherit();
        Item::cls().imprint().name = "Item";
        Item::cls().imprint().typeClass = OBJECT;
        Item::cls().imprint().serializable = false;
        Item::cls().imprint().isTypeObject = false;
        Item::cls().imprint().setup();
        
        
        // Label
        Label::cls().imprint().inherit();
        Label::cls().imprint().name = "Label";
        Label::cls().imprint().typeClass = OBJECT;
        Label::cls().imprint().serializable = false;
        Label::cls().imprint().isTypeObject = false;
        Label::cls().imprint().setup();
        
        
        // Icon
        Icon::cls().imprint().inherit();
        Icon::cls().imprint().name = "Icon";
        Icon::cls().imprint().typeClass = OBJECT;
        Icon::cls().imprint().serializable = false;
        Icon::cls().imprint().isTypeObject = false;
        Icon::cls().imprint().setup();
        
        
        // SliderKnob
        SliderKnob::cls().imprint().inherit();
        SliderKnob::cls().imprint().name = "SliderKnob";
        SliderKnob::cls().imprint().typeClass = OBJECT;
        SliderKnob::cls().imprint().serializable = false;
        SliderKnob::cls().imprint().isTypeObject = false;
        SliderKnob::cls().imprint().setup();
        
        
        // FileBrowser
        FileBrowser::cls().imprint().inherit();
        FileBrowser::cls().imprint().name = "FileBrowser";
        FileBrowser::cls().imprint().typeClass = OBJECT;
        FileBrowser::cls().imprint().serializable = false;
        FileBrowser::cls().imprint().isTypeObject = false;
        FileBrowser::cls().imprint().setup();
        
        
        // Container
        Container::cls().imprint().inherit();
        Container::cls().imprint().name = "Container";
        Container::cls().imprint().typeClass = OBJECT;
        Container::cls().imprint().serializable = false;
        Container::cls().imprint().isTypeObject = false;
        Container::cls().imprint().setup();
        
        
        // Filler
        Filler::cls().imprint().inherit();
        Filler::cls().imprint().name = "Filler";
        Filler::cls().imprint().typeClass = OBJECT;
        Filler::cls().imprint().serializable = false;
        Filler::cls().imprint().isTypeObject = false;
        Filler::cls().imprint().setup();
        
        
        // Decal
        Decal::cls().imprint().inherit();
        Decal::cls().imprint().name = "Decal";
        Decal::cls().imprint().typeClass = OBJECT;
        Decal::cls().imprint().serializable = false;
        Decal::cls().imprint().isTypeObject = false;
        Decal::cls().imprint().setup();
        
        
        // Control
        Control::cls().imprint().inherit();
        Control::cls().imprint().name = "Control";
        Control::cls().imprint().typeClass = OBJECT;
        Control::cls().imprint().serializable = false;
        Control::cls().imprint().isTypeObject = false;
        Control::cls().imprint().setup();
        
        
        // Text
        Text::cls().imprint().inherit();
        Text::cls().imprint().name = "Text";
        Text::cls().imprint().typeClass = OBJECT;
        Text::cls().imprint().serializable = false;
        Text::cls().imprint().isTypeObject = false;
        Text::cls().imprint().setup();
        
        
        // Title
        Title::cls().imprint().inherit();
        Title::cls().imprint().name = "Title";
        Title::cls().imprint().typeClass = OBJECT;
        Title::cls().imprint().serializable = false;
        Title::cls().imprint().isTypeObject = false;
        Title::cls().imprint().setup();
        
        
        // Button
        Button::cls().imprint().inherit();
        Button::cls().imprint().name = "Button";
        Button::cls().imprint().typeClass = OBJECT;
        Button::cls().imprint().serializable = false;
        Button::cls().imprint().isTypeObject = false;
        Button::cls().imprint().setup();
        
        
        // Toggle
        Toggle::cls().imprint().inherit();
        Toggle::cls().imprint().name = "Toggle";
        Toggle::cls().imprint().typeClass = OBJECT;
        Toggle::cls().imprint().serializable = false;
        Toggle::cls().imprint().isTypeObject = false;
        Toggle::cls().imprint().setup();
        
        
        // DropdownList
        DropdownList::cls().imprint().inherit();
        DropdownList::cls().imprint().name = "DropdownList";
        DropdownList::cls().imprint().typeClass = OBJECT;
        DropdownList::cls().imprint().serializable = false;
        DropdownList::cls().imprint().isTypeObject = false;
        DropdownList::cls().imprint().setup();
        
        
        // ScrollerKnob
        ScrollerKnob::cls().imprint().inherit();
        ScrollerKnob::cls().imprint().name = "ScrollerKnob";
        ScrollerKnob::cls().imprint().typeClass = OBJECT;
        ScrollerKnob::cls().imprint().serializable = false;
        ScrollerKnob::cls().imprint().isTypeObject = false;
        ScrollerKnob::cls().imprint().setup();
        
        
        // SliderDisplay
        SliderDisplay::cls().imprint().inherit();
        SliderDisplay::cls().imprint().name = "SliderDisplay";
        SliderDisplay::cls().imprint().typeClass = OBJECT;
        SliderDisplay::cls().imprint().serializable = false;
        SliderDisplay::cls().imprint().isTypeObject = false;
        SliderDisplay::cls().imprint().setup();
        
        
        // Directory
        Directory::cls().imprint().inherit();
        Directory::cls().imprint().name = "Directory";
        Directory::cls().imprint().typeClass = OBJECT;
        Directory::cls().imprint().serializable = false;
        Directory::cls().imprint().isTypeObject = false;
        Directory::cls().imprint().setup();
        
        
        // ExpandboxBody
        ExpandboxBody::cls().imprint().inherit();
        ExpandboxBody::cls().imprint().name = "ExpandboxBody";
        ExpandboxBody::cls().imprint().typeClass = OBJECT;
        ExpandboxBody::cls().imprint().serializable = false;
        ExpandboxBody::cls().imprint().isTypeObject = false;
        ExpandboxBody::cls().imprint().setup();
        
        
        // Page
        Page::cls().imprint().inherit();
        Page::cls().imprint().name = "Page";
        Page::cls().imprint().typeClass = OBJECT;
        Page::cls().imprint().serializable = false;
        Page::cls().imprint().isTypeObject = false;
        Page::cls().imprint().setup();
        
        
        // Dialog
        Dialog::cls().imprint().inherit();
        Dialog::cls().imprint().name = "Dialog";
        Dialog::cls().imprint().typeClass = OBJECT;
        Dialog::cls().imprint().serializable = false;
        Dialog::cls().imprint().isTypeObject = false;
        Dialog::cls().imprint().setup();
        
        
        // Board
        Board::cls().imprint().inherit();
        Board::cls().imprint().name = "Board";
        Board::cls().imprint().typeClass = OBJECT;
        Board::cls().imprint().serializable = false;
        Board::cls().imprint().isTypeObject = false;
        Board::cls().imprint().setup();
        
        
        // Row
        Row::cls().imprint().inherit();
        Row::cls().imprint().name = "Row";
        Row::cls().imprint().typeClass = OBJECT;
        Row::cls().imprint().serializable = false;
        Row::cls().imprint().isTypeObject = false;
        Row::cls().imprint().setup();
        
        
        // Div
        Div::cls().imprint().inherit();
        Div::cls().imprint().name = "Div";
        Div::cls().imprint().typeClass = OBJECT;
        Div::cls().imprint().serializable = false;
        Div::cls().imprint().isTypeObject = false;
        Div::cls().imprint().setup();
        
        
        // Stack
        Stack::cls().imprint().inherit();
        Stack::cls().imprint().name = "Stack";
        Stack::cls().imprint().typeClass = OBJECT;
        Stack::cls().imprint().serializable = false;
        Stack::cls().imprint().isTypeObject = false;
        Stack::cls().imprint().setup();
        
        
        // Sheet
        Sheet::cls().imprint().inherit();
        Sheet::cls().imprint().name = "Sheet";
        Sheet::cls().imprint().typeClass = OBJECT;
        Sheet::cls().imprint().serializable = false;
        Sheet::cls().imprint().isTypeObject = false;
        Sheet::cls().imprint().setup();
        
        
        // ScrollSheet
        ScrollSheet::cls().imprint().inherit();
        ScrollSheet::cls().imprint().name = "ScrollSheet";
        ScrollSheet::cls().imprint().typeClass = OBJECT;
        ScrollSheet::cls().imprint().serializable = false;
        ScrollSheet::cls().imprint().isTypeObject = false;
        ScrollSheet::cls().imprint().setup();
        
        
        // Tabber
        Tabber::cls().imprint().inherit();
        Tabber::cls().imprint().name = "Tabber";
        Tabber::cls().imprint().typeClass = OBJECT;
        Tabber::cls().imprint().serializable = false;
        Tabber::cls().imprint().isTypeObject = false;
        Tabber::cls().imprint().setup();
        
        
        // ColumnHeader
        ColumnHeader::cls().imprint().inherit();
        ColumnHeader::cls().imprint().name = "ColumnHeader";
        ColumnHeader::cls().imprint().typeClass = OBJECT;
        ColumnHeader::cls().imprint().serializable = false;
        ColumnHeader::cls().imprint().isTypeObject = false;
        ColumnHeader::cls().imprint().setup();
        
        
        // Tree
        Tree::cls().imprint().inherit();
        Tree::cls().imprint().name = "Tree";
        Tree::cls().imprint().typeClass = OBJECT;
        Tree::cls().imprint().serializable = false;
        Tree::cls().imprint().isTypeObject = false;
        Tree::cls().imprint().setup();
        
        
        // TypeIn
        TypeIn::cls().imprint().inherit();
        TypeIn::cls().imprint().name = "TypeIn";
        TypeIn::cls().imprint().typeClass = OBJECT;
        TypeIn::cls().imprint().serializable = false;
        TypeIn::cls().imprint().isTypeObject = false;
        TypeIn::cls().imprint().setup();
        
        
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
        
        
        // WrapControl
        WrapControl::cls().imprint().inherit();
        WrapControl::cls().imprint().name = "WrapControl";
        WrapControl::cls().imprint().typeClass = OBJECT;
        WrapControl::cls().imprint().serializable = false;
        WrapControl::cls().imprint().isTypeObject = false;
        WrapControl::cls().imprint().setup();
        
        
        // Overlay
        Overlay::cls().imprint().inherit();
        Overlay::cls().imprint().name = "Overlay";
        Overlay::cls().imprint().typeClass = OBJECT;
        Overlay::cls().imprint().serializable = false;
        Overlay::cls().imprint().isTypeObject = false;
        Overlay::cls().imprint().setup();
        
        
        // GridSheet
        GridSheet::cls().imprint().inherit();
        GridSheet::cls().imprint().name = "GridSheet";
        GridSheet::cls().imprint().typeClass = OBJECT;
        GridSheet::cls().imprint().serializable = false;
        GridSheet::cls().imprint().isTypeObject = false;
        GridSheet::cls().imprint().setup();
        
        
        // ToolbarMover
        ToolbarMover::cls().imprint().inherit();
        ToolbarMover::cls().imprint().name = "ToolbarMover";
        ToolbarMover::cls().imprint().typeClass = OBJECT;
        ToolbarMover::cls().imprint().serializable = false;
        ToolbarMover::cls().imprint().isTypeObject = false;
        ToolbarMover::cls().imprint().setup();
        
        
        // WindowSizer
        WindowSizer::cls().imprint().inherit();
        WindowSizer::cls().imprint().name = "WindowSizer";
        WindowSizer::cls().imprint().typeClass = OBJECT;
        WindowSizer::cls().imprint().serializable = false;
        WindowSizer::cls().imprint().isTypeObject = false;
        WindowSizer::cls().imprint().setup();
        
        
        // WrapButton
        WrapButton::cls().imprint().inherit();
        WrapButton::cls().imprint().name = "WrapButton";
        WrapButton::cls().imprint().typeClass = OBJECT;
        WrapButton::cls().imprint().serializable = false;
        WrapButton::cls().imprint().isTypeObject = false;
        WrapButton::cls().imprint().setup();
        
        
        // Checkbox
        Checkbox::cls().imprint().inherit();
        Checkbox::cls().imprint().name = "Checkbox";
        Checkbox::cls().imprint().typeClass = OBJECT;
        Checkbox::cls().imprint().serializable = false;
        Checkbox::cls().imprint().isTypeObject = false;
        Checkbox::cls().imprint().setup();
        
        
        // DropdownToggle
        DropdownToggle::cls().imprint().inherit();
        DropdownToggle::cls().imprint().name = "DropdownToggle";
        DropdownToggle::cls().imprint().typeClass = OBJECT;
        DropdownToggle::cls().imprint().serializable = false;
        DropdownToggle::cls().imprint().isTypeObject = false;
        DropdownToggle::cls().imprint().setup();
        
        
        // ScrollForward
        ScrollForward::cls().imprint().inherit();
        ScrollForward::cls().imprint().name = "ScrollForward";
        ScrollForward::cls().imprint().typeClass = OBJECT;
        ScrollForward::cls().imprint().serializable = false;
        ScrollForward::cls().imprint().isTypeObject = false;
        ScrollForward::cls().imprint().setup();
        
        
        // ScrollBackward
        ScrollBackward::cls().imprint().inherit();
        ScrollBackward::cls().imprint().name = "ScrollBackward";
        ScrollBackward::cls().imprint().typeClass = OBJECT;
        ScrollBackward::cls().imprint().serializable = false;
        ScrollBackward::cls().imprint().isTypeObject = false;
        ScrollBackward::cls().imprint().setup();
        
        
        // Scrollbar
        Scrollbar::cls().imprint().inherit();
        Scrollbar::cls().imprint().name = "Scrollbar";
        Scrollbar::cls().imprint().typeClass = OBJECT;
        Scrollbar::cls().imprint().serializable = false;
        Scrollbar::cls().imprint().isTypeObject = false;
        Scrollbar::cls().imprint().setup();
        
        
        // Slider
        Slider::cls().imprint().inherit();
        Slider::cls().imprint().name = "Slider";
        Slider::cls().imprint().typeClass = OBJECT;
        Slider::cls().imprint().serializable = false;
        Slider::cls().imprint().isTypeObject = false;
        Slider::cls().imprint().setup();
        
        
        // ExpandboxToggle
        ExpandboxToggle::cls().imprint().inherit();
        ExpandboxToggle::cls().imprint().name = "ExpandboxToggle";
        ExpandboxToggle::cls().imprint().typeClass = OBJECT;
        ExpandboxToggle::cls().imprint().serializable = false;
        ExpandboxToggle::cls().imprint().isTypeObject = false;
        ExpandboxToggle::cls().imprint().setup();
        
        
        // Expandbox
        Expandbox::cls().imprint().inherit();
        Expandbox::cls().imprint().name = "Expandbox";
        Expandbox::cls().imprint().typeClass = OBJECT;
        Expandbox::cls().imprint().serializable = false;
        Expandbox::cls().imprint().isTypeObject = false;
        Expandbox::cls().imprint().setup();
        
        
        // Layout
        Layout::cls().imprint().inherit();
        Layout::cls().imprint().name = "Layout";
        Layout::cls().imprint().typeClass = OBJECT;
        Layout::cls().imprint().serializable = false;
        Layout::cls().imprint().isTypeObject = false;
        Layout::cls().imprint().setup();
        
        
        // Header
        Header::cls().imprint().inherit();
        Header::cls().imprint().name = "Header";
        Header::cls().imprint().typeClass = OBJECT;
        Header::cls().imprint().serializable = false;
        Header::cls().imprint().isTypeObject = false;
        Header::cls().imprint().setup();
        
        
        // List
        List::cls().imprint().inherit();
        List::cls().imprint().name = "List";
        List::cls().imprint().typeClass = OBJECT;
        List::cls().imprint().serializable = false;
        List::cls().imprint().isTypeObject = false;
        List::cls().imprint().setup();
        
        
        // LabelSequence
        LabelSequence::cls().imprint().inherit();
        LabelSequence::cls().imprint().name = "LabelSequence";
        LabelSequence::cls().imprint().typeClass = OBJECT;
        LabelSequence::cls().imprint().serializable = false;
        LabelSequence::cls().imprint().isTypeObject = false;
        LabelSequence::cls().imprint().setup();
        
        
        // ButtonSequence
        ButtonSequence::cls().imprint().inherit();
        ButtonSequence::cls().imprint().name = "ButtonSequence";
        ButtonSequence::cls().imprint().typeClass = OBJECT;
        ButtonSequence::cls().imprint().serializable = false;
        ButtonSequence::cls().imprint().isTypeObject = false;
        ButtonSequence::cls().imprint().setup();
        
        
        // ScrollPlan
        ScrollPlan::cls().imprint().inherit();
        ScrollPlan::cls().imprint().name = "ScrollPlan";
        ScrollPlan::cls().imprint().typeClass = OBJECT;
        ScrollPlan::cls().imprint().serializable = false;
        ScrollPlan::cls().imprint().isTypeObject = false;
        ScrollPlan::cls().imprint().setup();
        
        
        // TabHeader
        TabHeader::cls().imprint().inherit();
        TabHeader::cls().imprint().name = "TabHeader";
        TabHeader::cls().imprint().typeClass = OBJECT;
        TabHeader::cls().imprint().serializable = false;
        TabHeader::cls().imprint().isTypeObject = false;
        TabHeader::cls().imprint().setup();
        
        
        // Tab
        Tab::cls().imprint().inherit();
        Tab::cls().imprint().name = "Tab";
        Tab::cls().imprint().typeClass = OBJECT;
        Tab::cls().imprint().serializable = false;
        Tab::cls().imprint().isTypeObject = false;
        Tab::cls().imprint().setup();
        
        
        // TabberHead
        TabberHead::cls().imprint().inherit();
        TabberHead::cls().imprint().name = "TabberHead";
        TabberHead::cls().imprint().typeClass = OBJECT;
        TabberHead::cls().imprint().serializable = false;
        TabberHead::cls().imprint().isTypeObject = false;
        TabberHead::cls().imprint().setup();
        
        
        // TabberBody
        TabberBody::cls().imprint().inherit();
        TabberBody::cls().imprint().name = "TabberBody";
        TabberBody::cls().imprint().typeClass = OBJECT;
        TabberBody::cls().imprint().serializable = false;
        TabberBody::cls().imprint().isTypeObject = false;
        TabberBody::cls().imprint().setup();
        
        
        // TableHead
        TableHead::cls().imprint().inherit();
        TableHead::cls().imprint().name = "TableHead";
        TableHead::cls().imprint().typeClass = OBJECT;
        TableHead::cls().imprint().serializable = false;
        TableHead::cls().imprint().isTypeObject = false;
        TableHead::cls().imprint().setup();
        
        
        // Table
        Table::cls().imprint().inherit();
        Table::cls().imprint().name = "Table";
        Table::cls().imprint().typeClass = OBJECT;
        Table::cls().imprint().serializable = false;
        Table::cls().imprint().isTypeObject = false;
        Table::cls().imprint().setup();
        
        
        // Textbox
        Textbox::cls().imprint().inherit();
        Textbox::cls().imprint().name = "Textbox";
        Textbox::cls().imprint().typeClass = OBJECT;
        Textbox::cls().imprint().serializable = false;
        Textbox::cls().imprint().isTypeObject = false;
        Textbox::cls().imprint().setup();
        
        
        // WValue
        WValue::cls().imprint().inherit();
        WValue::cls().imprint().name = "WValue";
        WValue::cls().imprint().typeClass = OBJECT;
        WValue::cls().imprint().serializable = false;
        WValue::cls().imprint().isTypeObject = false;
        WValue::cls().imprint().setup();
        
        
        // Tooltip
        Tooltip::cls().imprint().inherit();
        Tooltip::cls().imprint().name = "Tooltip";
        Tooltip::cls().imprint().typeClass = OBJECT;
        Tooltip::cls().imprint().serializable = false;
        Tooltip::cls().imprint().isTypeObject = false;
        Tooltip::cls().imprint().setup();
        
        
        // Placeholder
        Placeholder::cls().imprint().inherit();
        Placeholder::cls().imprint().name = "Placeholder";
        Placeholder::cls().imprint().typeClass = OBJECT;
        Placeholder::cls().imprint().serializable = false;
        Placeholder::cls().imprint().isTypeObject = false;
        Placeholder::cls().imprint().setup();
        
        
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
        
        
        // CloseButton
        CloseButton::cls().imprint().inherit();
        CloseButton::cls().imprint().name = "CloseButton";
        CloseButton::cls().imprint().typeClass = OBJECT;
        CloseButton::cls().imprint().serializable = false;
        CloseButton::cls().imprint().isTypeObject = false;
        CloseButton::cls().imprint().setup();
        
        
        // WindowHeader
        WindowHeader::cls().imprint().inherit();
        WindowHeader::cls().imprint().name = "WindowHeader";
        WindowHeader::cls().imprint().typeClass = OBJECT;
        WindowHeader::cls().imprint().serializable = false;
        WindowHeader::cls().imprint().isTypeObject = false;
        WindowHeader::cls().imprint().setup();
        
        
        // WindowSizerLeft
        WindowSizerLeft::cls().imprint().inherit();
        WindowSizerLeft::cls().imprint().name = "WindowSizerLeft";
        WindowSizerLeft::cls().imprint().typeClass = OBJECT;
        WindowSizerLeft::cls().imprint().serializable = false;
        WindowSizerLeft::cls().imprint().isTypeObject = false;
        WindowSizerLeft::cls().imprint().setup();
        
        
        // WindowSizerRight
        WindowSizerRight::cls().imprint().inherit();
        WindowSizerRight::cls().imprint().name = "WindowSizerRight";
        WindowSizerRight::cls().imprint().typeClass = OBJECT;
        WindowSizerRight::cls().imprint().serializable = false;
        WindowSizerRight::cls().imprint().isTypeObject = false;
        WindowSizerRight::cls().imprint().setup();
        
        
        // WindowFooter
        WindowFooter::cls().imprint().inherit();
        WindowFooter::cls().imprint().name = "WindowFooter";
        WindowFooter::cls().imprint().typeClass = OBJECT;
        WindowFooter::cls().imprint().serializable = false;
        WindowFooter::cls().imprint().isTypeObject = false;
        WindowFooter::cls().imprint().setup();
        
        
        // WindowBody
        WindowBody::cls().imprint().inherit();
        WindowBody::cls().imprint().name = "WindowBody";
        WindowBody::cls().imprint().typeClass = OBJECT;
        WindowBody::cls().imprint().serializable = false;
        WindowBody::cls().imprint().isTypeObject = false;
        WindowBody::cls().imprint().setup();
        
        
        // Window
        Window::cls().imprint().inherit();
        Window::cls().imprint().name = "Window";
        Window::cls().imprint().typeClass = OBJECT;
        Window::cls().imprint().serializable = false;
        Window::cls().imprint().isTypeObject = false;
        Window::cls().imprint().setup();
        
        
        // MultiButton
        MultiButton::cls().imprint().inherit();
        MultiButton::cls().imprint().name = "MultiButton";
        MultiButton::cls().imprint().typeClass = OBJECT;
        MultiButton::cls().imprint().serializable = false;
        MultiButton::cls().imprint().isTypeObject = false;
        MultiButton::cls().imprint().setup();
        
        
        // Dropdown
        Dropdown::cls().imprint().inherit();
        Dropdown::cls().imprint().name = "Dropdown";
        Dropdown::cls().imprint().typeClass = OBJECT;
        Dropdown::cls().imprint().serializable = false;
        Dropdown::cls().imprint().isTypeObject = false;
        Dropdown::cls().imprint().setup();
        
        
        // Scroller
        Scroller::cls().imprint().inherit();
        Scroller::cls().imprint().name = "Scroller";
        Scroller::cls().imprint().typeClass = OBJECT;
        Scroller::cls().imprint().serializable = false;
        Scroller::cls().imprint().isTypeObject = false;
        Scroller::cls().imprint().setup();
        
        
        // ExpandboxHeader
        ExpandboxHeader::cls().imprint().inherit();
        ExpandboxHeader::cls().imprint().name = "ExpandboxHeader";
        ExpandboxHeader::cls().imprint().typeClass = OBJECT;
        ExpandboxHeader::cls().imprint().serializable = false;
        ExpandboxHeader::cls().imprint().isTypeObject = false;
        ExpandboxHeader::cls().imprint().setup();
        
        
        // SelectList
        SelectList::cls().imprint().inherit();
        SelectList::cls().imprint().name = "SelectList";
        SelectList::cls().imprint().typeClass = OBJECT;
        SelectList::cls().imprint().serializable = false;
        SelectList::cls().imprint().isTypeObject = false;
        SelectList::cls().imprint().setup();
        
        
        // SortList
        SortList::cls().imprint().inherit();
        SortList::cls().imprint().name = "SortList";
        SortList::cls().imprint().typeClass = OBJECT;
        SortList::cls().imprint().serializable = false;
        SortList::cls().imprint().isTypeObject = false;
        SortList::cls().imprint().setup();
        
        
        // ScrollZone
        ScrollZone::cls().imprint().inherit();
        ScrollZone::cls().imprint().name = "ScrollZone";
        ScrollZone::cls().imprint().typeClass = OBJECT;
        ScrollZone::cls().imprint().serializable = false;
        ScrollZone::cls().imprint().isTypeObject = false;
        ScrollZone::cls().imprint().setup();
        
        
        // TreeNode
        TreeNode::cls().imprint().inherit();
        TreeNode::cls().imprint().name = "TreeNode";
        TreeNode::cls().imprint().typeClass = OBJECT;
        TreeNode::cls().imprint().serializable = false;
        TreeNode::cls().imprint().isTypeObject = false;
        TreeNode::cls().imprint().setup();
        
        
        // Input<bool>
        Input<bool>::cls().imprint().inherit();
        Input<bool>::cls().imprint().name = "Input<bool>";
        Input<bool>::cls().imprint().typeClass = OBJECT;
        Input<bool>::cls().imprint().serializable = false;
        Input<bool>::cls().imprint().isTypeObject = false;
        Input<bool>::cls().imprint().setup();
        
        
        // Input<string>
        Input<string>::cls().imprint().inherit();
        Input<string>::cls().imprint().name = "Input<string>";
        Input<string>::cls().imprint().typeClass = OBJECT;
        Input<string>::cls().imprint().serializable = false;
        Input<string>::cls().imprint().isTypeObject = false;
        Input<string>::cls().imprint().setup();
        
        
        // Input<toy::Colour>
        Input<toy::Colour>::cls().imprint().inherit();
        Input<toy::Colour>::cls().imprint().name = "Input<toy::Colour>";
        Input<toy::Colour>::cls().imprint().typeClass = OBJECT;
        Input<toy::Colour>::cls().imprint().serializable = false;
        Input<toy::Colour>::cls().imprint().isTypeObject = false;
        Input<toy::Colour>::cls().imprint().setup();
        
        
        // MasterDockline
        MasterDockline::cls().imprint().inherit();
        MasterDockline::cls().imprint().name = "MasterDockline";
        MasterDockline::cls().imprint().typeClass = OBJECT;
        MasterDockline::cls().imprint().serializable = false;
        MasterDockline::cls().imprint().isTypeObject = false;
        MasterDockline::cls().imprint().setup();
        
        
        // Dockspace
        Dockspace::cls().imprint().inherit();
        Dockspace::cls().imprint().name = "Dockspace";
        Dockspace::cls().imprint().typeClass = OBJECT;
        Dockspace::cls().imprint().serializable = false;
        Dockspace::cls().imprint().isTypeObject = false;
        Dockspace::cls().imprint().setup();
        
        
        // Menubar
        Menubar::cls().imprint().inherit();
        Menubar::cls().imprint().name = "Menubar";
        Menubar::cls().imprint().typeClass = OBJECT;
        Menubar::cls().imprint().serializable = false;
        Menubar::cls().imprint().isTypeObject = false;
        Menubar::cls().imprint().setup();
        
        
        // DropdownHead
        DropdownHead::cls().imprint().inherit();
        DropdownHead::cls().imprint().name = "DropdownHead";
        DropdownHead::cls().imprint().typeClass = OBJECT;
        DropdownHead::cls().imprint().serializable = false;
        DropdownHead::cls().imprint().isTypeObject = false;
        DropdownHead::cls().imprint().setup();
        
        
        // DropdownChoice
        DropdownChoice::cls().imprint().inherit();
        DropdownChoice::cls().imprint().name = "DropdownChoice";
        DropdownChoice::cls().imprint().typeClass = OBJECT;
        DropdownChoice::cls().imprint().serializable = false;
        DropdownChoice::cls().imprint().isTypeObject = false;
        DropdownChoice::cls().imprint().setup();
        
        
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
        
        
        
        module.types.push_back(&Image::cls());
        module.types.push_back(&Label::cls());
        module.types.push_back(&Text::cls());
        module.types.push_back(&Title::cls());
        module.types.push_back(&Icon::cls());
        module.types.push_back(&Button::cls());
        module.types.push_back(&WrapButton::cls());
        module.types.push_back(&MultiButton::cls());
        module.types.push_back(&Toggle::cls());
        module.types.push_back(&Checkbox::cls());
        module.types.push_back(&DropdownHead::cls());
        module.types.push_back(&DropdownToggle::cls());
        module.types.push_back(&DropdownChoice::cls());
        module.types.push_back(&DropdownList::cls());
        module.types.push_back(&Dropdown::cls());
        module.types.push_back(&DropdownInput::cls());
        module.types.push_back(&Scroller::cls());
        module.types.push_back(&ScrollerKnob::cls());
        module.types.push_back(&ScrollForward::cls());
        module.types.push_back(&ScrollBackward::cls());
        module.types.push_back(&Scrollbar::cls());
        module.types.push_back(&SliderKnob::cls());
        module.types.push_back(&Slider::cls());
        module.types.push_back(&SliderDisplay::cls());
        module.types.push_back(&Dir::cls());
        module.types.push_back(&File::cls());
        module.types.push_back(&Directory::cls());
        module.types.push_back(&FileBrowser::cls());
        module.types.push_back(&FileNode::cls());
        module.types.push_back(&DirectoryNode::cls());
        module.types.push_back(&ExpandboxHeader::cls());
        module.types.push_back(&ExpandboxBody::cls());
        module.types.push_back(&ExpandboxToggle::cls());
        module.types.push_back(&Expandbox::cls());
        module.types.push_back(&Page::cls());
        module.types.push_back(&Dialog::cls());
        module.types.push_back(&Board::cls());
        module.types.push_back(&Layout::cls());
        module.types.push_back(&Row::cls());
        module.types.push_back(&Div::cls());
        module.types.push_back(&Stack::cls());
        module.types.push_back(&Sheet::cls());
        module.types.push_back(&Header::cls());
        module.types.push_back(&List::cls());
        module.types.push_back(&SelectList::cls());
        module.types.push_back(&LabelSequence::cls());
        module.types.push_back(&ButtonSequence::cls());
        module.types.push_back(&SortList::cls());
        module.types.push_back(&ScrollZone::cls());
        module.types.push_back(&ScrollSheet::cls());
        module.types.push_back(&ScrollPlan::cls());
        module.types.push_back(&TabHeader::cls());
        module.types.push_back(&Tab::cls());
        module.types.push_back(&TabberHead::cls());
        module.types.push_back(&TabberBody::cls());
        module.types.push_back(&Tabber::cls());
        module.types.push_back(&TableHead::cls());
        module.types.push_back(&ColumnHeader::cls());
        module.types.push_back(&Table::cls());
        module.types.push_back(&TreeNode::cls());
        module.types.push_back(&Tree::cls());
        module.types.push_back(&StatSlider<float>::cls());
        module.types.push_back(&StatSlider<int>::cls());
        module.types.push_back(&Input<unsigned int>::cls());
        module.types.push_back(&Input<int>::cls());
        module.types.push_back(&Input<float>::cls());
        module.types.push_back(&Input<double>::cls());
        module.types.push_back(&Input<bool>::cls());
        module.types.push_back(&Input<string>::cls());
        module.types.push_back(&Input<toy::Colour>::cls());
        module.types.push_back(&Textbox::cls());
        module.types.push_back(&TypeIn::cls());
        module.types.push_back(&WValue::cls());
        module.types.push_back(&Frame::cls());
        module.types.push_back(&typecls<Dimension>());
        module.types.push_back(&typecls<Direction>());
        module.types.push_back(&typecls<Pivot>());
        module.types.push_back(&typecls<Align>());
        module.types.push_back(&typecls<FrameType>());
        module.types.push_back(&typecls<AutoLayout>());
        module.types.push_back(&typecls<Flow>());
        module.types.push_back(&typecls<Sizing>());
        module.types.push_back(&typecls<Space>());
        module.types.push_back(&typecls<Clipping>());
        module.types.push_back(&typecls<Opacity>());
        module.types.push_back(&BoxFloat::cls());
        module.types.push_back(&ImageSkin::cls());
        module.types.push_back(&Shadow::cls());
        module.types.push_back(&Paint::cls());
        module.types.push_back(&LayoutStyle::cls());
        module.types.push_back(&InkStyle::cls());
        module.types.push_back(&Style::cls());
        module.types.push_back(&Tooltip::cls());
        module.types.push_back(&Rectangle::cls());
        module.types.push_back(&Cursor::cls());
        module.types.push_back(&RootSheet::cls());
        module.types.push_back(&Wedge::cls());
        module.types.push_back(&typecls<std::vector<Widget*>>());
        module.types.push_back(&Container::cls());
        module.types.push_back(&WrapControl::cls());
        module.types.push_back(&Spacer::cls());
        module.types.push_back(&Filler::cls());
        module.types.push_back(&Decal::cls());
        module.types.push_back(&Overlay::cls());
        module.types.push_back(&GridSheet::cls());
        module.types.push_back(&typecls<WidgetState>());
        module.types.push_back(&Widget::cls());
        module.types.push_back(&Item::cls());
        module.types.push_back(&Control::cls());
        module.types.push_back(&Placeholder::cls());
        module.types.push_back(&DockTab::cls());
        module.types.push_back(&Docksection::cls());
        module.types.push_back(&Dockline::cls());
        module.types.push_back(&MasterDockline::cls());
        module.types.push_back(&Dockspace::cls());
        module.types.push_back(&Menu::cls());
        module.types.push_back(&Menubar::cls());
        module.types.push_back(&ToolButton::cls());
        module.types.push_back(&Tooldock::cls());
        module.types.push_back(&ToolbarMover::cls());
        module.types.push_back(&Toolbar::cls());
        module.types.push_back(&CloseButton::cls());
        module.types.push_back(&WindowHeader::cls());
        module.types.push_back(&WindowSizer::cls());
        module.types.push_back(&WindowSizerLeft::cls());
        module.types.push_back(&WindowSizerRight::cls());
        module.types.push_back(&WindowFooter::cls());
        module.types.push_back(&WindowBody::cls());
        module.types.push_back(&Window::cls());
    
    }

}
#endif

#endif // TOYUI_IMPRINTS_H
