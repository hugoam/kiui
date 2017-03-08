

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
#include <toyutil/Memory/Memory.h>

namespace toy
{
    
#ifdef IMPRINT_DEF_FILE
    Object& BoxFloat_create(BoxFloat* at, LrefVector& args) {  new(at) BoxFloat( args[0]->any<float>()->copy(), args[1]->any<float>()->copy(), args[2]->any<float>()->copy(), args[3]->any<float>()->copy() ); return *at; }
    Object& BoxFloat_proto_poolinject(AbstractPool& pool, LrefVector& args) { return BoxFloat_create(pool.as<Pool<BoxFloat>>().alloc(), args); }
    Object& BoxFloat_proto_lrefinject(Lref& lref, LrefVector& args) { return BoxFloat_create(&lref->as<BoxFloat>(), args); }
    AbstractPool* BoxFloat_makePool() { return new Pool<BoxFloat>(); }

    Object& InkStyle_create(InkStyle* at, LrefVector& args) {  new(at) InkStyle( &args[0]->as<Style>() ); return *at; }
    Object& InkStyle_proto_poolinject(AbstractPool& pool, LrefVector& args) { return InkStyle_create(pool.as<Pool<InkStyle>>().alloc(), args); }
    Object& InkStyle_proto_lrefinject(Lref& lref, LrefVector& args) { return InkStyle_create(&lref->as<InkStyle>(), args); }
    AbstractPool* InkStyle_makePool() { return new Pool<InkStyle>(); }

    






























