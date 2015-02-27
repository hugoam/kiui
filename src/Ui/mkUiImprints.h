#ifndef MKUIIMPRINTS_H_INCLUDED
#define MKUIIMPRINTS_H_INCLUDED

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiForward.h>
#include <Ui/mkUiTypes.h>

#include <Utils/mkUtils.h>
#include <Utils/Reflect/mkBaseImprint.h>
#include <Object/mkLibrary.h>
#include <Utils/Reflect/mkImprint.h>
#include <Utils/Reflect/mkInjector.h>
#include <Utils/Reflect/mkMethod.h>
#include <Utils/Memory/mkMemory.h>
#include <Utils/Memory/mkMultiPool.h>
#include <Utils/Memory/mkPoolMake.h>
#include <Object/Util/mkMake.h>

namespace mk
{
    
#ifdef IMPRINT_DEF_FILE
    Object* InkStyle_proto_inject(InkStyle* at, Maker* maker) { new(at) InkStyle( maker->args(0)[0]->mget<string>(), maker->args(0)[1]->mget<Colour>(), maker->args(0)[2]->mget<Colour>(), maker->args(0)[3]->mget<Colour>(), maker->args(0)[4]->mget<float>(), maker->args(0)[5]->mget<DimFloat>(), maker->args(0)[6]->mget<DimFloat>(), maker->args(0)[7]->mget<string>() ); return at; }
    Object* InkStyle_proto_poolinject(AbstractPool* pool, Maker* maker) { return InkStyle_proto_inject(pool->as<Pool<InkStyle>>()->alloc(), maker); }
    Object* InkStyle_proto_lrefinject(Lref& lref, Maker* maker) { return InkStyle_proto_inject(lref->as<InkStyle>(), maker); }
    AbstractPool* InkStyle_makePool() { return new Pool<InkStyle>(); }

    Object* DimFloat_proto_inject(DimFloat* at, Maker* maker) { new(at) DimFloat( maker->args(0)[0]->mget<float>(), maker->args(0)[1]->mget<float>() ); return at; }
    Object* DimFloat_proto_poolinject(AbstractPool* pool, Maker* maker) { return DimFloat_proto_inject(pool->as<Pool<DimFloat>>()->alloc(), maker); }
    Object* DimFloat_proto_lrefinject(Lref& lref, Maker* maker) { return DimFloat_proto_inject(lref->as<DimFloat>(), maker); }
    AbstractPool* DimFloat_makePool() { return new Pool<DimFloat>(); }

