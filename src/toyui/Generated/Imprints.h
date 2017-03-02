//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


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
    Object& DimFloat_create(DimFloat* at, LrefVector& args) {  new(at) DimFloat( args[0]->any<float>()->copy(), args[1]->any<float>()->copy() ); return *at; }
    Object& DimFloat_proto_poolinject(AbstractPool& pool, LrefVector& args) { return DimFloat_create(pool.as<Pool<DimFloat>>().alloc(), args); }
    Object& DimFloat_proto_lrefinject(Lref& lref, LrefVector& args) { return DimFloat_create(&lref->as<DimFloat>(), args); }
    AbstractPool* DimFloat_makePool() { return new Pool<DimFloat>(); }

    Object& BoxFloat_create(BoxFloat* at, LrefVector& args) {  new(at) BoxFloat( args[0]->any<float>()->copy(), args[1]->any<float>()->copy(), args[2]->any<float>()->copy(), args[3]->any<float>()->copy() ); return *at; }
    Object& BoxFloat_proto_poolinject(AbstractPool& pool, LrefVector& args) { return BoxFloat_create(pool.as<Pool<BoxFloat>>().alloc(), args); }
    Object& BoxFloat_proto_lrefinject(Lref& lref, LrefVector& args) { return BoxFloat_create(&lref->as<BoxFloat>(), args); }
    AbstractPool* BoxFloat_makePool() { return new Pool<BoxFloat>(); }

    Object& DimSizing_create(DimSizing* at, LrefVector& args) {  new(at) DimSizing( args[0]->any<Sizing>()->copy(), args[1]->any<Sizing>()->copy() ); return *at; }
    Object& DimSizing_proto_poolinject(AbstractPool& pool, LrefVector& args) { return DimSizing_create(pool.as<Pool<DimSizing>>().alloc(), args); }
    Object& DimSizing_proto_lrefinject(Lref& lref, LrefVector& args) { return DimSizing_create(&lref->as<DimSizing>(), args); }
    AbstractPool* DimSizing_makePool() { return new Pool<DimSizing>(); }

    Object& DimAlign_create(DimAlign* at, LrefVector& args) {  new(at) DimAlign( args[0]->any<Align>()->copy(), args[1]->any<Align>()->copy() ); return *at; }
    Object& DimAlign_proto_poolinject(AbstractPool& pool, LrefVector& args) { return DimAlign_create(pool.as<Pool<DimAlign>>().alloc(), args); }
    Object& DimAlign_proto_lrefinject(Lref& lref, LrefVector& args) { return DimAlign_create(&lref->as<DimAlign>(), args); }
    AbstractPool* DimAlign_makePool() { return new Pool<DimAlign>(); }

    Object& DimPivot_create(DimPivot* at, LrefVector& args) {  new(at) DimPivot( args[0]->any<Pivot>()->copy(), args[1]->any<Pivot>()->copy() ); return *at; }
    Object& DimPivot_proto_poolinject(AbstractPool& pool, LrefVector& args) { return DimPivot_create(pool.as<Pool<DimPivot>>().alloc(), args); }
    Object& DimPivot_proto_lrefinject(Lref& lref, LrefVector& args) { return DimPivot_create(&lref->as<DimPivot>(), args); }
    AbstractPool* DimPivot_makePool() { return new Pool<DimPivot>(); }

    Object& InkStyle_create(InkStyle* at, LrefVector& args) {  new(at) InkStyle( args[0]->any<string>()->copy() ); return *at; }
    Object& InkStyle_proto_poolinject(AbstractPool& pool, LrefVector& args) { return InkStyle_create(pool.as<Pool<InkStyle>>().alloc(), args); }
    Object& InkStyle_proto_lrefinject(Lref& lref, LrefVector& args) { return InkStyle_create(&lref->as<InkStyle>(), args); }
    AbstractPool* InkStyle_makePool() { return new Pool<InkStyle>(); }

    
































	void DimFloat_x(Object& object, Lref& ref) { ref->set<float>(object.as<DimFloat>().x()); }
	void DimFloat_setX(Object& object, const Lref& ref) { object.as<DimFloat>().setX(ref->any<float>()->copy()); }
	void DimFloat_y(Object& object, Lref& ref) { ref->set<float>(object.as<DimFloat>().y()); }
	void DimFloat_setY(Object& object, const Lref& ref) { object.as<DimFloat>().setY(ref->any<float>()->copy()); }

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

	void DimSizing_x(Object& object, Lref& ref) { ref->set<Sizing>(object.as<DimSizing>().x()); }
	void DimSizing_setX(Object& object, const Lref& ref) { object.as<DimSizing>().setX(ref->any<Sizing>()->copy()); }
	void DimSizing_y(Object& object, Lref& ref) { ref->set<Sizing>(object.as<DimSizing>().y()); }
	void DimSizing_setY(Object& object, const Lref& ref) { object.as<DimSizing>().setY(ref->any<Sizing>()->copy()); }

	void DimAlign_x(Object& object, Lref& ref) { ref->set<Align>(object.as<DimAlign>().x()); }
	void DimAlign_setX(Object& object, const Lref& ref) { object.as<DimAlign>().setX(ref->any<Align>()->copy()); }
	void DimAlign_y(Object& object, Lref& ref) { ref->set<Align>(object.as<DimAlign>().y()); }
	void DimAlign_setY(Object& object, const Lref& ref) { object.as<DimAlign>().setY(ref->any<Align>()->copy()); }

	void DimPivot_x(Object& object, Lref& ref) { ref->set<Pivot>(object.as<DimPivot>().x()); }
	void DimPivot_setX(Object& object, const Lref& ref) { object.as<DimPivot>().setX(ref->any<Pivot>()->copy()); }
	void DimPivot_y(Object& object, Lref& ref) { ref->set<Pivot>(object.as<DimPivot>().y()); }
	void DimPivot_setY(Object& object, const Lref& ref) { object.as<DimPivot>().setY(ref->any<Pivot>()->copy()); }

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


	void LayoutStyle_flow(Object& object, Lref& ref) { ref->set<Flow>(object.as<LayoutStyle>().flow()); }
	void LayoutStyle_clipping(Object& object, Lref& ref) { ref->set<Clipping>(object.as<LayoutStyle>().clipping()); }
	void LayoutStyle_opacity(Object& object, Lref& ref) { ref->set<Opacity>(object.as<LayoutStyle>().opacity()); }
	void LayoutStyle_div(Object& object, Lref& ref) { ref->set<Space>(object.as<LayoutStyle>().div()); }
	void LayoutStyle_layoutDim(Object& object, Lref& ref) { ref->set<Dimension>(object.as<LayoutStyle>().layoutDim()); }
	void LayoutStyle_align(Object& object, Lref& ref) { ref->set<DimAlign>(object.as<LayoutStyle>().align()); }
    Object* LayoutStyle_align_object(Object& object) { return &object.as<LayoutStyle>().align(); }
	void LayoutStyle_span(Object& object, Lref& ref) { ref->set<DimFloat>(object.as<LayoutStyle>().span()); }
    Object* LayoutStyle_span_object(Object& object) { return &object.as<LayoutStyle>().span(); }
	void LayoutStyle_size(Object& object, Lref& ref) { ref->set<DimFloat>(object.as<LayoutStyle>().size()); }
    Object* LayoutStyle_size_object(Object& object) { return &object.as<LayoutStyle>().size(); }
	void LayoutStyle_padding(Object& object, Lref& ref) { ref->set<BoxFloat>(object.as<LayoutStyle>().padding()); }
    Object* LayoutStyle_padding_object(Object& object) { return &object.as<LayoutStyle>().padding(); }
	void LayoutStyle_margin(Object& object, Lref& ref) { ref->set<DimFloat>(object.as<LayoutStyle>().margin()); }
    Object* LayoutStyle_margin_object(Object& object) { return &object.as<LayoutStyle>().margin(); }
	void LayoutStyle_spacing(Object& object, Lref& ref) { ref->set<DimFloat>(object.as<LayoutStyle>().spacing()); }
    Object* LayoutStyle_spacing_object(Object& object) { return &object.as<LayoutStyle>().spacing(); }
	void LayoutStyle_sizing(Object& object, Lref& ref) { ref->set<DimSizing>(object.as<LayoutStyle>().sizing()); }
    Object* LayoutStyle_sizing_object(Object& object) { return &object.as<LayoutStyle>().sizing(); }
	void LayoutStyle_pivot(Object& object, Lref& ref) { ref->set<DimPivot>(object.as<LayoutStyle>().pivot()); }
    Object* LayoutStyle_pivot_object(Object& object) { return &object.as<LayoutStyle>().pivot(); }
	void LayoutStyle_weight(Object& object, Lref& ref) { ref->set<Weight>(object.as<LayoutStyle>().weight()); }
	void LayoutStyle_weights(Object& object, Lref& ref) { ref->set<std::vector<float>>(object.as<LayoutStyle>().weights()); }
	void LayoutStyle_d_updated(Object& object, Lref& ref) { ref->set<size_t>(object.as<LayoutStyle>().d_updated); }
	void LayoutStyle_setD_updated(Object& object, const Lref& ref) { object.as<LayoutStyle>().d_updated = ref->any<size_t>()->copy(); }

	void InkStyle_name(Object& object, Lref& ref) { ref->set<string>(object.as<InkStyle>().name()); }
	void InkStyle_empty(Object& object, Lref& ref) { ref->set<bool>(object.as<InkStyle>().empty()); }
	void InkStyle_backgroundColour(Object& object, Lref& ref) { ref->set<Colour>(object.as<InkStyle>().backgroundColour()); }
    Object* InkStyle_backgroundColour_object(Object& object) { return &object.as<InkStyle>().backgroundColour(); }
	void InkStyle_borderColour(Object& object, Lref& ref) { ref->set<Colour>(object.as<InkStyle>().borderColour()); }
    Object* InkStyle_borderColour_object(Object& object) { return &object.as<InkStyle>().borderColour(); }
	void InkStyle_imageColour(Object& object, Lref& ref) { ref->set<Colour>(object.as<InkStyle>().imageColour()); }
    Object* InkStyle_imageColour_object(Object& object) { return &object.as<InkStyle>().imageColour(); }
	void InkStyle_textColour(Object& object, Lref& ref) { ref->set<Colour>(object.as<InkStyle>().textColour()); }
    Object* InkStyle_textColour_object(Object& object) { return &object.as<InkStyle>().textColour(); }
	void InkStyle_textFont(Object& object, Lref& ref) { ref->set<string>(object.as<InkStyle>().textFont()); }
	void InkStyle_textSize(Object& object, Lref& ref) { ref->set<float>(object.as<InkStyle>().textSize()); }
	void InkStyle_textBreak(Object& object, Lref& ref) { ref->set<bool>(object.as<InkStyle>().textBreak()); }
	void InkStyle_textWrap(Object& object, Lref& ref) { ref->set<bool>(object.as<InkStyle>().textWrap()); }
	void InkStyle_borderWidth(Object& object, Lref& ref) { ref->set<BoxFloat>(object.as<InkStyle>().borderWidth()); }
    Object* InkStyle_borderWidth_object(Object& object) { return &object.as<InkStyle>().borderWidth(); }
	void InkStyle_cornerRadius(Object& object, Lref& ref) { ref->set<BoxFloat>(object.as<InkStyle>().cornerRadius()); }
    Object* InkStyle_cornerRadius_object(Object& object) { return &object.as<InkStyle>().cornerRadius(); }
	void InkStyle_weakCorners(Object& object, Lref& ref) { ref->set<bool>(object.as<InkStyle>().weakCorners()); }
	void InkStyle_padding(Object& object, Lref& ref) { ref->set<BoxFloat>(object.as<InkStyle>().padding()); }
    Object* InkStyle_padding_object(Object& object) { return &object.as<InkStyle>().padding(); }
	void InkStyle_margin(Object& object, Lref& ref) { ref->set<BoxFloat>(object.as<InkStyle>().margin()); }
    Object* InkStyle_margin_object(Object& object) { return &object.as<InkStyle>().margin(); }
	void InkStyle_align(Object& object, Lref& ref) { ref->set<DimAlign>(object.as<InkStyle>().align()); }
    Object* InkStyle_align_object(Object& object) { return &object.as<InkStyle>().align(); }
	void InkStyle_linearGradient(Object& object, Lref& ref) { ref->set<DimFloat>(object.as<InkStyle>().linearGradient()); }
    Object* InkStyle_linearGradient_object(Object& object) { return &object.as<InkStyle>().linearGradient(); }
	void InkStyle_linearGradientDim(Object& object, Lref& ref) { ref->set<Dimension>(object.as<InkStyle>().linearGradientDim()); }
	void InkStyle_image(Object& object, Lref& ref) { ref->setobject(*object.as<InkStyle>().image()); }
    Object* InkStyle_image_object(Object& object) { return object.as<InkStyle>().image(); }
	void InkStyle_overlay(Object& object, Lref& ref) { ref->setobject(*object.as<InkStyle>().overlay()); }
    Object* InkStyle_overlay_object(Object& object) { return object.as<InkStyle>().overlay(); }
	void InkStyle_tile(Object& object, Lref& ref) { ref->setobject(*object.as<InkStyle>().tile()); }
    Object* InkStyle_tile_object(Object& object) { return object.as<InkStyle>().tile(); }
	void InkStyle_imageSkin(Object& object, Lref& ref) { ref->set<ImageSkin>(object.as<InkStyle>().imageSkin()); }
    Object* InkStyle_imageSkin_object(Object& object) { return &object.as<InkStyle>().imageSkin(); }
	void InkStyle_shadow(Object& object, Lref& ref) { ref->setobject(object.as<InkStyle>().shadow()); }
    Object* InkStyle_shadow_object(Object& object) { return &object.as<InkStyle>().shadow(); }

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
            
            typecls<Pivot>().imprint().setup("Pivot", ENUM);
            typecls<Pivot>().imprint().initEnum(StringVector({ "FORWARD", "REVERSE" }));
            typecls<Pivot>().imprint().initRefMethods<Pivot>();
            
            typecls<Align>().imprint().setup("Align", ENUM);
            typecls<Align>().imprint().initEnum(StringVector({ "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" }));
            typecls<Align>().imprint().initRefMethods<Align>();
            
            typecls<FrameType>().imprint().setup("FrameType", ENUM);
            typecls<FrameType>().imprint().initEnum(StringVector({ "FRAME", "STRIPE", "LAYER", "MASTER_LAYER", "SPACE_LAYER" }));
            typecls<FrameType>().imprint().initRefMethods<FrameType>();
            
            typecls<Flow>().imprint().setup("Flow", ENUM);
            typecls<Flow>().imprint().initEnum(StringVector({ "FLOW", "FREE", "FREE_FILL", "ALIGN", "OVERLAY", "FLOAT_DEPTH", "FLOAT_LENGTH" }));
            typecls<Flow>().imprint().initRefMethods<Flow>();
            
            typecls<Space>().imprint().setup("Space", ENUM);
            typecls<Space>().imprint().initEnum(StringVector({ "AUTO", "BLOCK", "DIV", "SPACE", "BOARD" }));
            typecls<Space>().imprint().initRefMethods<Space>();
            
            typecls<Sizing>().imprint().setup("Sizing", ENUM);
            typecls<Sizing>().imprint().initEnum(StringVector({ "FIXED", "SHRINK", "WRAP", "EXPAND", "MANUAL" }));
            typecls<Sizing>().imprint().initRefMethods<Sizing>();
            
            typecls<Clipping>().imprint().setup("Clipping", ENUM);
            typecls<Clipping>().imprint().initEnum(StringVector({ "NOCLIP", "CLIP" }));
            typecls<Clipping>().imprint().initRefMethods<Clipping>();
            
            typecls<Opacity>().imprint().setup("Opacity", ENUM);
            typecls<Opacity>().imprint().initEnum(StringVector({ "OPAQUE", "CLEAR", "HOLLOW" }));
            typecls<Opacity>().imprint().initRefMethods<Opacity>();
            
            typecls<Weight>().imprint().setup("Weight", ENUM);
            typecls<Weight>().imprint().initEnum(StringVector({ "NOWEIGHT", "LIST", "TABLE" }));
            typecls<Weight>().imprint().initRefMethods<Weight>();
            
            typecls<WidgetState>().imprint().setup("WidgetState", ENUM);
            typecls<WidgetState>().imprint().initEnum(StringVector({ "UNBOUND", "BOUND", "HOVERED", "TRIGGERED", "ACTIVATED", "FOCUSED", "DISABLED", "PRESSED", "DRAGGED", "CONTROL", "MODAL" }));
            typecls<WidgetState>().imprint().initRefMethods<WidgetState>();
            
        
            // Sequences
            typecls<std::vector<float>>().imprint().setup("std::vector<float>", SEQUENCE);
            typecls<std::vector<float>>().imprint().initRefMethods<std::vector<float>>();
            typecls<std::vector<float>>().imprint().initStore(typecls<float>());
            
        
            // Stores
        
        
            // Image
            Image::cls().imprint().setup("Image", OBJECT);
            Image::cls().imprint().initObject(false);
            
            // Device
            Device::cls().imprint().setup("Device", OBJECT);
            Device::cls().imprint().initObject(false);
            
            // Hook
            Hook::cls().imprint().setup("Hook", OBJECT);
            Hook::cls().imprint().initObject(false);
            
            // Frame
            Frame::cls().imprint().setup("Frame", OBJECT);
            Frame::cls().imprint().initObject(false);
            
            // Docksection
            Docksection::cls().imprint().setup("Docksection", OBJECT);
            Docksection::cls().imprint().initObject(false);
            
            // Dockline
            Dockline::cls().imprint().setup("Dockline", OBJECT);
            Dockline::cls().imprint().initObject(false);
            
            // DocklineX
            DocklineX::cls().imprint().setup("DocklineX", OBJECT);
            DocklineX::cls().imprint().initObject(false);
            
            // DocklineY
            DocklineY::cls().imprint().setup("DocklineY", OBJECT);
            DocklineY::cls().imprint().initObject(false);
            
            // MasterDockline
            MasterDockline::cls().imprint().setup("MasterDockline", OBJECT);
            MasterDockline::cls().imprint().initObject(false);
            
            // Dockspace
            Dockspace::cls().imprint().setup("Dockspace", OBJECT);
            Dockspace::cls().imprint().initObject(false);
            
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
            
            // TreeNodeHeader
            TreeNodeHeader::cls().imprint().setup("TreeNodeHeader", OBJECT);
            TreeNodeHeader::cls().imprint().initObject(false);
            
            // TreeNodeBody
            TreeNodeBody::cls().imprint().setup("TreeNodeBody", OBJECT);
            TreeNodeBody::cls().imprint().initObject(false);
            
            // TreeNodeToggle
            TreeNodeToggle::cls().imprint().setup("TreeNodeToggle", OBJECT);
            TreeNodeToggle::cls().imprint().initObject(false);
            
            // TreeNode
            TreeNode::cls().imprint().setup("TreeNode", OBJECT);
            TreeNode::cls().imprint().initObject(false);
            
            // Tree
            Tree::cls().imprint().setup("Tree", OBJECT);
            Tree::cls().imprint().initObject(false);
            
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
            
            // CloseButton
            CloseButton::cls().imprint().setup("CloseButton", OBJECT);
            CloseButton::cls().imprint().initObject(false);
            
            // Window
            Window::cls().imprint().setup("Window", OBJECT);
            Window::cls().imprint().initObject(false);
            
            // DockWindow
            DockWindow::cls().imprint().setup("DockWindow", OBJECT);
            DockWindow::cls().imprint().initObject(false);
            
            // WrapWindow
            WrapWindow::cls().imprint().setup("WrapWindow", OBJECT);
            WrapWindow::cls().imprint().initObject(false);
            
            // DimFloat
            DimFloat::cls().imprint().setup("DimFloat", STRUCT);
            DimFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 0, "x", &DimFloat_x, &DimFloat_setX, false, true));
            DimFloat::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 1, "y", &DimFloat_y, &DimFloat_setY, false, true));
            DimFloat::cls().imprint().initRefMethods<DimFloat>();
            DimFloat::cls().imprint().setConstructor(make_unique<Method>(DimFloat::cls(), "DimFloat", nullptr, ParamVector({ Param("x", lref(float()), INPUT_PARAM), Param("y", lref(float()), INPUT_PARAM) })));
            DimFloat::cls().imprint().initInjectors(&DimFloat_proto_poolinject, &DimFloat_proto_lrefinject, &DimFloat_makePool);
            DimFloat::cls().imprint().initObject(false);
            
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
            
            // DimSizing
            DimSizing::cls().imprint().setup("DimSizing", STRUCT);
            DimSizing::cls().imprint().addMember(make_unique<Member>(typecls<Sizing>(), 0, "x", &DimSizing_x, &DimSizing_setX, false, true));
            DimSizing::cls().imprint().addMember(make_unique<Member>(typecls<Sizing>(), 1, "y", &DimSizing_y, &DimSizing_setY, false, true));
            DimSizing::cls().imprint().initRefMethods<DimSizing>();
            DimSizing::cls().imprint().setConstructor(make_unique<Method>(DimSizing::cls(), "DimSizing", nullptr, ParamVector({ Param("x", lref(Sizing()), INPUT_PARAM), Param("y", lref(Sizing()), INPUT_PARAM) })));
            DimSizing::cls().imprint().initInjectors(&DimSizing_proto_poolinject, &DimSizing_proto_lrefinject, &DimSizing_makePool);
            DimSizing::cls().imprint().initObject(false);
            
            // DimAlign
            DimAlign::cls().imprint().setup("DimAlign", STRUCT);
            DimAlign::cls().imprint().addMember(make_unique<Member>(typecls<Align>(), 0, "x", &DimAlign_x, &DimAlign_setX, false, true));
            DimAlign::cls().imprint().addMember(make_unique<Member>(typecls<Align>(), 1, "y", &DimAlign_y, &DimAlign_setY, false, true));
            DimAlign::cls().imprint().initRefMethods<DimAlign>();
            DimAlign::cls().imprint().setConstructor(make_unique<Method>(DimAlign::cls(), "DimAlign", nullptr, ParamVector({ Param("x", lref(Align()), INPUT_PARAM), Param("y", lref(Align()), INPUT_PARAM) })));
            DimAlign::cls().imprint().initInjectors(&DimAlign_proto_poolinject, &DimAlign_proto_lrefinject, &DimAlign_makePool);
            DimAlign::cls().imprint().initObject(false);
            
            // DimPivot
            DimPivot::cls().imprint().setup("DimPivot", STRUCT);
            DimPivot::cls().imprint().addMember(make_unique<Member>(typecls<Pivot>(), 0, "x", &DimPivot_x, &DimPivot_setX, false, true));
            DimPivot::cls().imprint().addMember(make_unique<Member>(typecls<Pivot>(), 1, "y", &DimPivot_y, &DimPivot_setY, false, true));
            DimPivot::cls().imprint().initRefMethods<DimPivot>();
            DimPivot::cls().imprint().setConstructor(make_unique<Method>(DimPivot::cls(), "DimPivot", nullptr, ParamVector({ Param("x", lref(Pivot()), INPUT_PARAM), Param("y", lref(Pivot()), INPUT_PARAM) })));
            DimPivot::cls().imprint().initInjectors(&DimPivot_proto_poolinject, &DimPivot_proto_lrefinject, &DimPivot_makePool);
            DimPivot::cls().imprint().initObject(false);
            
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
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Flow>(), 0, "flow", &LayoutStyle_flow, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Clipping>(), 1, "clipping", &LayoutStyle_clipping, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Opacity>(), 2, "opacity", &LayoutStyle_opacity, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Space>(), 3, "div", &LayoutStyle_div, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Dimension>(), 4, "layoutDim", &LayoutStyle_layoutDim, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimAlign::cls(), 5, "align", &LayoutStyle_align, nullptr, true, false, &LayoutStyle_align_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimFloat::cls(), 6, "span", &LayoutStyle_span, nullptr, true, false, &LayoutStyle_span_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimFloat::cls(), 7, "size", &LayoutStyle_size, nullptr, true, false, &LayoutStyle_size_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), 8, "padding", &LayoutStyle_padding, nullptr, true, false, &LayoutStyle_padding_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimFloat::cls(), 9, "margin", &LayoutStyle_margin, nullptr, true, false, &LayoutStyle_margin_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimFloat::cls(), 10, "spacing", &LayoutStyle_spacing, nullptr, true, false, &LayoutStyle_spacing_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimSizing::cls(), 11, "sizing", &LayoutStyle_sizing, nullptr, true, false, &LayoutStyle_sizing_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(DimPivot::cls(), 12, "pivot", &LayoutStyle_pivot, nullptr, true, false, &LayoutStyle_pivot_object));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<Weight>(), 13, "weight", &LayoutStyle_weight, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<std::vector<float>>(), 14, "weights", &LayoutStyle_weights, nullptr, false, false));
            LayoutStyle::cls().imprint().addMember(make_unique<Member>(typecls<size_t>(), 15, "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, false, true));
            LayoutStyle::cls().imprint().initObject(false);
            
            // InkStyle
            InkStyle::cls().imprint().setup("InkStyle", OBJECT);
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<string>(), 0, "name", &InkStyle_name, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<bool>(), 1, "empty", &InkStyle_empty, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Colour::cls(), 2, "backgroundColour", &InkStyle_backgroundColour, nullptr, true, false, &InkStyle_backgroundColour_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Colour::cls(), 3, "borderColour", &InkStyle_borderColour, nullptr, true, false, &InkStyle_borderColour_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Colour::cls(), 4, "imageColour", &InkStyle_imageColour, nullptr, true, false, &InkStyle_imageColour_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Colour::cls(), 5, "textColour", &InkStyle_textColour, nullptr, true, false, &InkStyle_textColour_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<string>(), 6, "textFont", &InkStyle_textFont, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<float>(), 7, "textSize", &InkStyle_textSize, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<bool>(), 8, "textBreak", &InkStyle_textBreak, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<bool>(), 9, "textWrap", &InkStyle_textWrap, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), 10, "borderWidth", &InkStyle_borderWidth, nullptr, true, false, &InkStyle_borderWidth_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), 11, "cornerRadius", &InkStyle_cornerRadius, nullptr, true, false, &InkStyle_cornerRadius_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<bool>(), 12, "weakCorners", &InkStyle_weakCorners, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), 13, "padding", &InkStyle_padding, nullptr, true, false, &InkStyle_padding_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(BoxFloat::cls(), 14, "margin", &InkStyle_margin, nullptr, true, false, &InkStyle_margin_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(DimAlign::cls(), 15, "align", &InkStyle_align, nullptr, true, false, &InkStyle_align_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(DimFloat::cls(), 16, "linearGradient", &InkStyle_linearGradient, nullptr, true, false, &InkStyle_linearGradient_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(typecls<Dimension>(), 17, "linearGradientDim", &InkStyle_linearGradientDim, nullptr, false, false));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Image::cls(), 18, "image", &InkStyle_image, nullptr, false, false, &InkStyle_image_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Image::cls(), 19, "overlay", &InkStyle_overlay, nullptr, false, false, &InkStyle_overlay_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Image::cls(), 20, "tile", &InkStyle_tile, nullptr, false, false, &InkStyle_tile_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(ImageSkin::cls(), 21, "imageSkin", &InkStyle_imageSkin, nullptr, true, false, &InkStyle_imageSkin_object));
            InkStyle::cls().imprint().addMember(make_unique<Member>(Shadow::cls(), 22, "shadow", &InkStyle_shadow, nullptr, true, false, &InkStyle_shadow_object));
            InkStyle::cls().imprint().setConstructor(make_unique<Method>(InkStyle::cls(), "InkStyle", nullptr, ParamVector({ Param("name", lref(string()), INPUT_PARAM) })));
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
            
            // Checkbox
            Checkbox::cls().imprint().setup("Checkbox", OBJECT);
            Checkbox::cls().imprint().initObject(false);
            
            // Cursor
            Cursor::cls().imprint().setup("Cursor", OBJECT);
            Cursor::cls().imprint().initObject(false);
            
            // Tooltip
            Tooltip::cls().imprint().setup("Tooltip", OBJECT);
            Tooltip::cls().imprint().initObject(false);
            
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
            
            // Inputtoy::Colour
            Input<toy::Colour>::cls().imprint().setup("Input<toy::Colour>", OBJECT);
            Input<toy::Colour>::cls().imprint().initObject(false);
            
            // RootSheet
            RootSheet::cls().imprint().setup("RootSheet", OBJECT);
            RootSheet::cls().imprint().initObject(false);
            
            // Scrollbar
            Scrollbar::cls().imprint().setup("Scrollbar", OBJECT);
            Scrollbar::cls().imprint().initObject(false);
            
            // Piece
            Piece::cls().imprint().setup("Piece", OBJECT);
            Piece::cls().imprint().initObject(false);
            
            // Overlay
            Overlay::cls().imprint().setup("Overlay", OBJECT);
            Overlay::cls().imprint().initObject(false);
            
            // Board
            Board::cls().imprint().setup("Board", OBJECT);
            Board::cls().imprint().initObject(false);
            
            // ScrollSheet
            ScrollSheet::cls().imprint().setup("ScrollSheet", OBJECT);
            ScrollSheet::cls().imprint().initObject(false);
            
            // GridSheet
            GridSheet::cls().imprint().setup("GridSheet", OBJECT);
            GridSheet::cls().imprint().initObject(false);

            // StatSliderfloat
            StatSlider<float>::cls().imprint().setup("StatSlider<float>", OBJECT);
            StatSlider<float>::cls().imprint().initObject(false);
            
            // StatSliderint
            StatSlider<int>::cls().imprint().setup("StatSlider<int>", OBJECT);
            StatSlider<int>::cls().imprint().initObject(false);
            
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
            
            // Widget
            Widget::cls().imprint().setup("Widget", OBJECT);
            Widget::cls().imprint().addMember(make_unique<Member>(Piece::cls(), 0, "parent", &Widget_parent, nullptr, false, false, &Widget_parent_object));
            Widget::cls().imprint().addMember(make_unique<Member>(Frame::cls(), 1, "frame", &Widget_frame, nullptr, true, false, &Widget_frame_object));
            Widget::cls().imprint().addMember(make_unique<Member>(typecls<WidgetState>(), 2, "state", &Widget_state, nullptr, false, false));
            Widget::cls().imprint().addMember(make_unique<Member>(Style::cls(), 3, "style", &Widget_style, &Widget_setStyle, true, true, &Widget_style_object));
            Widget::cls().imprint().initObject(false);
            
            // Page
            Page::cls().imprint().setup("Page", OBJECT);
            Page::cls().imprint().initObject(false);
            
            // Dialog
            Dialog::cls().imprint().setup("Dialog", OBJECT);
            Dialog::cls().imprint().initObject(false);
            
            // Header
            Header::cls().imprint().setup("Header", OBJECT);
            Header::cls().imprint().initObject(false);
            
            
            m_rootTypes.push_back(&Image::cls());
            m_rootTypes.push_back(&Device::cls());
            m_rootTypes.push_back(&Hook::cls());
            m_rootTypes.push_back(&Frame::cls());
            m_rootTypes.push_back(&Docksection::cls());
            m_rootTypes.push_back(&Dockline::cls());
            m_rootTypes.push_back(&DocklineX::cls());
            m_rootTypes.push_back(&DocklineY::cls());
            m_rootTypes.push_back(&MasterDockline::cls());
            m_rootTypes.push_back(&Dockspace::cls());
            m_rootTypes.push_back(&Tab::cls());
            m_rootTypes.push_back(&TabberHead::cls());
            m_rootTypes.push_back(&TabberBody::cls());
            m_rootTypes.push_back(&Tabber::cls());
            m_rootTypes.push_back(&TableHead::cls());
            m_rootTypes.push_back(&ColumnHeader::cls());
            m_rootTypes.push_back(&Table::cls());
            m_rootTypes.push_back(&TreeNodeHeader::cls());
            m_rootTypes.push_back(&TreeNodeBody::cls());
            m_rootTypes.push_back(&TreeNodeToggle::cls());
            m_rootTypes.push_back(&TreeNode::cls());
            m_rootTypes.push_back(&Tree::cls());
            m_rootTypes.push_back(&WindowHeader::cls());
            m_rootTypes.push_back(&WindowSizer::cls());
            m_rootTypes.push_back(&WindowSizerLeft::cls());
            m_rootTypes.push_back(&WindowSizerRight::cls());
            m_rootTypes.push_back(&WindowFooter::cls());
            m_rootTypes.push_back(&WindowBody::cls());
            m_rootTypes.push_back(&CloseButton::cls());
            m_rootTypes.push_back(&Window::cls());
            m_rootTypes.push_back(&DockWindow::cls());
            m_rootTypes.push_back(&WrapWindow::cls());
            m_rootTypes.push_back(&DimFloat::cls());
            m_rootTypes.push_back(&BoxFloat::cls());
            m_rootTypes.push_back(&DimSizing::cls());
            m_rootTypes.push_back(&DimAlign::cls());
            m_rootTypes.push_back(&DimPivot::cls());
            m_rootTypes.push_back(&ImageSkin::cls());
            m_rootTypes.push_back(&Shadow::cls());
            m_rootTypes.push_back(&LayoutStyle::cls());
            m_rootTypes.push_back(&InkStyle::cls());
            m_rootTypes.push_back(&Style::cls());
            m_rootTypes.push_back(&Checkbox::cls());
            m_rootTypes.push_back(&Cursor::cls());
            m_rootTypes.push_back(&Tooltip::cls());
            m_rootTypes.push_back(&Dir::cls());
            m_rootTypes.push_back(&File::cls());
            m_rootTypes.push_back(&Directory::cls());
            m_rootTypes.push_back(&FileBrowser::cls());
            m_rootTypes.push_back(&FileNode::cls());
            m_rootTypes.push_back(&DirectoryNode::cls());
            m_rootTypes.push_back(&Input<toy::Colour>::cls());
            m_rootTypes.push_back(&RootSheet::cls());
            m_rootTypes.push_back(&Scrollbar::cls());
            m_rootTypes.push_back(&Piece::cls());
            m_rootTypes.push_back(&Overlay::cls());
            m_rootTypes.push_back(&Board::cls());
            m_rootTypes.push_back(&ScrollSheet::cls());
            m_rootTypes.push_back(&GridSheet::cls());
            m_rootTypes.push_back(&StatSlider<float>::cls());
            m_rootTypes.push_back(&StatSlider<int>::cls());
            m_rootTypes.push_back(&Textbox::cls());
            m_rootTypes.push_back(&TypeIn::cls());
            m_rootTypes.push_back(&Input<unsigned int>::cls());
            m_rootTypes.push_back(&Input<int>::cls());
            m_rootTypes.push_back(&Input<float>::cls());
            m_rootTypes.push_back(&Input<double>::cls());
            m_rootTypes.push_back(&Input<bool>::cls());
            m_rootTypes.push_back(&Input<string>::cls());
            m_rootTypes.push_back(&Widget::cls());
            m_rootTypes.push_back(&Page::cls());
            m_rootTypes.push_back(&Dialog::cls());
            m_rootTypes.push_back(&Header::cls());
        
        }

		static toyui instance;
        
    public:
        static toyui& module() { return instance; }
	};
    
	toyui toyui::instance;
#endif // IMPRINT_DEF_FILE
}

#endif // TOYUI_IMPRINTS_H