	void BoxFloat_x0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x0()); }
	void BoxFloat_setX0(Object& object, const Lref& ref) { object.as<BoxFloat>().setX0(ref->any<float>()->copy()); }
	void BoxFloat_y0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y0()); }
	void BoxFloat_setY0(Object& object, const Lref& ref) { object.as<BoxFloat>().setY0(ref->any<float>()->copy()); }
	void BoxFloat_x1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x1()); }
	void BoxFloat_setX1(Object& object, const Lref& ref) { object.as<BoxFloat>().setX1(ref->any<float>()->copy()); }
	void BoxFloat_y1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y1()); }
	void BoxFloat_setY1(Object& object, const Lref& ref) { object.as<BoxFloat>().setY1(ref->any<float>()->copy()); }
	void BoxFloat_x(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().x()); }
	void BoxFloat_y(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().y()); }
	void BoxFloat_w(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().w()); }
	void BoxFloat_h(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().h()); }
	void BoxFloat_xx(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().xx()); }
	void BoxFloat_xy(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().xy()); }
	void BoxFloat_yx(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().yx()); }
	void BoxFloat_yy(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().yy()); }
	void BoxFloat_v0(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v0()); }
	void BoxFloat_v1(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v1()); }
	void BoxFloat_v2(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v2()); }
	void BoxFloat_v3(Object& object, Lref& ref) { ref->set<float>(object.as<BoxFloat>().v3()); }

	void ImageSkin_d_image(Object& object, Lref& ref) { ref->setobject(*object.as<ImageSkin>().d_image); }
    Object* ImageSkin_d_image_object(Object& object) { return object.as<ImageSkin>().d_image; }
	void ImageSkin_setD_image(Object& object, const Lref& ref) { object.as<ImageSkin>().d_image = &ref->as<Image>(); }
	void ImageSkin_d_filetype(Object& object, Lref& ref) { ref->set<string>(object.as<ImageSkin>().d_filetype); }
	void ImageSkin_setD_filetype(Object& object, const Lref& ref) { object.as<ImageSkin>().d_filetype = ref->any<string>()->copy(); }
	void ImageSkin_d_top(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_top); }
	void ImageSkin_setD_top(Object& object, const Lref& ref) { object.as<ImageSkin>().d_top = ref->any<int>()->copy(); }
	void ImageSkin_d_right(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_right); }
	void ImageSkin_setD_right(Object& object, const Lref& ref) { object.as<ImageSkin>().d_right = ref->any<int>()->copy(); }
	void ImageSkin_d_bottom(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_bottom); }
	void ImageSkin_setD_bottom(Object& object, const Lref& ref) { object.as<ImageSkin>().d_bottom = ref->any<int>()->copy(); }
	void ImageSkin_d_left(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_left); }
	void ImageSkin_setD_left(Object& object, const Lref& ref) { object.as<ImageSkin>().d_left = ref->any<int>()->copy(); }
	void ImageSkin_d_margin(Object& object, Lref& ref) { ref->set<int>(object.as<ImageSkin>().d_margin); }
	void ImageSkin_setD_margin(Object& object, const Lref& ref) { object.as<ImageSkin>().d_margin = ref->any<int>()->copy(); }
	void ImageSkin_d_stretch(Object& object, Lref& ref) { ref->set<Dimension>(object.as<ImageSkin>().d_stretch); }
	void ImageSkin_setD_stretch(Object& object, const Lref& ref) { object.as<ImageSkin>().d_stretch = ref->any<Dimension>()->copy(); }


	void LayoutStyle_d_updated(Object& object, Lref& ref) { ref->set<size_t>(object.as<LayoutStyle>().d_updated); }
	void LayoutStyle_setD_updated(Object& object, const Lref& ref) { object.as<LayoutStyle>().d_updated = ref->any<size_t>()->copy(); }


	void Style_name(Object& object, Lref& ref) { ref->set<string>(object.as<Style>().name()); }
	void Style_base(Object& object, Lref& ref) { ref->setobject(*object.as<Style>().base()); }
    Object* Style_base_object(Object& object) { return object.as<Style>().base(); }
	void Style_layout(Object& object, Lref& ref) { ref->setobject(object.as<Style>().layout()); }
    Object* Style_layout_object(Object& object) { return &object.as<Style>().layout(); }
	void Style_skin(Object& object, Lref& ref) { ref->setobject(object.as<Style>().skin()); }
    Object* Style_skin_object(Object& object) { return &object.as<Style>().skin(); }
	void Style_updated(Object& object, Lref& ref) { ref->set<size_t>(object.as<Style>().updated()); }
	void Style_setUpdated(Object& object, const Lref& ref) { object.as<Style>().setUpdated(ref->any<size_t>()->copy()); }















	void Widget_parent(Object& object, Lref& ref) { ref->setobject(*object.as<Widget>().parent()); }
    Object* Widget_parent_object(Object& object) { return object.as<Widget>().parent(); }
	void Widget_container(Object& object, Lref& ref) { ref->setobject(*object.as<Widget>().container()); }
    Object* Widget_container_object(Object& object) { return object.as<Widget>().container(); }
	void Widget_index(Object& object, Lref& ref) { ref->set<size_t>(object.as<Widget>().index()); }
	void Widget_frame(Object& object, Lref& ref) { ref->setobject(object.as<Widget>().frame()); }
    Object* Widget_frame_object(Object& object) { return &object.as<Widget>().frame(); }
	void Widget_state(Object& object, Lref& ref) { ref->set<WidgetState>(object.as<Widget>().state()); }
	void Widget_style(Object& object, Lref& ref) { ref->setobject(object.as<Widget>().style()); }
    Object* Widget_style_object(Object& object) { return &object.as<Widget>().style(); }
	void Widget_setStyle(Object& object, const Lref& ref) { object.as<Widget>().setStyle(ref->as<Style>()); }
















    
    
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
        
            // Stores
        
        
            // Image
            Image::cls().imprint().setup("Image", OBJECT);
            Image::cls().imprint().initObject(false);
            
            // Checkbox
            Checkbox::cls().imprint().setup("Checkbox", OBJECT);
            Checkbox::cls().imprint().initObject(false);
            
            // Scrollbar
            Scrollbar::cls().imprint().setup("Scrollbar", OBJECT);
            Scrollbar::cls().imprint().initObject(false);
            
            // StatSliderfloat
            StatSlider<float>::cls().imprint().setup("StatSlider<float>", OBJECT);
            StatSlider<float>::cls().imprint().initObject(false);
            
            // StatSliderint
            StatSlider<int>::cls().imprint().setup("StatSlider<int>", OBJECT);
            StatSlider<int>::cls().imprint().initObject(false);
            
            // Dir
            Dir::cls().imprint().setup("Dir", OBJECT);
            Dir::cls().imprint().initObject(false);
            
            // File
            File::cls().imprint().setup("File", OBJECT);
            File::cls().imprint().initObject(false);
            
            // Directory
            Directory::cls().imprint().setup("Directory", OBJECT);
            Directory::cls().imprint().initObject(false);
            
            // FileBrowser
            FileBrowser::cls().imprint().setup("FileBrowser", OBJECT);
            FileBrowser::cls().imprint().initObject(false);
            
            // FileNode
            FileNode::cls().imprint().setup("FileNode", OBJECT);
            FileNode::cls().imprint().initObject(false);
            
            // DirectoryNode
            DirectoryNode::cls().imprint().setup("DirectoryNode", OBJECT);
            DirectoryNode::cls().imprint().initObject(false);
            
            // Tab
            Tab::cls().imprint().setup("Tab", OBJECT);
            Tab::cls().imprint().initObject(false);
            
            // TabberHead
            TabberHead::cls().imprint().setup("TabberHead", OBJECT);
            TabberHead::cls().imprint().initObject(false);
            
            // TabberBody
            TabberBody::cls().imprint().setup("TabberBody", OBJECT);
            TabberBody::cls().imprint().initObject(false);
            
            // Tabber
            Tabber::cls().imprint().setup("Tabber", OBJECT);
            Tabber::cls().imprint().initObject(false);
            
            // TableHead
            TableHead::cls().imprint().setup("TableHead", OBJECT);
            TableHead::cls().imprint().initObject(false);
            
            // ColumnHeader
            ColumnHeader::cls().imprint().setup("ColumnHeader", OBJECT);
            ColumnHeader::cls().imprint().initObject(false);
            
            // Table
            Table::cls().imprint().setup("Table", OBJECT);
            Table::cls().imprint().initObject(false);
            
            // TreeNode
            TreeNode::cls().imprint().setup("TreeNode", OBJECT);
            TreeNode::cls().imprint().initObject(false);
            
            // Tree
            Tree::cls().imprint().setup("Tree", OBJECT);
            Tree::cls().imprint().initObject(false);
            
            // Inputtoy::Colour
            Input<toy::Colour>::cls().imprint().setup("Input<toy::Colour>", OBJECT);
            Input<toy::Colour>::cls().imprint().initObject(false);
            
            // Textbox
            Textbox::cls().imprint().setup("Textbox", OBJECT);
            Textbox::cls().imprint().initObject(false);
            
            // TypeIn
            TypeIn::cls().imprint().setup("TypeIn", OBJECT);
            TypeIn::cls().imprint().initObject(false);
            
            // Inputunsigned int
            Input<unsigned int>::cls().imprint().setup("Input<unsigned int>", OBJECT);
            Input<unsigned int>::cls().imprint().initObject(false);
            
            // Inputint
            Input<int>::cls().imprint().setup("Input<int>", OBJECT);
            Input<int>::cls().imprint().initObject(false);
            
            // Inputfloat
            Input<float>::cls().imprint().setup("Input<float>", OBJECT);
            Input<float>::cls().imprint().initObject(false);
            
            // Inputdouble
            Input<double>::cls().imprint().setup("Input<double>", OBJECT);
            Input<double>::cls().imprint().initObject(false);
            
            // Inputbool
            Input<bool>::cls().imprint().setup("Input<bool>", OBJECT);
            Input<bool>::cls().imprint().initObject(false);
            
            // Inputstring
            Input<string>::cls().imprint().setup("Input<string>", OBJECT);
            Input<string>::cls().imprint().initObject(false);
            
            // Frame
            Frame::cls().imprint().setup("Frame", OBJECT);
            Frame::cls().imprint().initObject(false);
            
            // BoxFloat
            BoxFloat::cls().imprint().setup("BoxFloat", STRUCT);
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 0, "x0", &BoxFloat_x0, &BoxFloat_setX0, false, true));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 1, "y0", &BoxFloat_y0, &BoxFloat_setY0, false, true));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 2, "x1", &BoxFloat_x1, &BoxFloat_setX1, false, true));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 3, "y1", &BoxFloat_y1, &BoxFloat_setY1, false, true));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 4, "x", &BoxFloat_x, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 5, "y", &BoxFloat_y, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 6, "w", &BoxFloat_w, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 7, "h", &BoxFloat_h, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 8, "xx", &BoxFloat_xx, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 9, "xy", &BoxFloat_xy, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 10, "yx", &BoxFloat_yx, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 11, "yy", &BoxFloat_yy, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 12, "v0", &BoxFloat_v0, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 13, "v1", &BoxFloat_v1, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 14, "v2", &BoxFloat_v2, nullptr, false, false));
            BoxFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 15, "v3", &BoxFloat_v3, nullptr, false, false));
            BoxFloat::cls().imprint().initRefMethods<BoxFloat>();
            BoxFloat::cls().imprint().setConstructor(make_unique<Method>(BoxFloat::cls(), "BoxFloat", nullptr, ParamVector({ Param("x0", lref(float()), INPUT_PARAM), Param("y0", lref(float()), INPUT_PARAM), Param("x1", lref(float()), INPUT_PARAM), Param("y1", lref(float()), INPUT_PARAM) })));
            BoxFloat::cls().imprint().initInjectors(&BoxFloat_proto_poolinject, &BoxFloat_proto_lrefinject, &BoxFloat_makePool);
            BoxFloat::cls().imprint().initObject(false);
            
            // ImageSkin
            ImageSkin::cls().imprint().setup("ImageSkin", STRUCT);
            ImageSkin::cls().imprint().addMember(make_unique<Member>(Image::cls(), 0, "d_image", &ImageSkin_d_image, &ImageSkin_setD_image, false, true, &ImageSkin_d_image_object));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<string>(), 1, "d_filetype", &ImageSkin_d_filetype, &ImageSkin_setD_filetype, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<int>(), 2, "d_top", &ImageSkin_d_top, &ImageSkin_setD_top, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<int>(), 3, "d_right", &ImageSkin_d_right, &ImageSkin_setD_right, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<int>(), 4, "d_bottom", &ImageSkin_d_bottom, &ImageSkin_setD_bottom, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<int>(), 5, "d_left", &ImageSkin_d_left, &ImageSkin_setD_left, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<int>(), 6, "d_margin", &ImageSkin_d_margin, &ImageSkin_setD_margin, false, true));
            ImageSkin::cls().imprint().addMember(make_unique<Member>(typecls<Dimension>(), 7, "d_stretch", &ImageSkin_d_stretch, &ImageSkin_setD_stretch, false, true));
            ImageSkin::cls().imprint().initRefMethods<ImageSkin>();
            ImageSkin::cls().imprint().initObject(false);
            
            // Shadow
            Shadow::cls().imprint().setup("Shadow", OBJECT);
            Shadow::cls().imprint().initObject(false);
            
            // LayoutStyle
            LayoutStyle::cls().imprint().setup("LayoutStyle", OBJECT);
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<size_t>(), 0, "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, false, true));
            LayoutStyle::cls().imprint().initObject(false);
            
            // InkStyle
            InkStyle::cls().imprint().setup("InkStyle", OBJECT);
            InkStyle::cls().imprint().setConstructor(make_unique<Method>(InkStyle::cls(), "InkStyle", nullptr, ParamVector({ Param("style", Lref(Style::cls()), INPUT_PARAM) })));
            InkStyle::cls().imprint().initInjectors(&InkStyle_proto_poolinject, &InkStyle_proto_lrefinject, &InkStyle_makePool);
            InkStyle::cls().imprint().initObject(false);
            
            // Style
            Style::cls().imprint().setup("Style", OBJECT);
            Style::cls().imprint().addMember(make_unique<Member>(typecls<string>(), 0, "name", &Style_name, nullptr, false, false));
            Style::cls().imprint().addMember(make_unique<Member>(Style::cls(), 1, "base", &Style_base, nullptr, false, false, &Style_base_object));
            Style::cls().imprint().addMember(make_unique<Member>(LayoutStyle::cls(), 2, "layout", &Style_layout, nullptr, true, false, &Style_layout_object));
            Style::cls().imprint().addMember(make_unique<Member>(InkStyle::cls(), 3, "skin", &Style_skin, nullptr, true, false, &Style_skin_object));
            Style::cls().imprint().addMember(make_unique<Member>(typecls<size_t>(), 4, "updated", &Style_updated, &Style_setUpdated, false, true));
            Style::cls().imprint().initObject(false);
            
            // Tooltip
            Tooltip::cls().imprint().setup("Tooltip", OBJECT);
            Tooltip::cls().imprint().initObject(false);
            
            // Cursor
            Cursor::cls().imprint().setup("Cursor", OBJECT);
            Cursor::cls().imprint().initObject(false);
            
            // Page
            Page::cls().imprint().setup("Page", OBJECT);
            Page::cls().imprint().initObject(false);
            
            // RootSheet
            RootSheet::cls().imprint().setup("RootSheet", OBJECT);
            RootSheet::cls().imprint().initObject(false);
            
            // ScrollZone
            ScrollZone::cls().imprint().setup("ScrollZone", OBJECT);
            ScrollZone::cls().imprint().initObject(false);
            
            // ScrollSheet
            ScrollSheet::cls().imprint().setup("ScrollSheet", OBJECT);
            ScrollSheet::cls().imprint().initObject(false);
            
            // ScrollContainer
            ScrollContainer::cls().imprint().setup("ScrollContainer", OBJECT);
            ScrollContainer::cls().imprint().initObject(false);
            
            // ScrollPlan
            ScrollPlan::cls().imprint().setup("ScrollPlan", OBJECT);
            ScrollPlan::cls().imprint().initObject(false);
            
            // Wedge
            Wedge::cls().imprint().setup("Wedge", OBJECT);
            Wedge::cls().imprint().initObject(false);
            
            // Container
            Container::cls().imprint().setup("Container", OBJECT);
            Container::cls().imprint().initObject(false);
            
            // WrapControl
            WrapControl::cls().imprint().setup("WrapControl", OBJECT);
            WrapControl::cls().imprint().initObject(false);
            
            // Decal
            Decal::cls().imprint().setup("Decal", OBJECT);
            Decal::cls().imprint().initObject(false);
            
            // Overlay
            Overlay::cls().imprint().setup("Overlay", OBJECT);
            Overlay::cls().imprint().initObject(false);
            
            // GridSheet
            GridSheet::cls().imprint().setup("GridSheet", OBJECT);
            GridSheet::cls().imprint().initObject(false);
            
            // Widget
            Widget::cls().imprint().setup("Widget", OBJECT);
            Widget::cls().imprint().addMember(make_unique<Member>(Wedge::cls(), 0, "parent", &Widget_parent, nullptr, false, false, &Widget_parent_object));
            Widget::cls().imprint().addMember(make_unique<Member>(Container::cls(), 1, "container", &Widget_container, nullptr, false, false, &Widget_container_object));
            Widget::cls().imprint().addMember(make_unique<Member>(typecls<size_t>(), 2, "index", &Widget_index, nullptr, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Frame::cls(), 3, "frame", &Widget_frame, nullptr, true, false, &Widget_frame_object));
            Widget::cls().imprint().addMember(make_unique<Member>(typecls<WidgetState>(), 4, "state", &Widget_state, nullptr, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Style::cls(), 5, "style", &Widget_style, &Widget_setStyle, true, true, &Widget_style_object));
            Widget::cls().imprint().initObject(false);
            
            // Placeholder
            Placeholder::cls().imprint().setup("Placeholder", OBJECT);
            Placeholder::cls().imprint().initObject(false);
            
            // Docksection
            Docksection::cls().imprint().setup("Docksection", OBJECT);
            Docksection::cls().imprint().initObject(false);
            
            // Dockspace
            Dockspace::cls().imprint().setup("Dockspace", OBJECT);
            Dockspace::cls().imprint().initObject(false);
            
            // CloseButton
            CloseButton::cls().imprint().setup("CloseButton", OBJECT);
            CloseButton::cls().imprint().initObject(false);
            
            // WindowHeader
            WindowHeader::cls().imprint().setup("WindowHeader", OBJECT);
            WindowHeader::cls().imprint().initObject(false);
            
            // WindowSizer
            WindowSizer::cls().imprint().setup("WindowSizer", OBJECT);
            WindowSizer::cls().imprint().initObject(false);
            
            // WindowSizerLeft
            WindowSizerLeft::cls().imprint().setup("WindowSizerLeft", OBJECT);
            WindowSizerLeft::cls().imprint().initObject(false);
            
            // WindowSizerRight
            WindowSizerRight::cls().imprint().setup("WindowSizerRight", OBJECT);
            WindowSizerRight::cls().imprint().initObject(false);
            
            // WindowFooter
            WindowFooter::cls().imprint().setup("WindowFooter", OBJECT);
            WindowFooter::cls().imprint().initObject(false);
            
            // WindowBody
            WindowBody::cls().imprint().setup("WindowBody", OBJECT);
            WindowBody::cls().imprint().initObject(false);
            
            // Window
            Window::cls().imprint().setup("Window", OBJECT);
            Window::cls().imprint().initObject(false);
            
            // DockWindow
            DockWindow::cls().imprint().setup("DockWindow", OBJECT);
            DockWindow::cls().imprint().initObject(false);
            
            // WrapWindow
            WrapWindow::cls().imprint().setup("WrapWindow", OBJECT);
            WrapWindow::cls().imprint().initObject(false);
            
            
            m_rootTypes.push_back(&Image::cls());
            m_rootTypes.push_back(&Checkbox::cls());
            m_rootTypes.push_back(&Scrollbar::cls());
            m_rootTypes.push_back(&StatSlider<float>::cls());
            m_rootTypes.push_back(&StatSlider<int>::cls());
            m_rootTypes.push_back(&Dir::cls());
            m_rootTypes.push_back(&File::cls());
            m_rootTypes.push_back(&Directory::cls());
            m_rootTypes.push_back(&FileBrowser::cls());
            m_rootTypes.push_back(&FileNode::cls());
            m_rootTypes.push_back(&DirectoryNode::cls());
            m_rootTypes.push_back(&Tab::cls());
            m_rootTypes.push_back(&TabberHead::cls());
            m_rootTypes.push_back(&TabberBody::cls());
            m_rootTypes.push_back(&Tabber::cls());
            m_rootTypes.push_back(&TableHead::cls());
            m_rootTypes.push_back(&ColumnHeader::cls());
            m_rootTypes.push_back(&Table::cls());
            m_rootTypes.push_back(&TreeNode::cls());
            m_rootTypes.push_back(&Tree::cls());
            m_rootTypes.push_back(&Input<toy::Colour>::cls());
            m_rootTypes.push_back(&Textbox::cls());
            m_rootTypes.push_back(&TypeIn::cls());
            m_rootTypes.push_back(&Input<unsigned int>::cls());
            m_rootTypes.push_back(&Input<int>::cls());
            m_rootTypes.push_back(&Input<float>::cls());
            m_rootTypes.push_back(&Input<double>::cls());
            m_rootTypes.push_back(&Input<bool>::cls());
            m_rootTypes.push_back(&Input<string>::cls());
            m_rootTypes.push_back(&Frame::cls());
            m_rootTypes.push_back(&BoxFloat::cls());
            m_rootTypes.push_back(&ImageSkin::cls());
            m_rootTypes.push_back(&Shadow::cls());
            m_rootTypes.push_back(&LayoutStyle::cls());
            m_rootTypes.push_back(&InkStyle::cls());
            m_rootTypes.push_back(&Style::cls());
            m_rootTypes.push_back(&Tooltip::cls());
            m_rootTypes.push_back(&Cursor::cls());
            m_rootTypes.push_back(&Page::cls());
            m_rootTypes.push_back(&RootSheet::cls());
            m_rootTypes.push_back(&ScrollZone::cls());
            m_rootTypes.push_back(&ScrollSheet::cls());
            m_rootTypes.push_back(&ScrollContainer::cls());
            m_rootTypes.push_back(&ScrollPlan::cls());
            m_rootTypes.push_back(&Wedge::cls());
            m_rootTypes.push_back(&Container::cls());
            m_rootTypes.push_back(&WrapControl::cls());
            m_rootTypes.push_back(&Decal::cls());
            m_rootTypes.push_back(&Overlay::cls());
            m_rootTypes.push_back(&GridSheet::cls());
            m_rootTypes.push_back(&Widget::cls());
            m_rootTypes.push_back(&Placeholder::cls());
            m_rootTypes.push_back(&Docksection::cls());
            m_rootTypes.push_back(&Dockspace::cls());
            m_rootTypes.push_back(&CloseButton::cls());
            m_rootTypes.push_back(&WindowHeader::cls());
            m_rootTypes.push_back(&WindowSizer::cls());
            m_rootTypes.push_back(&WindowSizerLeft::cls());
            m_rootTypes.push_back(&WindowSizerRight::cls());
            m_rootTypes.push_back(&WindowFooter::cls());
            m_rootTypes.push_back(&WindowBody::cls());
            m_rootTypes.push_back(&Window::cls());
            m_rootTypes.push_back(&DockWindow::cls());
            m_rootTypes.push_back(&WrapWindow::cls());
        
        }

		static toyui instance;
        
    public:
        static toyui& module() { return instance; }
	};
    
	toyui toyui::instance;
#endif // IMPRINT_DEF_FILE
}

#endif // TOYUI_IMPRINTS_H