    Object* DimPivot_proto_inject(DimPivot* at, Maker* maker) { new(at) DimPivot( maker->args(0)[0]->mget<Pivot>(), maker->args(0)[1]->mget<Pivot>() ); return at; }
    Object* DimPivot_proto_poolinject(AbstractPool* pool, Maker* maker) { return DimPivot_proto_inject(pool->as<Pool<DimPivot>>()->alloc(), maker); }
    Object* DimPivot_proto_lrefinject(Lref& lref, Maker* maker) { return DimPivot_proto_inject(lref->as<DimPivot>(), maker); }
    AbstractPool* DimPivot_makePool() { return new Pool<DimPivot>(); }

    
	void InkStyle_mName(Object* object, Lref& ref) { ref->set<string>(object->as<InkStyle>()->mName); }
	void InkStyle_setMName(Object* object, const Lref& ref) { object->as<InkStyle>()->mName = ref->get<string>(); }
	void InkStyle_mEmpty(Object* object, Lref& ref) { ref->set<bool>(object->as<InkStyle>()->mEmpty); }
	void InkStyle_setMEmpty(Object* object, const Lref& ref) { object->as<InkStyle>()->mEmpty = ref->get<bool>(); }
	void InkStyle_mBackgroundColour(Object* object, Lref& ref) { ref->set<Colour>(object->as<InkStyle>()->mBackgroundColour); }
    Object* InkStyle_mBackgroundColour_object(Object* object) { return &object->as<InkStyle>()->mBackgroundColour; }
	void InkStyle_setMBackgroundColour(Object* object, const Lref& ref) { object->as<InkStyle>()->mBackgroundColour = ref->get<Colour>(); }
	void InkStyle_mBorderColour(Object* object, Lref& ref) { ref->set<Colour>(object->as<InkStyle>()->mBorderColour); }
    Object* InkStyle_mBorderColour_object(Object* object) { return &object->as<InkStyle>()->mBorderColour; }
	void InkStyle_setMBorderColour(Object* object, const Lref& ref) { object->as<InkStyle>()->mBorderColour = ref->get<Colour>(); }
	void InkStyle_mImageColour(Object* object, Lref& ref) { ref->set<Colour>(object->as<InkStyle>()->mImageColour); }
    Object* InkStyle_mImageColour_object(Object* object) { return &object->as<InkStyle>()->mImageColour; }
	void InkStyle_setMImageColour(Object* object, const Lref& ref) { object->as<InkStyle>()->mImageColour = ref->get<Colour>(); }
	void InkStyle_mTextColour(Object* object, Lref& ref) { ref->set<Colour>(object->as<InkStyle>()->mTextColour); }
    Object* InkStyle_mTextColour_object(Object* object) { return &object->as<InkStyle>()->mTextColour; }
	void InkStyle_setMTextColour(Object* object, const Lref& ref) { object->as<InkStyle>()->mTextColour = ref->get<Colour>(); }
	void InkStyle_mBorderWidth(Object* object, Lref& ref) { ref->set<float>(object->as<InkStyle>()->mBorderWidth); }
	void InkStyle_setMBorderWidth(Object* object, const Lref& ref) { object->as<InkStyle>()->mBorderWidth = ref->get<float>(); }
	void InkStyle_mCornerRadius(Object* object, Lref& ref) { ref->set<float>(object->as<InkStyle>()->mCornerRadius); }
	void InkStyle_setMCornerRadius(Object* object, const Lref& ref) { object->as<InkStyle>()->mCornerRadius = ref->get<float>(); }
	void InkStyle_mMargin(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<InkStyle>()->mMargin); }
    Object* InkStyle_mMargin_object(Object* object) { return &object->as<InkStyle>()->mMargin; }
	void InkStyle_setMMargin(Object* object, const Lref& ref) { object->as<InkStyle>()->mMargin = ref->get<DimFloat>(); }
	void InkStyle_mPadding(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<InkStyle>()->mPadding); }
    Object* InkStyle_mPadding_object(Object* object) { return &object->as<InkStyle>()->mPadding; }
	void InkStyle_setMPadding(Object* object, const Lref& ref) { object->as<InkStyle>()->mPadding = ref->get<DimFloat>(); }
	void InkStyle_mImage(Object* object, Lref& ref) { ref->set<string>(object->as<InkStyle>()->mImage); }
	void InkStyle_setMImage(Object* object, const Lref& ref) { object->as<InkStyle>()->mImage = ref->get<string>(); }

	void DimFloat_x(Object* object, Lref& ref) { ref->set<float>(object->as<DimFloat>()->x()); }
	void DimFloat_setX(Object* object, const Lref& ref) { object->as<DimFloat>()->setX(ref->get<float>()); }
	void DimFloat_y(Object* object, Lref& ref) { ref->set<float>(object->as<DimFloat>()->y()); }
	void DimFloat_setY(Object* object, const Lref& ref) { object->as<DimFloat>()->setY(ref->get<float>()); }

	void DimPivot_x(Object* object, Lref& ref) { ref->set<Pivot>(object->as<DimPivot>()->x()); }
	void DimPivot_setX(Object* object, const Lref& ref) { object->as<DimPivot>()->setX(ref->get<Pivot>()); }
	void DimPivot_y(Object* object, Lref& ref) { ref->set<Pivot>(object->as<DimPivot>()->y()); }
	void DimPivot_setY(Object* object, const Lref& ref) { object->as<DimPivot>()->setY(ref->get<Pivot>()); }

	void LayoutStyle_d_name(Object* object, Lref& ref) { ref->set<string>(object->as<LayoutStyle>()->d_name); }
	void LayoutStyle_setD_name(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_name = ref->get<string>(); }
	void LayoutStyle_d_flow(Object* object, Lref& ref) { ref->set<Flow>(object->as<LayoutStyle>()->d_flow); }
	void LayoutStyle_setD_flow(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_flow = ref->get<Flow>(); }
	void LayoutStyle_d_overflow(Object* object, Lref& ref) { ref->set<Overflow>(object->as<LayoutStyle>()->d_overflow); }
	void LayoutStyle_setD_overflow(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_overflow = ref->get<Overflow>(); }
	void LayoutStyle_d_layer(Object* object, Lref& ref) { ref->set<BoxLayer>(object->as<LayoutStyle>()->d_layer); }
	void LayoutStyle_setD_layer(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_layer = ref->get<BoxLayer>(); }
	void LayoutStyle_d_opacity(Object* object, Lref& ref) { ref->set<Opacity>(object->as<LayoutStyle>()->d_opacity); }
	void LayoutStyle_setD_opacity(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_opacity = ref->get<Opacity>(); }
	void LayoutStyle_d_div(Object* object, Lref& ref) { ref->set<bool>(object->as<LayoutStyle>()->d_div); }
	void LayoutStyle_setD_div(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_div = ref->get<bool>(); }
	void LayoutStyle_d_layoutDim(Object* object, Lref& ref) { ref->set<Dimension>(object->as<LayoutStyle>()->d_layoutDim); }
	void LayoutStyle_setD_layoutDim(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_layoutDim = ref->get<Dimension>(); }
	void LayoutStyle_d_span(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_span); }
    Object* LayoutStyle_d_span_object(Object* object) { return &object->as<LayoutStyle>()->d_span; }
	void LayoutStyle_setD_span(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_span = ref->get<DimFloat>(); }
	void LayoutStyle_d_size(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_size); }
    Object* LayoutStyle_d_size_object(Object* object) { return &object->as<LayoutStyle>()->d_size; }
	void LayoutStyle_setD_size(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_size = ref->get<DimFloat>(); }
	void LayoutStyle_d_frontpadding(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_frontpadding); }
    Object* LayoutStyle_d_frontpadding_object(Object* object) { return &object->as<LayoutStyle>()->d_frontpadding; }
	void LayoutStyle_setD_frontpadding(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_frontpadding = ref->get<DimFloat>(); }
	void LayoutStyle_d_backpadding(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_backpadding); }
    Object* LayoutStyle_d_backpadding_object(Object* object) { return &object->as<LayoutStyle>()->d_backpadding; }
	void LayoutStyle_setD_backpadding(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_backpadding = ref->get<DimFloat>(); }
	void LayoutStyle_d_margin(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_margin); }
    Object* LayoutStyle_d_margin_object(Object* object) { return &object->as<LayoutStyle>()->d_margin; }
	void LayoutStyle_setD_margin(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_margin = ref->get<DimFloat>(); }
	void LayoutStyle_d_spacing(Object* object, Lref& ref) { ref->set<DimFloat>(object->as<LayoutStyle>()->d_spacing); }
    Object* LayoutStyle_d_spacing_object(Object* object) { return &object->as<LayoutStyle>()->d_spacing; }
	void LayoutStyle_setD_spacing(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_spacing = ref->get<DimFloat>(); }
	void LayoutStyle_d_pivot(Object* object, Lref& ref) { ref->set<DimPivot>(object->as<LayoutStyle>()->d_pivot); }
    Object* LayoutStyle_d_pivot_object(Object* object) { return &object->as<LayoutStyle>()->d_pivot; }
	void LayoutStyle_setD_pivot(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_pivot = ref->get<DimPivot>(); }
	void LayoutStyle_d_weightTable(Object* object, Lref& ref) { ref->set<std::vector<float>>(object->as<LayoutStyle>()->d_weightTable); }
	void LayoutStyle_setD_weightTable(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_weightTable = ref->get<std::vector<float>>(); }
	void LayoutStyle_d_updated(Object* object, Lref& ref) { ref->set<int>(object->as<LayoutStyle>()->d_updated); }
	void LayoutStyle_setD_updated(Object* object, const Lref& ref) { object->as<LayoutStyle>()->d_updated = ref->get<int>(); }

	void Widget_parent(Object* object, Lref& ref) { ref->set<Sheet *>(object->as<Widget>()->parent()); }
	void Widget_clas(Object* object, Lref& ref) { ref->set<string>(object->as<Widget>()->clas()); }
	void Widget_frame(Object* object, Lref& ref) { ref->set<Frame *>(object->as<Widget>()->frame()); }
	void Widget_skin(Object* object, Lref& ref) { ref->set<InkStyle *>(object->as<Widget>()->skin()); }
    Object* Widget_skin_object(Object* object) { return object->as<Widget>()->skin(); }
	void Widget_layoutStyle(Object* object, Lref& ref) { ref->set<LayoutStyle *>(object->as<Widget>()->layoutStyle()); }
    Object* Widget_layoutStyle_object(Object* object) { return object->as<Widget>()->layoutStyle(); }
	void Widget_inkStyle(Object* object, Lref& ref) { ref->set<InkStyle *>(object->as<Widget>()->inkStyle()); }
    Object* Widget_inkStyle_object(Object* object) { return object->as<Widget>()->inkStyle(); }

    
	void imprintmkUi(std::vector<Type*>& types, std::vector<Type*>& prototypes)
	{
        // Base Types
    
        // Enums
        typeof<Pivot>()->setupImprint(make<Imprint>(typeof<Pivot>(), "Pivot", ENUM));
        typeof<Pivot>()->imprint()->initEnum(StringVector({ "FORWARD", "REVERSE" }));
        typeof<Pivot>()->imprint()->initRefMethods<Pivot>();
        
        typeof<Dimension>()->setupImprint(make<Imprint>(typeof<Dimension>(), "Dimension", ENUM));
        typeof<Dimension>()->imprint()->initEnum(StringVector({ "DIM_X", "DIM_Y" }));
        typeof<Dimension>()->imprint()->initRefMethods<Dimension>();
        
        typeof<FrameType>()->setupImprint(make<Imprint>(typeof<FrameType>(), "FrameType", ENUM));
        typeof<FrameType>()->imprint()->initEnum(StringVector({ "FRAME", "STRIPE" }));
        typeof<FrameType>()->imprint()->initRefMethods<FrameType>();
        
        typeof<Flow>()->setupImprint(make<Imprint>(typeof<Flow>(), "Flow", ENUM));
        typeof<Flow>()->imprint()->initEnum(StringVector({ "FLOW", "MANUAL" }));
        typeof<Flow>()->imprint()->initRefMethods<Flow>();
        
        typeof<Overflow>()->setupImprint(make<Imprint>(typeof<Overflow>(), "Overflow", ENUM));
        typeof<Overflow>()->imprint()->initEnum(StringVector({ "CLIP", "SCROLL" }));
        typeof<Overflow>()->imprint()->initRefMethods<Overflow>();
        
        typeof<BoxLayer>()->setupImprint(make<Imprint>(typeof<BoxLayer>(), "BoxLayer", ENUM));
        typeof<BoxLayer>()->imprint()->initEnum(StringVector({ "FLAT", "LAYER" }));
        typeof<BoxLayer>()->imprint()->initRefMethods<BoxLayer>();
        
        typeof<Opacity>()->setupImprint(make<Imprint>(typeof<Opacity>(), "Opacity", ENUM));
        typeof<Opacity>()->imprint()->initEnum(StringVector({ "_OPAQUE", "_VOID" }));
        typeof<Opacity>()->imprint()->initRefMethods<Opacity>();
        
    
        // Sequences
        typeof<std::vector<float>>()->setupImprint(make<Imprint>(typeof<std::vector<float>>(), "std::vector<float>", SEQUENCE));
        typeof<std::vector<float>>()->imprint()->initRefMethods<std::vector<float>>();
        typeof<std::vector<float>>()->imprint()->initStore(typeof<float>());
        
    
        // Stores
    
   
        // InkStyle
        InkStyle::cls()->setupImprint(make<Imprint>(InkStyle::cls(), "InkStyle", STRUCT));
        InkStyle::cls()->imprint()->addMember(make<Member>(Typed<string>::cls(), 0, "mName", &InkStyle_mName, &InkStyle_setMName, false, true));
        InkStyle::cls()->imprint()->addMember(make<Member>(Typed<bool>::cls(), 1, "mEmpty", &InkStyle_mEmpty, &InkStyle_setMEmpty, false, true));
        InkStyle::cls()->imprint()->addMember(make<Member>(Colour::cls(), 2, "mBackgroundColour", &InkStyle_mBackgroundColour, &InkStyle_setMBackgroundColour, true, true, &InkStyle_mBackgroundColour_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(Colour::cls(), 3, "mBorderColour", &InkStyle_mBorderColour, &InkStyle_setMBorderColour, true, true, &InkStyle_mBorderColour_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(Colour::cls(), 4, "mImageColour", &InkStyle_mImageColour, &InkStyle_setMImageColour, true, true, &InkStyle_mImageColour_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(Colour::cls(), 5, "mTextColour", &InkStyle_mTextColour, &InkStyle_setMTextColour, true, true, &InkStyle_mTextColour_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(Typed<float>::cls(), 6, "mBorderWidth", &InkStyle_mBorderWidth, &InkStyle_setMBorderWidth, false, true));
        InkStyle::cls()->imprint()->addMember(make<Member>(Typed<float>::cls(), 7, "mCornerRadius", &InkStyle_mCornerRadius, &InkStyle_setMCornerRadius, false, true));
        InkStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 8, "mMargin", &InkStyle_mMargin, &InkStyle_setMMargin, true, true, &InkStyle_mMargin_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 9, "mPadding", &InkStyle_mPadding, &InkStyle_setMPadding, true, true, &InkStyle_mPadding_object));
        InkStyle::cls()->imprint()->addMember(make<Member>(Typed<string>::cls(), 10, "mImage", &InkStyle_mImage, &InkStyle_setMImage, false, true));
        InkStyle::cls()->imprint()->initRefMethods<InkStyle>();
        InkStyle::cls()->imprint()->setConstructor(make<Method>(InkStyle::cls(), "InkStyle", nullptr, LrefVector({ lref(string()), Lref(nullptr, Colour::cls()), Lref(nullptr, Colour::cls()), Lref(nullptr, Colour::cls()), lref(float()), Lref(nullptr, DimFloat::cls()), Lref(nullptr, DimFloat::cls()), lref(string()) }), StringVector({ "name", "background", "text", "border", "borderWidth", "margin", "padding", "image" }), LrefVector({ lref(string()), Lref(nullptr, Colour::cls()), Lref(nullptr, Colour::cls()), Lref(nullptr, Colour::cls()), lref(float()), Lref(nullptr, DimFloat::cls()), Lref(nullptr, DimFloat::cls()), lref(string()) })));
        InkStyle::cls()->imprint()->initInjectors(&InkStyle_proto_poolinject, &InkStyle_proto_lrefinject, &InkStyle_makePool);
        InkStyle::cls()->imprint()->initObject(false);
        
        // DimFloat
        DimFloat::cls()->setupImprint(make<Imprint>(DimFloat::cls(), "DimFloat", STRUCT));
        DimFloat::cls()->imprint()->addMember(make<Member>(Typed<float>::cls(), 0, "x", &DimFloat_x, &DimFloat_setX, false, true));
        DimFloat::cls()->imprint()->addMember(make<Member>(Typed<float>::cls(), 1, "y", &DimFloat_y, &DimFloat_setY, false, true));
        DimFloat::cls()->imprint()->initRefMethods<DimFloat>();
        DimFloat::cls()->imprint()->setConstructor(make<Method>(DimFloat::cls(), "DimFloat", nullptr, LrefVector({ lref(float()), lref(float()) }), StringVector({ "x", "y" }), LrefVector({ lref(float()), lref(float()) })));
        DimFloat::cls()->imprint()->initInjectors(&DimFloat_proto_poolinject, &DimFloat_proto_lrefinject, &DimFloat_makePool);
        DimFloat::cls()->imprint()->initObject(false);
        
        // DimPivot
        DimPivot::cls()->setupImprint(make<Imprint>(DimPivot::cls(), "DimPivot", STRUCT));
        DimPivot::cls()->imprint()->addMember(make<Member>(Typed<Pivot>::cls(), 0, "x", &DimPivot_x, &DimPivot_setX, false, true));
        DimPivot::cls()->imprint()->addMember(make<Member>(Typed<Pivot>::cls(), 1, "y", &DimPivot_y, &DimPivot_setY, false, true));
        DimPivot::cls()->imprint()->initRefMethods<DimPivot>();
        DimPivot::cls()->imprint()->setConstructor(make<Method>(DimPivot::cls(), "DimPivot", nullptr, LrefVector({ lref(Pivot()), lref(Pivot()) }), StringVector({ "x", "y" }), LrefVector({ lref(Pivot()), lref(Pivot()) })));
        DimPivot::cls()->imprint()->initInjectors(&DimPivot_proto_poolinject, &DimPivot_proto_lrefinject, &DimPivot_makePool);
        DimPivot::cls()->imprint()->initObject(false);
        
        // LayoutStyle
        LayoutStyle::cls()->setupImprint(make<Imprint>(LayoutStyle::cls(), "LayoutStyle", STRUCT));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<string>::cls(), 0, "d_name", &LayoutStyle_d_name, &LayoutStyle_setD_name, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<Flow>::cls(), 1, "d_flow", &LayoutStyle_d_flow, &LayoutStyle_setD_flow, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<Overflow>::cls(), 2, "d_overflow", &LayoutStyle_d_overflow, &LayoutStyle_setD_overflow, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<BoxLayer>::cls(), 3, "d_layer", &LayoutStyle_d_layer, &LayoutStyle_setD_layer, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<Opacity>::cls(), 4, "d_opacity", &LayoutStyle_d_opacity, &LayoutStyle_setD_opacity, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<bool>::cls(), 5, "d_div", &LayoutStyle_d_div, &LayoutStyle_setD_div, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<Dimension>::cls(), 6, "d_layoutDim", &LayoutStyle_d_layoutDim, &LayoutStyle_setD_layoutDim, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 7, "d_span", &LayoutStyle_d_span, &LayoutStyle_setD_span, true, true, &LayoutStyle_d_span_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 8, "d_size", &LayoutStyle_d_size, &LayoutStyle_setD_size, true, true, &LayoutStyle_d_size_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 9, "d_frontpadding", &LayoutStyle_d_frontpadding, &LayoutStyle_setD_frontpadding, true, true, &LayoutStyle_d_frontpadding_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 10, "d_backpadding", &LayoutStyle_d_backpadding, &LayoutStyle_setD_backpadding, true, true, &LayoutStyle_d_backpadding_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 11, "d_margin", &LayoutStyle_d_margin, &LayoutStyle_setD_margin, true, true, &LayoutStyle_d_margin_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimFloat::cls(), 12, "d_spacing", &LayoutStyle_d_spacing, &LayoutStyle_setD_spacing, true, true, &LayoutStyle_d_spacing_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(DimPivot::cls(), 13, "d_pivot", &LayoutStyle_d_pivot, &LayoutStyle_setD_pivot, true, true, &LayoutStyle_d_pivot_object));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<std::vector<float>>::cls(), 14, "d_weightTable", &LayoutStyle_d_weightTable, &LayoutStyle_setD_weightTable, false, true));
        LayoutStyle::cls()->imprint()->addMember(make<Member>(Typed<int>::cls(), 15, "d_updated", &LayoutStyle_d_updated, &LayoutStyle_setD_updated, false, true));
        LayoutStyle::cls()->imprint()->initRefMethods<LayoutStyle>();
        LayoutStyle::cls()->imprint()->initObject(false);
        
        // Widget
        Widget::cls()->setupImprint(make<Imprint>(Widget::cls(), "Widget", OBJECT));
        Widget::cls()->imprint()->addMember(make<Member>(Typed<Sheet>::cls(), 0, "parent", &Widget_parent, nullptr, false, false));
        Widget::cls()->imprint()->addMember(make<Member>(Typed<string>::cls(), 1, "clas", &Widget_clas, nullptr, false, false));
        Widget::cls()->imprint()->addMember(make<Member>(Typed<Frame>::cls(), 2, "frame", &Widget_frame, nullptr, false, false));
        Widget::cls()->imprint()->addMember(make<Member>(InkStyle::cls(), 3, "skin", &Widget_skin, nullptr, false, false, &Widget_skin_object));
        Widget::cls()->imprint()->addMember(make<Member>(LayoutStyle::cls(), 4, "layoutStyle", &Widget_layoutStyle, nullptr, false, false, &Widget_layoutStyle_object));
        Widget::cls()->imprint()->addMember(make<Member>(InkStyle::cls(), 5, "inkStyle", &Widget_inkStyle, nullptr, false, false, &Widget_inkStyle_object));
        Widget::cls()->imprint()->initObject(false);
        
        
        types.push_back(InkStyle::cls());
        types.push_back(DimFloat::cls());
        types.push_back(DimPivot::cls());
        types.push_back(LayoutStyle::cls());
        types.push_back(Widget::cls());
	}
#endif // IMPRINT_DEF_FILE
}

#endif // MKUIIMPRINTS_H_INCLUDED