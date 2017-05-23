

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
    Object& BoxFloat_poolinject(AbstractPool& pool, LrefVector& args) { return BoxFloat_create(pool.as<Pool<BoxFloat>>().alloc(), args); }
    Object& BoxFloat_lrefinject(Lref& lref, LrefVector& args) { return BoxFloat_create(&lref->as<BoxFloat>(), args); }
    AbstractPool* BoxFloat_makePool() { return new Pool<BoxFloat>(); }

    Object& InkStyle_create(InkStyle* at, LrefVector& args) {  new(at) InkStyle( &args[0]->as<Style>() ); return *at; }
    Object& InkStyle_poolinject(AbstractPool& pool, LrefVector& args) { return InkStyle_create(pool.as<Pool<InkStyle>>().alloc(), args); }
    Object& InkStyle_lrefinject(Lref& lref, LrefVector& args) { return InkStyle_create(&lref->as<InkStyle>(), args); }
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
            typecls<Dimension>().imprint().name = "Dimension";
            typecls<Dimension>().imprint().typeClass = ENUM;
            typecls<Dimension>().imprint().enumIds = { "DIM_X", "DIM_Y", "DIM_XX", "DIM_YY", "DIM_NULL" };
            typecls<Dimension>().imprint().initRefMethods<Dimension>();
            
            typecls<Direction>().imprint().name = "Direction";
            typecls<Direction>().imprint().typeClass = ENUM;
            typecls<Direction>().imprint().enumIds = { "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "DIMENSION", "DIRECTION_AUTO" };
            typecls<Direction>().imprint().initRefMethods<Direction>();
            
            typecls<Pivot>().imprint().name = "Pivot";
            typecls<Pivot>().imprint().typeClass = ENUM;
            typecls<Pivot>().imprint().enumIds = { "FORWARD", "REVERSE" };
            typecls<Pivot>().imprint().initRefMethods<Pivot>();
            
            typecls<Align>().imprint().name = "Align";
            typecls<Align>().imprint().typeClass = ENUM;
            typecls<Align>().imprint().enumIds = { "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" };
            typecls<Align>().imprint().initRefMethods<Align>();
            
            typecls<FrameType>().imprint().name = "FrameType";
            typecls<FrameType>().imprint().typeClass = ENUM;
            typecls<FrameType>().imprint().enumIds = { "FRAME", "STRIPE", "GRID", "TABLE", "LAYER", "MASTER_LAYER", "SPACE_LAYER" };
            typecls<FrameType>().imprint().initRefMethods<FrameType>();
            
            typecls<AutoLayout>().imprint().name = "AutoLayout";
            typecls<AutoLayout>().imprint().typeClass = ENUM;
            typecls<AutoLayout>().imprint().enumIds = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" };
            typecls<AutoLayout>().imprint().initRefMethods<AutoLayout>();
            
            typecls<Flow>().imprint().name = "Flow";
            typecls<Flow>().imprint().typeClass = ENUM;
            typecls<Flow>().imprint().enumIds = { "FLOW", "OVERLAY", "ALIGN", "FREE" };
            typecls<Flow>().imprint().initRefMethods<Flow>();
            
            typecls<Sizing>().imprint().name = "Sizing";
            typecls<Sizing>().imprint().typeClass = ENUM;
            typecls<Sizing>().imprint().enumIds = { "FIXED", "MANUAL", "SHRINK", "WRAP", "EXPAND" };
            typecls<Sizing>().imprint().initRefMethods<Sizing>();
            
            typecls<Space>().imprint().name = "Space";
            typecls<Space>().imprint().typeClass = ENUM;
            typecls<Space>().imprint().enumIds = { "MANUAL_SPACE", "SHEET", "ITEM", "BLOCK", "FIXED_BLOCK", "LINE", "STACK", "DIV", "SPACE", "BOARD", "PARALLEL_FLEX" };
            typecls<Space>().imprint().initRefMethods<Space>();
            
            typecls<Clipping>().imprint().name = "Clipping";
            typecls<Clipping>().imprint().typeClass = ENUM;
            typecls<Clipping>().imprint().enumIds = { "NOCLIP", "CLIP" };
            typecls<Clipping>().imprint().initRefMethods<Clipping>();
            
            typecls<Opacity>().imprint().name = "Opacity";
            typecls<Opacity>().imprint().typeClass = ENUM;
            typecls<Opacity>().imprint().enumIds = { "OPAQUE", "CLEAR", "HOLLOW" };
            typecls<Opacity>().imprint().initRefMethods<Opacity>();
            
            typecls<WidgetState>().imprint().name = "WidgetState";
            typecls<WidgetState>().imprint().typeClass = ENUM;
            typecls<WidgetState>().imprint().enumIds = { "NOSTATE", "HOVERED", "TRIGGERED", "ACTIVATED", "FOCUSED", "DISABLED", "PRESSED", "DRAGGED", "CONTROL", "MODAL" };
            typecls<WidgetState>().imprint().initRefMethods<WidgetState>();
            
        
            // Sequences
            typecls<std::vector<Widget*>>().imprint().name = "std::vector<Widget*>";
            typecls<std::vector<Widget*>>().imprint().typeClass = SEQUENCE;
            typecls<std::vector<Widget*>>().imprint().initRefMethods<std::vector<Widget*>>();
            typecls<std::vector<Widget*>>().imprint().initObjectVector<Widget*>();
            
        
            // Stores
        
        
            // Image
            Image::cls().imprint().name = "Image";
            Image::cls().imprint().typeClass = STRUCT;
            Image::cls().imprint().serializable = false;
            Image::cls().imprint().isTypeObject = false;
            Image::cls().imprint().initRefMethods<Image>();
            
            
            // StatSliderfloat
            StatSlider<float>::cls().imprint().name = "StatSlider<float>";
            StatSlider<float>::cls().imprint().typeClass = OBJECT;
            StatSlider<float>::cls().imprint().serializable = false;
            StatSlider<float>::cls().imprint().isTypeObject = false;
            
            
            // StatSliderint
            StatSlider<int>::cls().imprint().name = "StatSlider<int>";
            StatSlider<int>::cls().imprint().typeClass = OBJECT;
            StatSlider<int>::cls().imprint().serializable = false;
            StatSlider<int>::cls().imprint().isTypeObject = false;
            
            
            // Inputunsigned int
            Input<unsigned int>::cls().imprint().name = "Input<unsigned int>";
            Input<unsigned int>::cls().imprint().typeClass = OBJECT;
            Input<unsigned int>::cls().imprint().serializable = false;
            Input<unsigned int>::cls().imprint().isTypeObject = false;
            
            
            // Inputint
            Input<int>::cls().imprint().name = "Input<int>";
            Input<int>::cls().imprint().typeClass = OBJECT;
            Input<int>::cls().imprint().serializable = false;
            Input<int>::cls().imprint().isTypeObject = false;
            
            
            // Inputfloat
            Input<float>::cls().imprint().name = "Input<float>";
            Input<float>::cls().imprint().typeClass = OBJECT;
            Input<float>::cls().imprint().serializable = false;
            Input<float>::cls().imprint().isTypeObject = false;
            
            
            // Inputdouble
            Input<double>::cls().imprint().name = "Input<double>";
            Input<double>::cls().imprint().typeClass = OBJECT;
            Input<double>::cls().imprint().serializable = false;
            Input<double>::cls().imprint().isTypeObject = false;
            
            
            // Frame
            Frame::cls().imprint().name = "Frame";
            Frame::cls().imprint().typeClass = OBJECT;
            Frame::cls().imprint().serializable = false;
            Frame::cls().imprint().isTypeObject = false;
            
            
            // BoxFloat
            BoxFloat::cls().imprint().name = "BoxFloat";
            BoxFloat::cls().imprint().typeClass = STRUCT;
            BoxFloat::cls().imprint().serializable = false;
            BoxFloat::cls().imprint().isTypeObject = false;
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x0), typecls<float>(), 0, "x0", &BoxFloat_x0, &BoxFloat_setX0, true, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y0), typecls<float>(), 1, "y0", &BoxFloat_y0, &BoxFloat_setY0, true, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x1), typecls<float>(), 2, "x1", &BoxFloat_x1, &BoxFloat_setX1, true, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y1), typecls<float>(), 3, "y1", &BoxFloat_y1, &BoxFloat_setY1, true, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::x), typecls<float>(), 4, "x", &BoxFloat_x, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::y), typecls<float>(), 5, "y", &BoxFloat_y, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::w), typecls<float>(), 6, "w", &BoxFloat_w, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::h), typecls<float>(), 7, "h", &BoxFloat_h, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v0), typecls<float>(), 8, "v0", &BoxFloat_v0, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v1), typecls<float>(), 9, "v1", &BoxFloat_v1, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v2), typecls<float>(), 10, "v2", &BoxFloat_v2, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().members.emplace_back(make_unique<Member>(BoxFloat::cls(), lref(&BoxFloat::v3), typecls<float>(), 11, "v3", &BoxFloat_v3, nullptr, false, false, false, false));
            BoxFloat::cls().imprint().constructor = make_unique<Method>(BoxFloat::cls(), "BoxFloat", Lref(), nullptr, ParamVector({ Param("x0", lref(float()), false, INPUT_PARAM), Param("y0", lref(float()), false, INPUT_PARAM), Param("x1", lref(float()), false, INPUT_PARAM), Param("y1", lref(float()), false, INPUT_PARAM) }));
            BoxFloat::cls().imprint().poolInject = &BoxFloat_poolinject;
            BoxFloat::cls().imprint().lrefInject = &BoxFloat_lrefinject;
            BoxFloat::cls().imprint().makePool = &BoxFloat_makePool;
            BoxFloat::cls().imprint().initRefMethods<BoxFloat>();
            
            
            // ImageSkin
            ImageSkin::cls().imprint().name = "ImageSkin";
            ImageSkin::cls().imprint().typeClass = STRUCT;
            ImageSkin::cls().imprint().serializable = false;
            ImageSkin::cls().imprint().isTypeObject = false;
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), Image::cls(), 0, "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<string>(), 1, "d_filetype", &ImageSkin_d_filetype, &ImageSkin_setD_filetype, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 2, "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 3, "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 4, "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 5, "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<int>(), 6, "d_margin", &ImageSkin_d_margin, &ImageSkin_setD_margin, true, false, false, false));
            ImageSkin::cls().imprint().members.emplace_back(make_unique<Member>(ImageSkin::cls(), Lref(), typecls<Dimension>(), 7, "d_stretch", &ImageSkin_d_stretch, &ImageSkin_setD_stretch, true, false, false, false));
            ImageSkin::cls().imprint().initRefMethods<ImageSkin>();
            
            
            // Shadow
            Shadow::cls().imprint().name = "Shadow";
            Shadow::cls().imprint().typeClass = STRUCT;
            Shadow::cls().imprint().serializable = false;
            Shadow::cls().imprint().isTypeObject = false;
            Shadow::cls().imprint().initRefMethods<Shadow>();
            
            
            // Paint
            Paint::cls().imprint().name = "Paint";
            Paint::cls().imprint().typeClass = STRUCT;
            Paint::cls().imprint().serializable = false;
            Paint::cls().imprint().isTypeObject = false;
            Paint::cls().imprint().initRefMethods<Paint>();
            
            
            // LayoutStyle
            LayoutStyle::cls().imprint().name = "LayoutStyle";
            LayoutStyle::cls().imprint().typeClass = STRUCT;
            LayoutStyle::cls().imprint().serializable = false;
            LayoutStyle::cls().imprint().isTypeObject = false;
            LayoutStyle::cls().imprint().members.emplace_back(make_unique<Member>(LayoutStyle::cls(), Lref(), typecls<size_t>(), 0, "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, true, false, false, false));
            LayoutStyle::cls().imprint().initRefMethods<LayoutStyle>();
            
            
            // InkStyle
            InkStyle::cls().imprint().name = "InkStyle";
            InkStyle::cls().imprint().typeClass = STRUCT;
            InkStyle::cls().imprint().serializable = false;
            InkStyle::cls().imprint().isTypeObject = false;
            InkStyle::cls().imprint().constructor = make_unique<Method>(InkStyle::cls(), "InkStyle", Lref(), nullptr, ParamVector({ Param("style", Lref(Style::cls()), true, INPUT_PARAM) }));
            InkStyle::cls().imprint().poolInject = &InkStyle_poolinject;
            InkStyle::cls().imprint().lrefInject = &InkStyle_lrefinject;
            InkStyle::cls().imprint().makePool = &InkStyle_makePool;
            InkStyle::cls().imprint().initRefMethods<InkStyle>();
            
            
            // Style
            Style::cls().imprint().name = "Style";
            Style::cls().imprint().typeClass = OBJECT;
            Style::cls().imprint().serializable = false;
            Style::cls().imprint().isTypeObject = true;
            Style::cls().imprint().members.emplace_back(make_unique<Member>(Style::cls(), lref(&Style::name), typecls<string>(), 0, "name", &Style_name, nullptr, false, false, false, false));
            Style::cls().imprint().members.emplace_back(make_unique<Member>(Style::cls(), lref(&Style::base), Style::cls(), 1, "base", &Style_base, nullptr, false, false, false, false));
            Style::cls().imprint().members.emplace_back(make_unique<Member>(Style::cls(), lref(&Style::layout), LayoutStyle::cls(), 2, "layout", &Style_layout, nullptr, false, false, false, false));
            Style::cls().imprint().members.emplace_back(make_unique<Member>(Style::cls(), lref(&Style::skin), InkStyle::cls(), 3, "skin", &Style_skin, nullptr, false, false, false, false));
            Style::cls().imprint().members.emplace_back(make_unique<Member>(Style::cls(), lref(&Style::updated), typecls<size_t>(), 4, "updated", &Style_updated, &Style_setUpdated, true, false, false, false));
            
            
            // Widget
            Widget::cls().imprint().name = "Widget";
            Widget::cls().imprint().typeClass = OBJECT;
            Widget::cls().imprint().serializable = false;
            Widget::cls().imprint().isTypeObject = true;
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::parent), Wedge::cls(), 0, "parent", &Widget_parent, nullptr, false, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::container), Container::cls(), 1, "container", &Widget_container, nullptr, false, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::index), typecls<size_t>(), 2, "index", &Widget_index, nullptr, false, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::frame), Frame::cls(), 3, "frame", &Widget_frame, nullptr, false, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::state), typecls<WidgetState>(), 4, "state", &Widget_state, nullptr, false, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::style), Style::cls(), 5, "style", &Widget_style, &Widget_setStyle, true, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::label), typecls<string>(), 6, "label", &Widget_label, &Widget_setLabel, true, false, false, false));
            Widget::cls().imprint().members.emplace_back(make_unique<Member>(Widget::cls(), lref(&Widget::image), Image::cls(), 7, "image", &Widget_image, &Widget_setImage, true, false, false, false));
            
            
            // DockTab
            DockTab::cls().imprint().name = "DockTab";
            DockTab::cls().imprint().typeClass = OBJECT;
            DockTab::cls().imprint().serializable = false;
            DockTab::cls().imprint().isTypeObject = false;
            
            
            // Wedge
            Wedge::cls().imprint().name = "Wedge";
            Wedge::cls().imprint().typeClass = OBJECT;
            Wedge::cls().imprint().serializable = false;
            Wedge::cls().imprint().isTypeObject = false;
            Wedge::cls().imprint().members.emplace_back(make_unique<Member>(Wedge::cls(), lref(&Wedge::contents), typecls<std::vector<Widget*>>(), 0, "contents", &Wedge_contents, nullptr, false, true, false, false));
            
            
            // Spacer
            Spacer::cls().imprint().name = "Spacer";
            Spacer::cls().imprint().typeClass = OBJECT;
            Spacer::cls().imprint().serializable = false;
            Spacer::cls().imprint().isTypeObject = false;
            
            
            // Item
            Item::cls().imprint().name = "Item";
            Item::cls().imprint().typeClass = OBJECT;
            Item::cls().imprint().serializable = false;
            Item::cls().imprint().isTypeObject = false;
            
            
            // Label
            Label::cls().imprint().name = "Label";
            Label::cls().imprint().typeClass = OBJECT;
            Label::cls().imprint().serializable = false;
            Label::cls().imprint().isTypeObject = false;
            
            
            // Icon
            Icon::cls().imprint().name = "Icon";
            Icon::cls().imprint().typeClass = OBJECT;
            Icon::cls().imprint().serializable = false;
            Icon::cls().imprint().isTypeObject = false;
            
            
            // SliderKnob
            SliderKnob::cls().imprint().name = "SliderKnob";
            SliderKnob::cls().imprint().typeClass = OBJECT;
            SliderKnob::cls().imprint().serializable = false;
            SliderKnob::cls().imprint().isTypeObject = false;
            
            
            // FileBrowser
            FileBrowser::cls().imprint().name = "FileBrowser";
            FileBrowser::cls().imprint().typeClass = OBJECT;
            FileBrowser::cls().imprint().serializable = false;
            FileBrowser::cls().imprint().isTypeObject = false;
            
            
            // Container
            Container::cls().imprint().name = "Container";
            Container::cls().imprint().typeClass = OBJECT;
            Container::cls().imprint().serializable = false;
            Container::cls().imprint().isTypeObject = false;
            
            
            // Filler
            Filler::cls().imprint().name = "Filler";
            Filler::cls().imprint().typeClass = OBJECT;
            Filler::cls().imprint().serializable = false;
            Filler::cls().imprint().isTypeObject = false;
            
            
            // Decal
            Decal::cls().imprint().name = "Decal";
            Decal::cls().imprint().typeClass = OBJECT;
            Decal::cls().imprint().serializable = false;
            Decal::cls().imprint().isTypeObject = false;
            
            
            // Control
            Control::cls().imprint().name = "Control";
            Control::cls().imprint().typeClass = OBJECT;
            Control::cls().imprint().serializable = false;
            Control::cls().imprint().isTypeObject = false;
            
            
            // Text
            Text::cls().imprint().name = "Text";
            Text::cls().imprint().typeClass = OBJECT;
            Text::cls().imprint().serializable = false;
            Text::cls().imprint().isTypeObject = false;
            
            
            // Title
            Title::cls().imprint().name = "Title";
            Title::cls().imprint().typeClass = OBJECT;
            Title::cls().imprint().serializable = false;
            Title::cls().imprint().isTypeObject = false;
            
            
            // Button
            Button::cls().imprint().name = "Button";
            Button::cls().imprint().typeClass = OBJECT;
            Button::cls().imprint().serializable = false;
            Button::cls().imprint().isTypeObject = false;
            
            
            // Toggle
            Toggle::cls().imprint().name = "Toggle";
            Toggle::cls().imprint().typeClass = OBJECT;
            Toggle::cls().imprint().serializable = false;
            Toggle::cls().imprint().isTypeObject = false;
            
            
            // DropdownList
            DropdownList::cls().imprint().name = "DropdownList";
            DropdownList::cls().imprint().typeClass = OBJECT;
            DropdownList::cls().imprint().serializable = false;
            DropdownList::cls().imprint().isTypeObject = false;
            
            
            // ScrollerKnob
            ScrollerKnob::cls().imprint().name = "ScrollerKnob";
            ScrollerKnob::cls().imprint().typeClass = OBJECT;
            ScrollerKnob::cls().imprint().serializable = false;
            ScrollerKnob::cls().imprint().isTypeObject = false;
            
            
            // SliderDisplay
            SliderDisplay::cls().imprint().name = "SliderDisplay";
            SliderDisplay::cls().imprint().typeClass = OBJECT;
            SliderDisplay::cls().imprint().serializable = false;
            SliderDisplay::cls().imprint().isTypeObject = false;
            
            
            // Directory
            Directory::cls().imprint().name = "Directory";
            Directory::cls().imprint().typeClass = OBJECT;
            Directory::cls().imprint().serializable = false;
            Directory::cls().imprint().isTypeObject = false;
            
            
            // ExpandboxBody
            ExpandboxBody::cls().imprint().name = "ExpandboxBody";
            ExpandboxBody::cls().imprint().typeClass = OBJECT;
            ExpandboxBody::cls().imprint().serializable = false;
            ExpandboxBody::cls().imprint().isTypeObject = false;
            
            
            // Page
            Page::cls().imprint().name = "Page";
            Page::cls().imprint().typeClass = OBJECT;
            Page::cls().imprint().serializable = false;
            Page::cls().imprint().isTypeObject = false;
            
            
            // Dialog
            Dialog::cls().imprint().name = "Dialog";
            Dialog::cls().imprint().typeClass = OBJECT;
            Dialog::cls().imprint().serializable = false;
            Dialog::cls().imprint().isTypeObject = false;
            
            
            // Board
            Board::cls().imprint().name = "Board";
            Board::cls().imprint().typeClass = OBJECT;
            Board::cls().imprint().serializable = false;
            Board::cls().imprint().isTypeObject = false;
            
            
            // Row
            Row::cls().imprint().name = "Row";
            Row::cls().imprint().typeClass = OBJECT;
            Row::cls().imprint().serializable = false;
            Row::cls().imprint().isTypeObject = false;
            
            
            // Div
            Div::cls().imprint().name = "Div";
            Div::cls().imprint().typeClass = OBJECT;
            Div::cls().imprint().serializable = false;
            Div::cls().imprint().isTypeObject = false;
            
            
            // Stack
            Stack::cls().imprint().name = "Stack";
            Stack::cls().imprint().typeClass = OBJECT;
            Stack::cls().imprint().serializable = false;
            Stack::cls().imprint().isTypeObject = false;
            
            
            // Sheet
            Sheet::cls().imprint().name = "Sheet";
            Sheet::cls().imprint().typeClass = OBJECT;
            Sheet::cls().imprint().serializable = false;
            Sheet::cls().imprint().isTypeObject = false;
            
            
            // ScrollSheet
            ScrollSheet::cls().imprint().name = "ScrollSheet";
            ScrollSheet::cls().imprint().typeClass = OBJECT;
            ScrollSheet::cls().imprint().serializable = false;
            ScrollSheet::cls().imprint().isTypeObject = false;
            
            
            // Tabber
            Tabber::cls().imprint().name = "Tabber";
            Tabber::cls().imprint().typeClass = OBJECT;
            Tabber::cls().imprint().serializable = false;
            Tabber::cls().imprint().isTypeObject = false;
            
            
            // ColumnHeader
            ColumnHeader::cls().imprint().name = "ColumnHeader";
            ColumnHeader::cls().imprint().typeClass = OBJECT;
            ColumnHeader::cls().imprint().serializable = false;
            ColumnHeader::cls().imprint().isTypeObject = false;
            
            
            // Tree
            Tree::cls().imprint().name = "Tree";
            Tree::cls().imprint().typeClass = OBJECT;
            Tree::cls().imprint().serializable = false;
            Tree::cls().imprint().isTypeObject = false;
            
            
            // TypeIn
            TypeIn::cls().imprint().name = "TypeIn";
            TypeIn::cls().imprint().typeClass = OBJECT;
            TypeIn::cls().imprint().serializable = false;
            TypeIn::cls().imprint().isTypeObject = false;
            
            
            // Rectangle
            Rectangle::cls().imprint().name = "Rectangle";
            Rectangle::cls().imprint().typeClass = OBJECT;
            Rectangle::cls().imprint().serializable = false;
            Rectangle::cls().imprint().isTypeObject = false;
            
            
            // Cursor
            Cursor::cls().imprint().name = "Cursor";
            Cursor::cls().imprint().typeClass = OBJECT;
            Cursor::cls().imprint().serializable = false;
            Cursor::cls().imprint().isTypeObject = false;
            
            
            // RootSheet
            RootSheet::cls().imprint().name = "RootSheet";
            RootSheet::cls().imprint().typeClass = OBJECT;
            RootSheet::cls().imprint().serializable = false;
            RootSheet::cls().imprint().isTypeObject = false;
            
            
            // WrapControl
            WrapControl::cls().imprint().name = "WrapControl";
            WrapControl::cls().imprint().typeClass = OBJECT;
            WrapControl::cls().imprint().serializable = false;
            WrapControl::cls().imprint().isTypeObject = false;
            
            
            // Overlay
            Overlay::cls().imprint().name = "Overlay";
            Overlay::cls().imprint().typeClass = OBJECT;
            Overlay::cls().imprint().serializable = false;
            Overlay::cls().imprint().isTypeObject = false;
            
            
            // GridSheet
            GridSheet::cls().imprint().name = "GridSheet";
            GridSheet::cls().imprint().typeClass = OBJECT;
            GridSheet::cls().imprint().serializable = false;
            GridSheet::cls().imprint().isTypeObject = false;
            
            
            // ToolbarMover
            ToolbarMover::cls().imprint().name = "ToolbarMover";
            ToolbarMover::cls().imprint().typeClass = OBJECT;
            ToolbarMover::cls().imprint().serializable = false;
            ToolbarMover::cls().imprint().isTypeObject = false;
            
            
            // WindowSizer
            WindowSizer::cls().imprint().name = "WindowSizer";
            WindowSizer::cls().imprint().typeClass = OBJECT;
            WindowSizer::cls().imprint().serializable = false;
            WindowSizer::cls().imprint().isTypeObject = false;
            
            
            // WrapButton
            WrapButton::cls().imprint().name = "WrapButton";
            WrapButton::cls().imprint().typeClass = OBJECT;
            WrapButton::cls().imprint().serializable = false;
            WrapButton::cls().imprint().isTypeObject = false;
            
            
            // Checkbox
            Checkbox::cls().imprint().name = "Checkbox";
            Checkbox::cls().imprint().typeClass = OBJECT;
            Checkbox::cls().imprint().serializable = false;
            Checkbox::cls().imprint().isTypeObject = false;
            
            
            // DropdownToggle
            DropdownToggle::cls().imprint().name = "DropdownToggle";
            DropdownToggle::cls().imprint().typeClass = OBJECT;
            DropdownToggle::cls().imprint().serializable = false;
            DropdownToggle::cls().imprint().isTypeObject = false;
            
            
            // ScrollForward
            ScrollForward::cls().imprint().name = "ScrollForward";
            ScrollForward::cls().imprint().typeClass = OBJECT;
            ScrollForward::cls().imprint().serializable = false;
            ScrollForward::cls().imprint().isTypeObject = false;
            
            
            // ScrollBackward
            ScrollBackward::cls().imprint().name = "ScrollBackward";
            ScrollBackward::cls().imprint().typeClass = OBJECT;
            ScrollBackward::cls().imprint().serializable = false;
            ScrollBackward::cls().imprint().isTypeObject = false;
            
            
            // Scrollbar
            Scrollbar::cls().imprint().name = "Scrollbar";
            Scrollbar::cls().imprint().typeClass = OBJECT;
            Scrollbar::cls().imprint().serializable = false;
            Scrollbar::cls().imprint().isTypeObject = false;
            
            
            // Slider
            Slider::cls().imprint().name = "Slider";
            Slider::cls().imprint().typeClass = OBJECT;
            Slider::cls().imprint().serializable = false;
            Slider::cls().imprint().isTypeObject = false;
            
            
            // ExpandboxToggle
            ExpandboxToggle::cls().imprint().name = "ExpandboxToggle";
            ExpandboxToggle::cls().imprint().typeClass = OBJECT;
            ExpandboxToggle::cls().imprint().serializable = false;
            ExpandboxToggle::cls().imprint().isTypeObject = false;
            
            
            // Expandbox
            Expandbox::cls().imprint().name = "Expandbox";
            Expandbox::cls().imprint().typeClass = OBJECT;
            Expandbox::cls().imprint().serializable = false;
            Expandbox::cls().imprint().isTypeObject = false;
            
            
            // Layout
            Layout::cls().imprint().name = "Layout";
            Layout::cls().imprint().typeClass = OBJECT;
            Layout::cls().imprint().serializable = false;
            Layout::cls().imprint().isTypeObject = false;
            
            
            // Header
            Header::cls().imprint().name = "Header";
            Header::cls().imprint().typeClass = OBJECT;
            Header::cls().imprint().serializable = false;
            Header::cls().imprint().isTypeObject = false;
            
            
            // List
            List::cls().imprint().name = "List";
            List::cls().imprint().typeClass = OBJECT;
            List::cls().imprint().serializable = false;
            List::cls().imprint().isTypeObject = false;
            
            
            // LabelSequence
            LabelSequence::cls().imprint().name = "LabelSequence";
            LabelSequence::cls().imprint().typeClass = OBJECT;
            LabelSequence::cls().imprint().serializable = false;
            LabelSequence::cls().imprint().isTypeObject = false;
            
            
            // ButtonSequence
            ButtonSequence::cls().imprint().name = "ButtonSequence";
            ButtonSequence::cls().imprint().typeClass = OBJECT;
            ButtonSequence::cls().imprint().serializable = false;
            ButtonSequence::cls().imprint().isTypeObject = false;
            
            
            // ScrollPlan
            ScrollPlan::cls().imprint().name = "ScrollPlan";
            ScrollPlan::cls().imprint().typeClass = OBJECT;
            ScrollPlan::cls().imprint().serializable = false;
            ScrollPlan::cls().imprint().isTypeObject = false;
            
            
            // TabHeader
            TabHeader::cls().imprint().name = "TabHeader";
            TabHeader::cls().imprint().typeClass = OBJECT;
            TabHeader::cls().imprint().serializable = false;
            TabHeader::cls().imprint().isTypeObject = false;
            
            
            // Tab
            Tab::cls().imprint().name = "Tab";
            Tab::cls().imprint().typeClass = OBJECT;
            Tab::cls().imprint().serializable = false;
            Tab::cls().imprint().isTypeObject = false;
            
            
            // TabberHead
            TabberHead::cls().imprint().name = "TabberHead";
            TabberHead::cls().imprint().typeClass = OBJECT;
            TabberHead::cls().imprint().serializable = false;
            TabberHead::cls().imprint().isTypeObject = false;
            
            
            // TabberBody
            TabberBody::cls().imprint().name = "TabberBody";
            TabberBody::cls().imprint().typeClass = OBJECT;
            TabberBody::cls().imprint().serializable = false;
            TabberBody::cls().imprint().isTypeObject = false;
            
            
            // TableHead
            TableHead::cls().imprint().name = "TableHead";
            TableHead::cls().imprint().typeClass = OBJECT;
            TableHead::cls().imprint().serializable = false;
            TableHead::cls().imprint().isTypeObject = false;
            
            
            // Table
            Table::cls().imprint().name = "Table";
            Table::cls().imprint().typeClass = OBJECT;
            Table::cls().imprint().serializable = false;
            Table::cls().imprint().isTypeObject = false;
            
            
            // Textbox
            Textbox::cls().imprint().name = "Textbox";
            Textbox::cls().imprint().typeClass = OBJECT;
            Textbox::cls().imprint().serializable = false;
            Textbox::cls().imprint().isTypeObject = false;
            
            
            // WValue
            WValue::cls().imprint().name = "WValue";
            WValue::cls().imprint().typeClass = OBJECT;
            WValue::cls().imprint().serializable = false;
            WValue::cls().imprint().isTypeObject = false;
            
            
            // Tooltip
            Tooltip::cls().imprint().name = "Tooltip";
            Tooltip::cls().imprint().typeClass = OBJECT;
            Tooltip::cls().imprint().serializable = false;
            Tooltip::cls().imprint().isTypeObject = false;
            
            
            // Placeholder
            Placeholder::cls().imprint().name = "Placeholder";
            Placeholder::cls().imprint().typeClass = OBJECT;
            Placeholder::cls().imprint().serializable = false;
            Placeholder::cls().imprint().isTypeObject = false;
            
            
            // Docksection
            Docksection::cls().imprint().name = "Docksection";
            Docksection::cls().imprint().typeClass = OBJECT;
            Docksection::cls().imprint().serializable = false;
            Docksection::cls().imprint().isTypeObject = false;
            
            
            // Dockline
            Dockline::cls().imprint().name = "Dockline";
            Dockline::cls().imprint().typeClass = OBJECT;
            Dockline::cls().imprint().serializable = false;
            Dockline::cls().imprint().isTypeObject = false;
            
            
            // Tooldock
            Tooldock::cls().imprint().name = "Tooldock";
            Tooldock::cls().imprint().typeClass = OBJECT;
            Tooldock::cls().imprint().serializable = false;
            Tooldock::cls().imprint().isTypeObject = false;
            
            
            // Toolbar
            Toolbar::cls().imprint().name = "Toolbar";
            Toolbar::cls().imprint().typeClass = OBJECT;
            Toolbar::cls().imprint().serializable = false;
            Toolbar::cls().imprint().isTypeObject = false;
            
            
            // CloseButton
            CloseButton::cls().imprint().name = "CloseButton";
            CloseButton::cls().imprint().typeClass = OBJECT;
            CloseButton::cls().imprint().serializable = false;
            CloseButton::cls().imprint().isTypeObject = false;
            
            
            // WindowHeader
            WindowHeader::cls().imprint().name = "WindowHeader";
            WindowHeader::cls().imprint().typeClass = OBJECT;
            WindowHeader::cls().imprint().serializable = false;
            WindowHeader::cls().imprint().isTypeObject = false;
            
            
            // WindowSizerLeft
            WindowSizerLeft::cls().imprint().name = "WindowSizerLeft";
            WindowSizerLeft::cls().imprint().typeClass = OBJECT;
            WindowSizerLeft::cls().imprint().serializable = false;
            WindowSizerLeft::cls().imprint().isTypeObject = false;
            
            
            // WindowSizerRight
            WindowSizerRight::cls().imprint().name = "WindowSizerRight";
            WindowSizerRight::cls().imprint().typeClass = OBJECT;
            WindowSizerRight::cls().imprint().serializable = false;
            WindowSizerRight::cls().imprint().isTypeObject = false;
            
            
            // WindowFooter
            WindowFooter::cls().imprint().name = "WindowFooter";
            WindowFooter::cls().imprint().typeClass = OBJECT;
            WindowFooter::cls().imprint().serializable = false;
            WindowFooter::cls().imprint().isTypeObject = false;
            
            
            // WindowBody
            WindowBody::cls().imprint().name = "WindowBody";
            WindowBody::cls().imprint().typeClass = OBJECT;
            WindowBody::cls().imprint().serializable = false;
            WindowBody::cls().imprint().isTypeObject = false;
            
            
            // Window
            Window::cls().imprint().name = "Window";
            Window::cls().imprint().typeClass = OBJECT;
            Window::cls().imprint().serializable = false;
            Window::cls().imprint().isTypeObject = false;
            
            
            // MultiButton
            MultiButton::cls().imprint().name = "MultiButton";
            MultiButton::cls().imprint().typeClass = OBJECT;
            MultiButton::cls().imprint().serializable = false;
            MultiButton::cls().imprint().isTypeObject = false;
            
            
            // Dropdown
            Dropdown::cls().imprint().name = "Dropdown";
            Dropdown::cls().imprint().typeClass = OBJECT;
            Dropdown::cls().imprint().serializable = false;
            Dropdown::cls().imprint().isTypeObject = false;
            
            
            // Scroller
            Scroller::cls().imprint().name = "Scroller";
            Scroller::cls().imprint().typeClass = OBJECT;
            Scroller::cls().imprint().serializable = false;
            Scroller::cls().imprint().isTypeObject = false;
            
            
            // ExpandboxHeader
            ExpandboxHeader::cls().imprint().name = "ExpandboxHeader";
            ExpandboxHeader::cls().imprint().typeClass = OBJECT;
            ExpandboxHeader::cls().imprint().serializable = false;
            ExpandboxHeader::cls().imprint().isTypeObject = false;
            
            
            // SelectList
            SelectList::cls().imprint().name = "SelectList";
            SelectList::cls().imprint().typeClass = OBJECT;
            SelectList::cls().imprint().serializable = false;
            SelectList::cls().imprint().isTypeObject = false;
            
            
            // SortList
            SortList::cls().imprint().name = "SortList";
            SortList::cls().imprint().typeClass = OBJECT;
            SortList::cls().imprint().serializable = false;
            SortList::cls().imprint().isTypeObject = false;
            
            
            // ScrollZone
            ScrollZone::cls().imprint().name = "ScrollZone";
            ScrollZone::cls().imprint().typeClass = OBJECT;
            ScrollZone::cls().imprint().serializable = false;
            ScrollZone::cls().imprint().isTypeObject = false;
            
            
            // TreeNode
            TreeNode::cls().imprint().name = "TreeNode";
            TreeNode::cls().imprint().typeClass = OBJECT;
            TreeNode::cls().imprint().serializable = false;
            TreeNode::cls().imprint().isTypeObject = false;
            
            
            // Inputtoy::Colour
            Input<toy::Colour>::cls().imprint().name = "Input<toy::Colour>";
            Input<toy::Colour>::cls().imprint().typeClass = OBJECT;
            Input<toy::Colour>::cls().imprint().serializable = false;
            Input<toy::Colour>::cls().imprint().isTypeObject = false;
            
            
            // Inputbool
            Input<bool>::cls().imprint().name = "Input<bool>";
            Input<bool>::cls().imprint().typeClass = OBJECT;
            Input<bool>::cls().imprint().serializable = false;
            Input<bool>::cls().imprint().isTypeObject = false;
            
            
            // Inputstring
            Input<string>::cls().imprint().name = "Input<string>";
            Input<string>::cls().imprint().typeClass = OBJECT;
            Input<string>::cls().imprint().serializable = false;
            Input<string>::cls().imprint().isTypeObject = false;
            
            
            // MasterDockline
            MasterDockline::cls().imprint().name = "MasterDockline";
            MasterDockline::cls().imprint().typeClass = OBJECT;
            MasterDockline::cls().imprint().serializable = false;
            MasterDockline::cls().imprint().isTypeObject = false;
            
            
            // Dockspace
            Dockspace::cls().imprint().name = "Dockspace";
            Dockspace::cls().imprint().typeClass = OBJECT;
            Dockspace::cls().imprint().serializable = false;
            Dockspace::cls().imprint().isTypeObject = false;
            
            
            // Menubar
            Menubar::cls().imprint().name = "Menubar";
            Menubar::cls().imprint().typeClass = OBJECT;
            Menubar::cls().imprint().serializable = false;
            Menubar::cls().imprint().isTypeObject = false;
            
            
            // DropdownHead
            DropdownHead::cls().imprint().name = "DropdownHead";
            DropdownHead::cls().imprint().typeClass = OBJECT;
            DropdownHead::cls().imprint().serializable = false;
            DropdownHead::cls().imprint().isTypeObject = false;
            
            
            // DropdownChoice
            DropdownChoice::cls().imprint().name = "DropdownChoice";
            DropdownChoice::cls().imprint().typeClass = OBJECT;
            DropdownChoice::cls().imprint().serializable = false;
            DropdownChoice::cls().imprint().isTypeObject = false;
            
            
            // DropdownInput
            DropdownInput::cls().imprint().name = "DropdownInput";
            DropdownInput::cls().imprint().typeClass = OBJECT;
            DropdownInput::cls().imprint().serializable = false;
            DropdownInput::cls().imprint().isTypeObject = false;
            
            
            // Dir
            Dir::cls().imprint().name = "Dir";
            Dir::cls().imprint().typeClass = OBJECT;
            Dir::cls().imprint().serializable = false;
            Dir::cls().imprint().isTypeObject = false;
            
            
            // File
            File::cls().imprint().name = "File";
            File::cls().imprint().typeClass = OBJECT;
            File::cls().imprint().serializable = false;
            File::cls().imprint().isTypeObject = false;
            
            
            // FileNode
            FileNode::cls().imprint().name = "FileNode";
            FileNode::cls().imprint().typeClass = OBJECT;
            FileNode::cls().imprint().serializable = false;
            FileNode::cls().imprint().isTypeObject = false;
            
            
            // DirectoryNode
            DirectoryNode::cls().imprint().name = "DirectoryNode";
            DirectoryNode::cls().imprint().typeClass = OBJECT;
            DirectoryNode::cls().imprint().serializable = false;
            DirectoryNode::cls().imprint().isTypeObject = false;
            
            
            // Menu
            Menu::cls().imprint().name = "Menu";
            Menu::cls().imprint().typeClass = OBJECT;
            Menu::cls().imprint().serializable = false;
            Menu::cls().imprint().isTypeObject = false;
            
            
            // ToolButton
            ToolButton::cls().imprint().name = "ToolButton";
            ToolButton::cls().imprint().typeClass = OBJECT;
            ToolButton::cls().imprint().serializable = false;
            ToolButton::cls().imprint().isTypeObject = false;
            
            
            
            types.push_back(&Image::cls());
            types.push_back(&Label::cls());
            types.push_back(&Text::cls());
            types.push_back(&Title::cls());
            types.push_back(&Icon::cls());
            types.push_back(&Button::cls());
            types.push_back(&WrapButton::cls());
            types.push_back(&MultiButton::cls());
            types.push_back(&Toggle::cls());
            types.push_back(&Checkbox::cls());
            types.push_back(&DropdownHead::cls());
            types.push_back(&DropdownToggle::cls());
            types.push_back(&DropdownChoice::cls());
            types.push_back(&DropdownList::cls());
            types.push_back(&Dropdown::cls());
            types.push_back(&DropdownInput::cls());
            types.push_back(&Scroller::cls());
            types.push_back(&ScrollerKnob::cls());
            types.push_back(&ScrollForward::cls());
            types.push_back(&ScrollBackward::cls());
            types.push_back(&Scrollbar::cls());
            types.push_back(&SliderKnob::cls());
            types.push_back(&Slider::cls());
            types.push_back(&SliderDisplay::cls());
            types.push_back(&StatSlider<float>::cls());
            types.push_back(&StatSlider<int>::cls());
            types.push_back(&Dir::cls());
            types.push_back(&File::cls());
            types.push_back(&Directory::cls());
            types.push_back(&FileBrowser::cls());
            types.push_back(&FileNode::cls());
            types.push_back(&DirectoryNode::cls());
            types.push_back(&ExpandboxHeader::cls());
            types.push_back(&ExpandboxBody::cls());
            types.push_back(&ExpandboxToggle::cls());
            types.push_back(&Expandbox::cls());
            types.push_back(&Page::cls());
            types.push_back(&Dialog::cls());
            types.push_back(&Board::cls());
            types.push_back(&Layout::cls());
            types.push_back(&Row::cls());
            types.push_back(&Div::cls());
            types.push_back(&Stack::cls());
            types.push_back(&Sheet::cls());
            types.push_back(&Header::cls());
            types.push_back(&List::cls());
            types.push_back(&SelectList::cls());
            types.push_back(&LabelSequence::cls());
            types.push_back(&ButtonSequence::cls());
            types.push_back(&SortList::cls());
            types.push_back(&ScrollZone::cls());
            types.push_back(&ScrollSheet::cls());
            types.push_back(&ScrollPlan::cls());
            types.push_back(&TabHeader::cls());
            types.push_back(&Tab::cls());
            types.push_back(&TabberHead::cls());
            types.push_back(&TabberBody::cls());
            types.push_back(&Tabber::cls());
            types.push_back(&TableHead::cls());
            types.push_back(&ColumnHeader::cls());
            types.push_back(&Table::cls());
            types.push_back(&TreeNode::cls());
            types.push_back(&Tree::cls());
            types.push_back(&Input<toy::Colour>::cls());
            types.push_back(&Textbox::cls());
            types.push_back(&TypeIn::cls());
            types.push_back(&Input<unsigned int>::cls());
            types.push_back(&Input<int>::cls());
            types.push_back(&Input<float>::cls());
            types.push_back(&Input<double>::cls());
            types.push_back(&Input<bool>::cls());
            types.push_back(&Input<string>::cls());
            types.push_back(&WValue::cls());
            types.push_back(&Frame::cls());
            types.push_back(&typecls<Dimension>());
            types.push_back(&typecls<Direction>());
            types.push_back(&typecls<Pivot>());
            types.push_back(&typecls<Align>());
            types.push_back(&typecls<FrameType>());
            types.push_back(&typecls<AutoLayout>());
            types.push_back(&typecls<Flow>());
            types.push_back(&typecls<Sizing>());
            types.push_back(&typecls<Space>());
            types.push_back(&typecls<Clipping>());
            types.push_back(&typecls<Opacity>());
            types.push_back(&BoxFloat::cls());
            types.push_back(&ImageSkin::cls());
            types.push_back(&Shadow::cls());
            types.push_back(&Paint::cls());
            types.push_back(&LayoutStyle::cls());
            types.push_back(&InkStyle::cls());
            types.push_back(&Style::cls());
            types.push_back(&Tooltip::cls());
            types.push_back(&Rectangle::cls());
            types.push_back(&Cursor::cls());
            types.push_back(&RootSheet::cls());
            types.push_back(&Wedge::cls());
            types.push_back(&typecls<std::vector<Widget*>>());
            types.push_back(&Container::cls());
            types.push_back(&WrapControl::cls());
            types.push_back(&Spacer::cls());
            types.push_back(&Filler::cls());
            types.push_back(&Decal::cls());
            types.push_back(&Overlay::cls());
            types.push_back(&GridSheet::cls());
            types.push_back(&typecls<WidgetState>());
            types.push_back(&Widget::cls());
            types.push_back(&Item::cls());
            types.push_back(&Control::cls());
            types.push_back(&Placeholder::cls());
            types.push_back(&DockTab::cls());
            types.push_back(&Docksection::cls());
            types.push_back(&Dockline::cls());
            types.push_back(&MasterDockline::cls());
            types.push_back(&Dockspace::cls());
            types.push_back(&Menu::cls());
            types.push_back(&Menubar::cls());
            types.push_back(&ToolButton::cls());
            types.push_back(&Tooldock::cls());
            types.push_back(&ToolbarMover::cls());
            types.push_back(&Toolbar::cls());
            types.push_back(&CloseButton::cls());
            types.push_back(&WindowHeader::cls());
            types.push_back(&WindowSizer::cls());
            types.push_back(&WindowSizerLeft::cls());
            types.push_back(&WindowSizerRight::cls());
            types.push_back(&WindowFooter::cls());
            types.push_back(&WindowBody::cls());
            types.push_back(&Window::cls());
        
        }

		static toyui instance;
        
    public:
        static toyui& module() { return instance; }
	};
    
	toyui toyui::instance;
#endif // IMPRINT_DEF_FILE
}

#endif // TOYUI_IMPRINTS_H
