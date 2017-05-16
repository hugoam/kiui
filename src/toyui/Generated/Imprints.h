

#ifndef TOYUI_IMPRINTS_H
#define TOYUI_IMPRINTS_H

#include <toyui/Config.h>
#include <toyui/Forward.h>
#include <toyui/Types.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Reflect/Member.h>
#include <toyobj/Reflect/Injector.h>
#include <toyobj/Reflect/Method.h>
#include <toyobj/Util/Unique.h>
#include <toyobj/Module.h>
#include <toyobj/Memory/Memory.h>

namespace toy
{
#ifdef IMPRINT_DEF_FILE
    Object& BoxFloat_create(BoxFloat* at, LrefVector& args) {  new(at) BoxFloat( args[0]->copy<float>(), args[1]->copy<float>(), args[2]->copy<float>(), args[3]->copy<float>() ); return *at; }
    Object& BoxFloat_proto_poolinject(AbstractPool& pool, LrefVector& args) { return BoxFloat_create(pool.as<Pool<BoxFloat>>().alloc(), args); }
    Object& BoxFloat_proto_lrefinject(Lref& lref, LrefVector& args) { return BoxFloat_create(&lref->as<BoxFloat>(), args); }
    AbstractPool* BoxFloat_makePool() { return new Pool<BoxFloat>(); }

    Object& InkStyle_create(InkStyle* at, LrefVector& args) {  new(at) InkStyle( &args[0]->as<Style>() ); return *at; }
    Object& InkStyle_proto_poolinject(AbstractPool& pool, LrefVector& args) { return InkStyle_create(pool.as<Pool<InkStyle>>().alloc(), args); }
    Object& InkStyle_proto_lrefinject(Lref& lref, LrefVector& args) { return InkStyle_create(&lref->as<InkStyle>(), args); }
    AbstractPool* InkStyle_makePool() { return new Pool<InkStyle>(); }

    








	void BoxFloat_x0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x0()); }
	void BoxFloat_setX0(Object& object, const Lref& ref) { object.as<BoxFloat>().setX0(ref->copy<float>()); }
	void BoxFloat_y0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y0()); }
	void BoxFloat_setY0(Object& object, const Lref& ref) { object.as<BoxFloat>().setY0(ref->copy<float>()); }
	void BoxFloat_x1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x1()); }
	void BoxFloat_setX1(Object& object, const Lref& ref) { object.as<BoxFloat>().setX1(ref->copy<float>()); }
	void BoxFloat_y1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y1()); }
	void BoxFloat_setY1(Object& object, const Lref& ref) { object.as<BoxFloat>().setY1(ref->copy<float>()); }
	void BoxFloat_x(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x()); }
	void BoxFloat_y(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y()); }
	void BoxFloat_w(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().w()); }
	void BoxFloat_h(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().h()); }
	void BoxFloat_v0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v0()); }
	void BoxFloat_v1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v1()); }
	void BoxFloat_v2(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v2()); }
	void BoxFloat_v3(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v3()); }

	void ImageSkin_d_image(Object& object, Lref& ref) { ref->set<Image>(*object.as<ImageSkin>().d_image); }
	void ImageSkin_setD_image(Object& object, const Lref& ref) { object.as<ImageSkin>().d_image = &ref->as<Image>(); }
	void ImageSkin_d_filetype(Object& object, Lref& ref) { ref->set<string>(object.as<ImageSkin>().d_filetype); }
	void ImageSkin_setD_filetype(Object& object, const Lref& ref) { object.as<ImageSkin>().d_filetype = ref->copy<string>(); }
	void ImageSkin_d_top(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_top); }
	void ImageSkin_setD_top(Object& object, const Lref& ref) { object.as<ImageSkin>().d_top = ref->copy<int>(); }
	void ImageSkin_d_right(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_right); }
	void ImageSkin_setD_right(Object& object, const Lref& ref) { object.as<ImageSkin>().d_right = ref->copy<int>(); }
	void ImageSkin_d_bottom(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_bottom); }
	void ImageSkin_setD_bottom(Object& object, const Lref& ref) { object.as<ImageSkin>().d_bottom = ref->copy<int>(); }
	void ImageSkin_d_left(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_left); }
	void ImageSkin_setD_left(Object& object, const Lref& ref) { object.as<ImageSkin>().d_left = ref->copy<int>(); }
	void ImageSkin_d_margin(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_margin); }
	void ImageSkin_setD_margin(Object& object, const Lref& ref) { object.as<ImageSkin>().d_margin = ref->copy<int>(); }
	void ImageSkin_d_stretch(Object& object, Lref& ref) { ref->set<Dimension>(object.as<ImageSkin>().d_stretch); }
	void ImageSkin_setD_stretch(Object& object, const Lref& ref) { object.as<ImageSkin>().d_stretch = ref->copy<Dimension>(); }


	void LayoutStyle_d_updated(Object& object, Lref& ref) { ref->set<size_t>(object.as<LayoutStyle>().d_updated); }
	void LayoutStyle_setD_updated(Object& object, const Lref& ref) { object.as<LayoutStyle>().d_updated = ref->copy<size_t>(); }


	void Style_name(Object& object, Lref& ref) { ref->set<string>(object.as<Style>().name()); }
	void Style_base(Object& object, Lref& ref) { ref->setobject(*object.as<Style>().base()); }
	void Style_layout(Object& object, Lref& ref) { ref->set<LayoutStyle>(object.as<Style>().layout()); }
	void Style_skin(Object& object, Lref& ref) { ref->set<InkStyle>(object.as<Style>().skin()); }
	void Style_updated(Object& object, Lref& ref) { ref->set<size_t>(object.as<Style>().updated()); }
	void Style_setUpdated(Object& object, const Lref& ref) { object.as<Style>().setUpdated(ref->copy<size_t>()); }

	void Widget_parent(Object& object, Lref& ref) { ref->setobject(*object.as<Widget>().parent()); }
	void Widget_container(Object& object, Lref& ref) { ref->setobject(*object.as<Widget>().container()); }
	void Widget_index(Object& object, Lref& ref) { ref->set<size_t>(object.as<Widget>().index()); }
	void Widget_frame(Object& object, Lref& ref) { ref->setobject(object.as<Widget>().frame()); }
	void Widget_state(Object& object, Lref& ref) { ref->set<WidgetState>(object.as<Widget>().state()); }
	void Widget_style(Object& object, Lref& ref) { ref->setobject(object.as<Widget>().style()); }
	void Widget_setStyle(Object& object, const Lref& ref) { object.as<Widget>().setStyle(ref->as<Style>()); }
	void Widget_label(Object& object, Lref& ref) { ref->set<string>(object.as<Widget>().label()); }
	void Widget_setLabel(Object& object, const Lref& ref) { object.as<Widget>().setLabel(ref->copy<string>()); }
	void Widget_image(Object& object, Lref& ref) { ref->set<Image>(*object.as<Widget>().image()); }
	void Widget_setImage(Object& object, const Lref& ref) { object.as<Widget>().setImage(&ref->as<Image>()); }


	void Wedge_contents(Object& object, Lref& ref) { ref->set<std::vector<Widget*>>(object.as<Wedge>().contents()); }



































































































    
    
	class toyui : public Module
	{
    private:
        toyui()
        {
            // Base Types
        
            // Enums
            typecls<Dimension>().imprint().setup("Dimension", ENUM);
            typecls<Dimension>().imprint().initEnum(StringVector({ "DIM_X", "DIM_Y", "DIM_XX", "DIM_YY", "DIM_NULL" }));
            typecls<Dimension>().imprint().initRefMethods<Dimension>();
            
            typecls<Direction>().imprint().setup("Direction", ENUM);
            typecls<Direction>().imprint().initEnum(StringVector({ "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "DIMENSION", "DIRECTION_AUTO" }));
            typecls<Direction>().imprint().initRefMethods<Direction>();
            
            typecls<Pivot>().imprint().setup("Pivot", ENUM);
            typecls<Pivot>().imprint().initEnum(StringVector({ "FORWARD", "REVERSE" }));
            typecls<Pivot>().imprint().initRefMethods<Pivot>();
            
            typecls<Align>().imprint().setup("Align", ENUM);
            typecls<Align>().imprint().initEnum(StringVector({ "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" }));
            typecls<Align>().imprint().initRefMethods<Align>();
            
            typecls<FrameType>().imprint().setup("FrameType", ENUM);
            typecls<FrameType>().imprint().initEnum(StringVector({ "FRAME", "STRIPE", "GRID", "TABLE", "LAYER", "MASTER_LAYER", "SPACE_LAYER" }));
            typecls<FrameType>().imprint().initRefMethods<FrameType>();
            
            typecls<AutoLayout>().imprint().setup("AutoLayout", ENUM);
            typecls<AutoLayout>().imprint().initEnum(StringVector({ "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" }));
            typecls<AutoLayout>().imprint().initRefMethods<AutoLayout>();
            
            typecls<Flow>().imprint().setup("Flow", ENUM);
            typecls<Flow>().imprint().initEnum(StringVector({ "FLOW", "OVERLAY", "ALIGN", "FREE" }));
            typecls<Flow>().imprint().initRefMethods<Flow>();
            
            typecls<Space>().imprint().setup("Space", ENUM);
            typecls<Space>().imprint().initEnum(StringVector({ "MANUAL_SPACE", "SHEET", "ITEM", "BLOCK", "FIXED_BLOCK", "LINE", "STACK", "DIV", "SPACE", "BOARD", "PARALLEL_FLEX" }));
            typecls<Space>().imprint().initRefMethods<Space>();
            
            typecls<Sizing>().imprint().setup("Sizing", ENUM);
            typecls<Sizing>().imprint().initEnum(StringVector({ "FIXED", "MANUAL", "SHRINK", "WRAP", "EXPAND" }));
            typecls<Sizing>().imprint().initRefMethods<Sizing>();
            
            typecls<Clipping>().imprint().setup("Clipping", ENUM);
            typecls<Clipping>().imprint().initEnum(StringVector({ "NOCLIP", "CLIP" }));
            typecls<Clipping>().imprint().initRefMethods<Clipping>();
            
            typecls<Opacity>().imprint().setup("Opacity", ENUM);
            typecls<Opacity>().imprint().initEnum(StringVector({ "OPAQUE", "CLEAR", "HOLLOW" }));
            typecls<Opacity>().imprint().initRefMethods<Opacity>();
            
            typecls<WidgetState>().imprint().setup("WidgetState", ENUM);
            typecls<WidgetState>().imprint().initEnum(StringVector({ "NOSTATE", "HOVERED", "TRIGGERED", "ACTIVATED", "FOCUSED", "DISABLED", "PRESSED", "DRAGGED", "CONTROL", "MODAL" }));
            typecls<WidgetState>().imprint().initRefMethods<WidgetState>();
            
        
            // Sequences
            typecls<std::vector<Widget*>>().imprint().setup("std::vector<Widget*>", SEQUENCE);
            typecls<std::vector<Widget*>>().imprint().initRefMethods<std::vector<Widget*>>();
            typecls<std::vector<Widget*>>().imprint().initObjectVector<Widget*>();
            
        
            // Stores
        
        
            // Image
            Image::cls().imprint().setup("Image", STRUCT);
            Image::cls().imprint().initRefMethods<Image>();
            Image::cls().imprint().initObject(false, false);
            
            // StatSliderfloat
            StatSlider<float>::cls().imprint().setup("StatSlider<float>", OBJECT);
            StatSlider<float>::cls().imprint().initObject(false, false);
            
            // StatSliderint
            StatSlider<int>::cls().imprint().setup("StatSlider<int>", OBJECT);
            StatSlider<int>::cls().imprint().initObject(false, false);
            
            // Inputunsigned int
            Input<unsigned int>::cls().imprint().setup("Input<unsigned int>", OBJECT);
            Input<unsigned int>::cls().imprint().initObject(false, false);
            
            // Inputint
            Input<int>::cls().imprint().setup("Input<int>", OBJECT);
            Input<int>::cls().imprint().initObject(false, false);
            
            // Inputfloat
            Input<float>::cls().imprint().setup("Input<float>", OBJECT);
            Input<float>::cls().imprint().initObject(false, false);
            
            // Inputdouble
            Input<double>::cls().imprint().setup("Input<double>", OBJECT);
            Input<double>::cls().imprint().initObject(false, false);
            
            // Frame
            Frame::cls().imprint().setup("Frame", OBJECT);
            Frame::cls().imprint().initObject(false, false);
            
            // BoxFloat
            BoxFloat::cls().imprint().setup("BoxFloat", STRUCT);
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x0), typecls<float>(), 0, "x0", &BoxFloat_x0, &BoxFloat_setX0, true, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y0), typecls<float>(), 1, "y0", &BoxFloat_y0, &BoxFloat_setY0, true, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x1), typecls<float>(), 2, "x1", &BoxFloat_x1, &BoxFloat_setX1, true, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y1), typecls<float>(), 3, "y1", &BoxFloat_y1, &BoxFloat_setY1, true, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x), typecls<float>(), 4, "x", &BoxFloat_x, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y), typecls<float>(), 5, "y", &BoxFloat_y, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::w), typecls<float>(), 6, "w", &BoxFloat_w, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::h), typecls<float>(), 7, "h", &BoxFloat_h, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v0), typecls<float>(), 8, "v0", &BoxFloat_v0, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v1), typecls<float>(), 9, "v1", &BoxFloat_v1, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v2), typecls<float>(), 10, "v2", &BoxFloat_v2, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v3), typecls<float>(), 11, "v3", &BoxFloat_v3, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().initRefMethods<BoxFloat>();
            BoxFloat::cls().imprint().setConstructor(make_unique<Method>(BoxFloat::cls(), "BoxFloat", Lref(), nullptr, ParamVector({ Param("x0", lref(float()), false, INPUT_PARAM), Param("y0", lref(float()), false, INPUT_PARAM), Param("x1", lref(float()), false, INPUT_PARAM), Param("y1", lref(float()), false, INPUT_PARAM) })));
            BoxFloat::cls().imprint().initInjectors(&BoxFloat_proto_poolinject, &BoxFloat_proto_lrefinject, &BoxFloat_makePool);
            BoxFloat::cls().imprint().initObject(false, false);
            
            // ImageSkin
            ImageSkin::cls().imprint().setup("ImageSkin", STRUCT);
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), Image::cls(), 0, "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<string>(), 1, "d_filetype", &ImageSkin_d_filetype, &ImageSkin_setD_filetype, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 2, "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 3, "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 4, "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 5, "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 6, "d_margin", &ImageSkin_d_margin, &ImageSkin_setD_margin, true, false, false, false));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<Dimension>(), 7, "d_stretch", &ImageSkin_d_stretch, &ImageSkin_setD_stretch, true, false, false, false));
            ImageSkin::cls().imprint().initRefMethods<ImageSkin>();
            ImageSkin::cls().imprint().initObject(false, false);
            
            // Shadow
            Shadow::cls().imprint().setup("Shadow", STRUCT);
            Shadow::cls().imprint().initRefMethods<Shadow>();
            Shadow::cls().imprint().initObject(false, false);
            
            // LayoutStyle
            LayoutStyle::cls().imprint().setup("LayoutStyle", STRUCT);
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(LayoutStyle::cls(), Lref(), typecls<size_t>(), 0, "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, true, false, false, false));
            LayoutStyle::cls().imprint().initRefMethods<LayoutStyle>();
            LayoutStyle::cls().imprint().initObject(false, false);
            
            // InkStyle
            InkStyle::cls().imprint().setup("InkStyle", STRUCT);
            InkStyle::cls().imprint().initRefMethods<InkStyle>();
            InkStyle::cls().imprint().setConstructor(make_unique<Method>(InkStyle::cls(), "InkStyle", Lref(), nullptr, ParamVector({ Param("style", Lref(Style::cls()), true, INPUT_PARAM) })));
            InkStyle::cls().imprint().initInjectors(&InkStyle_proto_poolinject, &InkStyle_proto_lrefinject, &InkStyle_makePool);
            InkStyle::cls().imprint().initObject(false, false);
            
            // Style
            Style::cls().imprint().setup("Style", OBJECT);
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), lref(&Style::name), typecls<string>(), 0, "name", &Style_name, nullptr, false, false, false, false));
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), lref(&Style::base), Style::cls(), 1, "base", &Style_base, nullptr, false, false, false, false));
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), lref(&Style::layout), LayoutStyle::cls(), 2, "layout", &Style_layout, nullptr, false, false, false, false));
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), lref(&Style::skin), InkStyle::cls(), 3, "skin", &Style_skin, nullptr, false, false, false, false));
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), lref(&Style::updated), typecls<size_t>(), 4, "updated", &Style_updated, &Style_setUpdated, true, false, false, false));
            Style::cls().imprint().initObject(false, true);
            
            // Widget
            Widget::cls().imprint().setup("Widget", OBJECT);
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::parent), Wedge::cls(), 0, "parent", &Widget_parent, nullptr, false, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::container), Container::cls(), 1, "container", &Widget_container, nullptr, false, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::index), typecls<size_t>(), 2, "index", &Widget_index, nullptr, false, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::frame), Frame::cls(), 3, "frame", &Widget_frame, nullptr, false, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::state), typecls<WidgetState>(), 4, "state", &Widget_state, nullptr, false, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::style), Style::cls(), 5, "style", &Widget_style, &Widget_setStyle, true, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::label), typecls<string>(), 6, "label", &Widget_label, &Widget_setLabel, true, false, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Widget::cls(), lref(&Widget::image), Image::cls(), 7, "image", &Widget_image, &Widget_setImage, true, false, false, false));
            Widget::cls().imprint().initObject(false, true);
            
            // DockTab
            DockTab::cls().imprint().setup("DockTab", OBJECT);
            DockTab::cls().imprint().initObject(false, false);
            
            // Wedge
            Wedge::cls().imprint().setup("Wedge", OBJECT);
            Wedge::cls().imprint().addMember(make_unique<Member>(Wedge::cls(), lref(&Wedge::contents), typecls<std::vector<Widget*>>(), 0, "contents", &Wedge_contents, nullptr, false, true, false, false));
            Wedge::cls().imprint().initObject(false, false);
            
            // Spacer
            Spacer::cls().imprint().setup("Spacer", OBJECT);
            Spacer::cls().imprint().initObject(false, false);
            
            // Item
            Item::cls().imprint().setup("Item", OBJECT);
            Item::cls().imprint().initObject(false, false);
            
            // Label
            Label::cls().imprint().setup("Label", OBJECT);
            Label::cls().imprint().initObject(false, false);
            
            // Icon
            Icon::cls().imprint().setup("Icon", OBJECT);
            Icon::cls().imprint().initObject(false, false);
            
            // SliderKnob
            SliderKnob::cls().imprint().setup("SliderKnob", OBJECT);
            SliderKnob::cls().imprint().initObject(false, false);
            
            // FileBrowser
            FileBrowser::cls().imprint().setup("FileBrowser", OBJECT);
            FileBrowser::cls().imprint().initObject(false, false);
            
            // Container
            Container::cls().imprint().setup("Container", OBJECT);
            Container::cls().imprint().initObject(false, false);
            
            // Filler
            Filler::cls().imprint().setup("Filler", OBJECT);
            Filler::cls().imprint().initObject(false, false);
            
            // Decal
            Decal::cls().imprint().setup("Decal", OBJECT);
            Decal::cls().imprint().initObject(false, false);
            
            // Control
            Control::cls().imprint().setup("Control", OBJECT);
            Control::cls().imprint().initObject(false, false);
            
            // Text
            Text::cls().imprint().setup("Text", OBJECT);
            Text::cls().imprint().initObject(false, false);
            
            // Title
            Title::cls().imprint().setup("Title", OBJECT);
            Title::cls().imprint().initObject(false, false);
            
            // Button
            Button::cls().imprint().setup("Button", OBJECT);
            Button::cls().imprint().initObject(false, false);
            
            // Toggle
            Toggle::cls().imprint().setup("Toggle", OBJECT);
            Toggle::cls().imprint().initObject(false, false);
            
            // DropdownList
            DropdownList::cls().imprint().setup("DropdownList", OBJECT);
            DropdownList::cls().imprint().initObject(false, false);
            
            // ScrollerKnob
            ScrollerKnob::cls().imprint().setup("ScrollerKnob", OBJECT);
            ScrollerKnob::cls().imprint().initObject(false, false);
            
            // SliderDisplay
            SliderDisplay::cls().imprint().setup("SliderDisplay", OBJECT);
            SliderDisplay::cls().imprint().initObject(false, false);
            
            // Directory
            Directory::cls().imprint().setup("Directory", OBJECT);
            Directory::cls().imprint().initObject(false, false);
            
            // ExpandboxBody
            ExpandboxBody::cls().imprint().setup("ExpandboxBody", OBJECT);
            ExpandboxBody::cls().imprint().initObject(false, false);
            
            // Tabber
            Tabber::cls().imprint().setup("Tabber", OBJECT);
            Tabber::cls().imprint().initObject(false, false);
            
            // ColumnHeader
            ColumnHeader::cls().imprint().setup("ColumnHeader", OBJECT);
            ColumnHeader::cls().imprint().initObject(false, false);
            
            // Tree
            Tree::cls().imprint().setup("Tree", OBJECT);
            Tree::cls().imprint().initObject(false, false);
            
            // TypeIn
            TypeIn::cls().imprint().setup("TypeIn", OBJECT);
            TypeIn::cls().imprint().initObject(false, false);
            
            // Rectangle
            Rectangle::cls().imprint().setup("Rectangle", OBJECT);
            Rectangle::cls().imprint().initObject(false, false);
            
            // Cursor
            Cursor::cls().imprint().setup("Cursor", OBJECT);
            Cursor::cls().imprint().initObject(false, false);
            
            // Page
            Page::cls().imprint().setup("Page", OBJECT);
            Page::cls().imprint().initObject(false, false);
            
            // Dialog
            Dialog::cls().imprint().setup("Dialog", OBJECT);
            Dialog::cls().imprint().initObject(false, false);
            
            // Board
            Board::cls().imprint().setup("Board", OBJECT);
            Board::cls().imprint().initObject(false, false);
            
            // Row
            Row::cls().imprint().setup("Row", OBJECT);
            Row::cls().imprint().initObject(false, false);
            
            // Div
            Div::cls().imprint().setup("Div", OBJECT);
            Div::cls().imprint().initObject(false, false);
            
            // Stack
            Stack::cls().imprint().setup("Stack", OBJECT);
            Stack::cls().imprint().initObject(false, false);
            
            // Sheet
            Sheet::cls().imprint().setup("Sheet", OBJECT);
            Sheet::cls().imprint().initObject(false, false);
            
            // RootSheet
            RootSheet::cls().imprint().setup("RootSheet", OBJECT);
            RootSheet::cls().imprint().initObject(false, false);
            
            // ScrollSheet
            ScrollSheet::cls().imprint().setup("ScrollSheet", OBJECT);
            ScrollSheet::cls().imprint().initObject(false, false);
            
            // WrapControl
            WrapControl::cls().imprint().setup("WrapControl", OBJECT);
            WrapControl::cls().imprint().initObject(false, false);
            
            // Overlay
            Overlay::cls().imprint().setup("Overlay", OBJECT);
            Overlay::cls().imprint().initObject(false, false);
            
            // GridSheet
            GridSheet::cls().imprint().setup("GridSheet", OBJECT);
            GridSheet::cls().imprint().initObject(false, false);
            
            // ToolbarMover
            ToolbarMover::cls().imprint().setup("ToolbarMover", OBJECT);
            ToolbarMover::cls().imprint().initObject(false, false);
            
            // WindowSizer
            WindowSizer::cls().imprint().setup("WindowSizer", OBJECT);
            WindowSizer::cls().imprint().initObject(false, false);
            
            // WrapButton
            WrapButton::cls().imprint().setup("WrapButton", OBJECT);
            WrapButton::cls().imprint().initObject(false, false);
            
            // Checkbox
            Checkbox::cls().imprint().setup("Checkbox", OBJECT);
            Checkbox::cls().imprint().initObject(false, false);
            
            // DropdownToggle
            DropdownToggle::cls().imprint().setup("DropdownToggle", OBJECT);
            DropdownToggle::cls().imprint().initObject(false, false);
            
            // ScrollForward
            ScrollForward::cls().imprint().setup("ScrollForward", OBJECT);
            ScrollForward::cls().imprint().initObject(false, false);
            
            // ScrollBackward
            ScrollBackward::cls().imprint().setup("ScrollBackward", OBJECT);
            ScrollBackward::cls().imprint().initObject(false, false);
            
            // Scrollbar
            Scrollbar::cls().imprint().setup("Scrollbar", OBJECT);
            Scrollbar::cls().imprint().initObject(false, false);
            
            // Slider
            Slider::cls().imprint().setup("Slider", OBJECT);
            Slider::cls().imprint().initObject(false, false);
            
            // ExpandboxToggle
            ExpandboxToggle::cls().imprint().setup("ExpandboxToggle", OBJECT);
            ExpandboxToggle::cls().imprint().initObject(false, false);
            
            // Expandbox
            Expandbox::cls().imprint().setup("Expandbox", OBJECT);
            Expandbox::cls().imprint().initObject(false, false);
            
            // List
            List::cls().imprint().setup("List", OBJECT);
            List::cls().imprint().initObject(false, false);
            
            // LabelSequence
            LabelSequence::cls().imprint().setup("LabelSequence", OBJECT);
            LabelSequence::cls().imprint().initObject(false, false);
            
            // ButtonSequence
            ButtonSequence::cls().imprint().setup("ButtonSequence", OBJECT);
            ButtonSequence::cls().imprint().initObject(false, false);
            
            // TabHeader
            TabHeader::cls().imprint().setup("TabHeader", OBJECT);
            TabHeader::cls().imprint().initObject(false, false);
            
            // Tab
            Tab::cls().imprint().setup("Tab", OBJECT);
            Tab::cls().imprint().initObject(false, false);
            
            // TabberHead
            TabberHead::cls().imprint().setup("TabberHead", OBJECT);
            TabberHead::cls().imprint().initObject(false, false);
            
            // TabberBody
            TabberBody::cls().imprint().setup("TabberBody", OBJECT);
            TabberBody::cls().imprint().initObject(false, false);
            
            // TableHead
            TableHead::cls().imprint().setup("TableHead", OBJECT);
            TableHead::cls().imprint().initObject(false, false);
            
            // Table
            Table::cls().imprint().setup("Table", OBJECT);
            Table::cls().imprint().initObject(false, false);
            
            // Textbox
            Textbox::cls().imprint().setup("Textbox", OBJECT);
            Textbox::cls().imprint().initObject(false, false);
            
            // WValue
            WValue::cls().imprint().setup("WValue", OBJECT);
            WValue::cls().imprint().initObject(false, false);
            
            // Tooltip
            Tooltip::cls().imprint().setup("Tooltip", OBJECT);
            Tooltip::cls().imprint().initObject(false, false);
            
            // Layout
            Layout::cls().imprint().setup("Layout", OBJECT);
            Layout::cls().imprint().initObject(false, false);
            
            // Header
            Header::cls().imprint().setup("Header", OBJECT);
            Header::cls().imprint().initObject(false, false);
            
            // ScrollPlan
            ScrollPlan::cls().imprint().setup("ScrollPlan", OBJECT);
            ScrollPlan::cls().imprint().initObject(false, false);
            
            // Placeholder
            Placeholder::cls().imprint().setup("Placeholder", OBJECT);
            Placeholder::cls().imprint().initObject(false, false);
            
            // Docksection
            Docksection::cls().imprint().setup("Docksection", OBJECT);
            Docksection::cls().imprint().initObject(false, false);
            
            // Dockline
            Dockline::cls().imprint().setup("Dockline", OBJECT);
            Dockline::cls().imprint().initObject(false, false);
            
            // Tooldock
            Tooldock::cls().imprint().setup("Tooldock", OBJECT);
            Tooldock::cls().imprint().initObject(false, false);
            
            // Toolbar
            Toolbar::cls().imprint().setup("Toolbar", OBJECT);
            Toolbar::cls().imprint().initObject(false, false);
            
            // CloseButton
            CloseButton::cls().imprint().setup("CloseButton", OBJECT);
            CloseButton::cls().imprint().initObject(false, false);
            
            // WindowHeader
            WindowHeader::cls().imprint().setup("WindowHeader", OBJECT);
            WindowHeader::cls().imprint().initObject(false, false);
            
            // WindowSizerLeft
            WindowSizerLeft::cls().imprint().setup("WindowSizerLeft", OBJECT);
            WindowSizerLeft::cls().imprint().initObject(false, false);
            
            // WindowSizerRight
            WindowSizerRight::cls().imprint().setup("WindowSizerRight", OBJECT);
            WindowSizerRight::cls().imprint().initObject(false, false);
            
            // WindowFooter
            WindowFooter::cls().imprint().setup("WindowFooter", OBJECT);
            WindowFooter::cls().imprint().initObject(false, false);
            
            // WindowBody
            WindowBody::cls().imprint().setup("WindowBody", OBJECT);
            WindowBody::cls().imprint().initObject(false, false);
            
            // Window
            Window::cls().imprint().setup("Window", OBJECT);
            Window::cls().imprint().initObject(false, false);
            
            // MultiButton
            MultiButton::cls().imprint().setup("MultiButton", OBJECT);
            MultiButton::cls().imprint().initObject(false, false);
            
            // Dropdown
            Dropdown::cls().imprint().setup("Dropdown", OBJECT);
            Dropdown::cls().imprint().initObject(false, false);
            
            // Scroller
            Scroller::cls().imprint().setup("Scroller", OBJECT);
            Scroller::cls().imprint().initObject(false, false);
            
            // ExpandboxHeader
            ExpandboxHeader::cls().imprint().setup("ExpandboxHeader", OBJECT);
            ExpandboxHeader::cls().imprint().initObject(false, false);
            
            // SelectList
            SelectList::cls().imprint().setup("SelectList", OBJECT);
            SelectList::cls().imprint().initObject(false, false);
            
            // SortList
            SortList::cls().imprint().setup("SortList", OBJECT);
            SortList::cls().imprint().initObject(false, false);
            
            // TreeNode
            TreeNode::cls().imprint().setup("TreeNode", OBJECT);
            TreeNode::cls().imprint().initObject(false, false);
            
            // Inputtoy::Colour
            Input<toy::Colour>::cls().imprint().setup("Input<toy::Colour>", OBJECT);
            Input<toy::Colour>::cls().imprint().initObject(false, false);
            
            // Inputbool
            Input<bool>::cls().imprint().setup("Input<bool>", OBJECT);
            Input<bool>::cls().imprint().initObject(false, false);
            
            // Inputstring
            Input<string>::cls().imprint().setup("Input<string>", OBJECT);
            Input<string>::cls().imprint().initObject(false, false);
            
            // ScrollZone
            ScrollZone::cls().imprint().setup("ScrollZone", OBJECT);
            ScrollZone::cls().imprint().initObject(false, false);
            
            // MasterDockline
            MasterDockline::cls().imprint().setup("MasterDockline", OBJECT);
            MasterDockline::cls().imprint().initObject(false, false);
            
            // Dockspace
            Dockspace::cls().imprint().setup("Dockspace", OBJECT);
            Dockspace::cls().imprint().initObject(false, false);
            
            // Menubar
            Menubar::cls().imprint().setup("Menubar", OBJECT);
            Menubar::cls().imprint().initObject(false, false);
            
            // DropdownHead
            DropdownHead::cls().imprint().setup("DropdownHead", OBJECT);
            DropdownHead::cls().imprint().initObject(false, false);
            
            // DropdownChoice
            DropdownChoice::cls().imprint().setup("DropdownChoice", OBJECT);
            DropdownChoice::cls().imprint().initObject(false, false);
            
            // DropdownInput
            DropdownInput::cls().imprint().setup("DropdownInput", OBJECT);
            DropdownInput::cls().imprint().initObject(false, false);
            
            // Dir
            Dir::cls().imprint().setup("Dir", OBJECT);
            Dir::cls().imprint().initObject(false, false);
            
            // File
            File::cls().imprint().setup("File", OBJECT);
            File::cls().imprint().initObject(false, false);
            
            // FileNode
            FileNode::cls().imprint().setup("FileNode", OBJECT);
            FileNode::cls().imprint().initObject(false, false);
            
            // DirectoryNode
            DirectoryNode::cls().imprint().setup("DirectoryNode", OBJECT);
            DirectoryNode::cls().imprint().initObject(false, false);
            
            // Menu
            Menu::cls().imprint().setup("Menu", OBJECT);
            Menu::cls().imprint().initObject(false, false);
            
            // ToolButton
            ToolButton::cls().imprint().setup("ToolButton", OBJECT);
            ToolButton::cls().imprint().initObject(false, false);
            
            
            m_rootTypes.push_back(&Image::cls());
            m_rootTypes.push_back(&StatSlider<float>::cls());
            m_rootTypes.push_back(&StatSlider<int>::cls());
            m_rootTypes.push_back(&Input<unsigned int>::cls());
            m_rootTypes.push_back(&Input<int>::cls());
            m_rootTypes.push_back(&Input<float>::cls());
            m_rootTypes.push_back(&Input<double>::cls());
            m_rootTypes.push_back(&Frame::cls());
            m_rootTypes.push_back(&BoxFloat::cls());
            m_rootTypes.push_back(&ImageSkin::cls());
            m_rootTypes.push_back(&Shadow::cls());
            m_rootTypes.push_back(&LayoutStyle::cls());
            m_rootTypes.push_back(&InkStyle::cls());
            m_rootTypes.push_back(&Style::cls());
            m_rootTypes.push_back(&Widget::cls());
            m_rootTypes.push_back(&DockTab::cls());
            m_rootTypes.push_back(&Wedge::cls());
            m_rootTypes.push_back(&Spacer::cls());
            m_rootTypes.push_back(&Item::cls());
            m_rootTypes.push_back(&Label::cls());
            m_rootTypes.push_back(&Icon::cls());
            m_rootTypes.push_back(&SliderKnob::cls());
            m_rootTypes.push_back(&FileBrowser::cls());
            m_rootTypes.push_back(&Container::cls());
            m_rootTypes.push_back(&Filler::cls());
            m_rootTypes.push_back(&Decal::cls());
            m_rootTypes.push_back(&Control::cls());
            m_rootTypes.push_back(&Text::cls());
            m_rootTypes.push_back(&Title::cls());
            m_rootTypes.push_back(&Button::cls());
            m_rootTypes.push_back(&Toggle::cls());
            m_rootTypes.push_back(&DropdownList::cls());
            m_rootTypes.push_back(&ScrollerKnob::cls());
            m_rootTypes.push_back(&SliderDisplay::cls());
            m_rootTypes.push_back(&Directory::cls());
            m_rootTypes.push_back(&ExpandboxBody::cls());
            m_rootTypes.push_back(&Tabber::cls());
            m_rootTypes.push_back(&ColumnHeader::cls());
            m_rootTypes.push_back(&Tree::cls());
            m_rootTypes.push_back(&TypeIn::cls());
            m_rootTypes.push_back(&Rectangle::cls());
            m_rootTypes.push_back(&Cursor::cls());
            m_rootTypes.push_back(&Page::cls());
            m_rootTypes.push_back(&Dialog::cls());
            m_rootTypes.push_back(&Board::cls());
            m_rootTypes.push_back(&Row::cls());
            m_rootTypes.push_back(&Div::cls());
            m_rootTypes.push_back(&Stack::cls());
            m_rootTypes.push_back(&Sheet::cls());
            m_rootTypes.push_back(&RootSheet::cls());
            m_rootTypes.push_back(&ScrollSheet::cls());
            m_rootTypes.push_back(&WrapControl::cls());
            m_rootTypes.push_back(&Overlay::cls());
            m_rootTypes.push_back(&GridSheet::cls());
            m_rootTypes.push_back(&ToolbarMover::cls());
            m_rootTypes.push_back(&WindowSizer::cls());
            m_rootTypes.push_back(&WrapButton::cls());
            m_rootTypes.push_back(&Checkbox::cls());
            m_rootTypes.push_back(&DropdownToggle::cls());
            m_rootTypes.push_back(&ScrollForward::cls());
            m_rootTypes.push_back(&ScrollBackward::cls());
            m_rootTypes.push_back(&Scrollbar::cls());
            m_rootTypes.push_back(&Slider::cls());
            m_rootTypes.push_back(&ExpandboxToggle::cls());
            m_rootTypes.push_back(&Expandbox::cls());
            m_rootTypes.push_back(&List::cls());
            m_rootTypes.push_back(&LabelSequence::cls());
            m_rootTypes.push_back(&ButtonSequence::cls());
            m_rootTypes.push_back(&TabHeader::cls());
            m_rootTypes.push_back(&Tab::cls());
            m_rootTypes.push_back(&TabberHead::cls());
            m_rootTypes.push_back(&TabberBody::cls());
            m_rootTypes.push_back(&TableHead::cls());
            m_rootTypes.push_back(&Table::cls());
            m_rootTypes.push_back(&Textbox::cls());
            m_rootTypes.push_back(&WValue::cls());
            m_rootTypes.push_back(&Tooltip::cls());
            m_rootTypes.push_back(&Layout::cls());
            m_rootTypes.push_back(&Header::cls());
            m_rootTypes.push_back(&ScrollPlan::cls());
            m_rootTypes.push_back(&Placeholder::cls());
            m_rootTypes.push_back(&Docksection::cls());
            m_rootTypes.push_back(&Dockline::cls());
            m_rootTypes.push_back(&Tooldock::cls());
            m_rootTypes.push_back(&Toolbar::cls());
            m_rootTypes.push_back(&CloseButton::cls());
            m_rootTypes.push_back(&WindowHeader::cls());
            m_rootTypes.push_back(&WindowSizerLeft::cls());
            m_rootTypes.push_back(&WindowSizerRight::cls());
            m_rootTypes.push_back(&WindowFooter::cls());
            m_rootTypes.push_back(&WindowBody::cls());
            m_rootTypes.push_back(&Window::cls());
            m_rootTypes.push_back(&MultiButton::cls());
            m_rootTypes.push_back(&Dropdown::cls());
            m_rootTypes.push_back(&Scroller::cls());
            m_rootTypes.push_back(&ExpandboxHeader::cls());
            m_rootTypes.push_back(&SelectList::cls());
            m_rootTypes.push_back(&SortList::cls());
            m_rootTypes.push_back(&TreeNode::cls());
            m_rootTypes.push_back(&Input<toy::Colour>::cls());
            m_rootTypes.push_back(&Input<bool>::cls());
            m_rootTypes.push_back(&Input<string>::cls());
            m_rootTypes.push_back(&ScrollZone::cls());
            m_rootTypes.push_back(&MasterDockline::cls());
            m_rootTypes.push_back(&Dockspace::cls());
            m_rootTypes.push_back(&Menubar::cls());
            m_rootTypes.push_back(&DropdownHead::cls());
            m_rootTypes.push_back(&DropdownChoice::cls());
            m_rootTypes.push_back(&DropdownInput::cls());
            m_rootTypes.push_back(&Dir::cls());
            m_rootTypes.push_back(&File::cls());
            m_rootTypes.push_back(&FileNode::cls());
            m_rootTypes.push_back(&DirectoryNode::cls());
            m_rootTypes.push_back(&Menu::cls());
            m_rootTypes.push_back(&ToolButton::cls());
        
        }

		static toyui instance;
        
    public:
        static toyui& module() { return instance; }
	};
    
	toyui toyui::instance;
#endif // IMPRINT_DEF_FILE
}

#endif // TOYUI_IMPRINTS_H
