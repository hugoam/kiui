

#ifndef TOYUI_META_H
#define TOYUI_META_H

#include <toyui/Config.h>
#include <toyui/Forward.h>
#include <toyui/Bundle.h>
#include <toyui/Types.h>

#include <toyobj/Reflect/Meta.h>
#include <toyobj/Module/Module.h>

namespace toy
{
#ifdef TOYUI_REFLECTION_IMPL
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
    
	template <> TOY_UI_EXPORT Type& cls<Space>() { static Type ty("Space"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Space>>() { static Type ty("MemberPointer<Space>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Space>>() { static Type ty("MethodPointer<Space>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dim<size_t>>() { static Type ty("Dim<size_t>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<size_t>>>() { static Type ty("MemberPointer<Dim<size_t>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<size_t>>>() { static Type ty("MethodPointer<Dim<size_t>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dim<AutoLayout>>() { static Type ty("Dim<AutoLayout>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<AutoLayout>>>() { static Type ty("MemberPointer<Dim<AutoLayout>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<AutoLayout>>>() { static Type ty("MethodPointer<Dim<AutoLayout>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dim<Sizing>>() { static Type ty("Dim<Sizing>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Sizing>>>() { static Type ty("MemberPointer<Dim<Sizing>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Sizing>>>() { static Type ty("MethodPointer<Dim<Sizing>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dim<Align>>() { static Type ty("Dim<Align>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Align>>>() { static Type ty("MemberPointer<Dim<Align>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Align>>>() { static Type ty("MethodPointer<Dim<Align>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dim<Pivot>>() { static Type ty("Dim<Pivot>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Pivot>>>() { static Type ty("MemberPointer<Dim<Pivot>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Pivot>>>() { static Type ty("MethodPointer<Dim<Pivot>>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<DimFloat>() { static Type ty("DimFloat"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<DimFloat>>() { static Type ty("MemberPointer<DimFloat>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<DimFloat>>() { static Type ty("MethodPointer<DimFloat>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<BoxFloat>() { static Type ty("BoxFloat"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<BoxFloat>>() { static Type ty("MemberPointer<BoxFloat>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<BoxFloat>>() { static Type ty("MethodPointer<BoxFloat>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Image>() { static Type ty("Image"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Image>>() { static Type ty("MemberPointer<Image>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Image>>() { static Type ty("MethodPointer<Image>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<ImageSkin>() { static Type ty("ImageSkin"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<ImageSkin>>() { static Type ty("MemberPointer<ImageSkin>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<ImageSkin>>() { static Type ty("MethodPointer<ImageSkin>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Shadow>() { static Type ty("Shadow"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Shadow>>() { static Type ty("MemberPointer<Shadow>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Shadow>>() { static Type ty("MethodPointer<Shadow>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Paint>() { static Type ty("Paint"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Layout>() { static Type ty("Layout"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Layout>>() { static Type ty("MemberPointer<Layout>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Layout>>() { static Type ty("MethodPointer<Layout>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<InkStyle>() { static Type ty("InkStyle"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<InkStyle>>() { static Type ty("MemberPointer<InkStyle>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<InkStyle>>() { static Type ty("MethodPointer<InkStyle>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Style>() { static Type ty("Style"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Style>>() { static Type ty("MemberPointer<Style>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Style>>() { static Type ty("MethodPointer<Style>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Caption>() { static Type ty("Caption"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Frame>() { static Type ty("Frame"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Widget>() { static Type ty("Widget"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Widget>>() { static Type ty("MemberPointer<Widget>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Widget>>() { static Type ty("MethodPointer<Widget>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<RenderTarget>() { static Type ty("RenderTarget"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<UiWindow>() { static Type ty("UiWindow"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Styler>() { static Type ty("Styler"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Layer>() { static Type ty("Layer", cls<Frame>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Wedge>() { static Type ty("Wedge", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Wedge>>() { static Type ty("MemberPointer<Wedge>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Wedge>>() { static Type ty("MethodPointer<Wedge>"); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Label>() { static Type ty("Label", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Button>() { static Type ty("Button", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Toggle>() { static Type ty("Toggle", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<WindowSizer>() { static Type ty("WindowSizer", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NodeKnob>() { static Type ty("NodeKnob", cls<Widget>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<GridSheet>() { static Type ty("GridSheet", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Tooltip>() { static Type ty("Tooltip", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Rectangle>() { static Type ty("Rectangle", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Cursor>() { static Type ty("Cursor", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<RootSheet>() { static Type ty("RootSheet", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<WrapButton>() { static Type ty("WrapButton", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Slider>() { static Type ty("Slider", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Scrollbar>() { static Type ty("Scrollbar", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Fillbar>() { static Type ty("Fillbar", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Checkbox>() { static Type ty("Checkbox", cls<Toggle>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<ScrollSheet>() { static Type ty("ScrollSheet", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Popup>() { static Type ty("Popup", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<TypeIn>() { static Type ty("TypeIn", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<RadioSwitch>() { static Type ty("RadioSwitch", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<SliderInput<float>>() { static Type ty("SliderInput<float>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<SliderInput<int>>() { static Type ty("SliderInput<int>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NumberInput<unsigned int>>() { static Type ty("NumberInput<unsigned int>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NumberInput<int>>() { static Type ty("NumberInput<int>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NumberInput<float>>() { static Type ty("NumberInput<float>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NumberInput<double>>() { static Type ty("NumberInput<double>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<bool>>() { static Type ty("Input<bool>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<Colour>>() { static Type ty("Input<Colour>", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Expandbox>() { static Type ty("Expandbox", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Tree>() { static Type ty("Tree", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Table>() { static Type ty("Table", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Tab>() { static Type ty("Tab", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Tabber>() { static Type ty("Tabber", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Directory>() { static Type ty("Directory", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<FileBrowser>() { static Type ty("FileBrowser", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dockspace>() { static Type ty("Dockspace", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<WindowHeader>() { static Type ty("WindowHeader", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<WindowFooter>() { static Type ty("WindowFooter", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Window>() { static Type ty("Window", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dockbar>() { static Type ty("Dockbar", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NodePlug>() { static Type ty("NodePlug", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NodeCable>() { static Type ty("NodeCable", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<NodeHeader>() { static Type ty("NodeHeader", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Node>() { static Type ty("Node", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Menubar>() { static Type ty("Menubar", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Tooldock>() { static Type ty("Tooldock", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Toolbar>() { static Type ty("Toolbar", cls<Wedge>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<MultiButton>() { static Type ty("MultiButton", cls<WrapButton>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<ScrollPlan>() { static Type ty("ScrollPlan", cls<ScrollSheet>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<SelectList>() { static Type ty("SelectList", cls<ScrollSheet>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dropdown>() { static Type ty("Dropdown", cls<WrapButton>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<FilterInput>() { static Type ty("FilterInput", cls<TypeIn>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Textbox>() { static Type ty("Textbox", cls<TypeIn>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<unsigned int>>() { static Type ty("Input<unsigned int>", cls<NumberInput<unsigned int>>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<int>>() { static Type ty("Input<int>", cls<NumberInput<int>>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<float>>() { static Type ty("Input<float>", cls<NumberInput<float>>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<double>>() { static Type ty("Input<double>", cls<NumberInput<double>>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Input<string>>() { static Type ty("Input<string>", cls<TypeIn>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<TreeNode>() { static Type ty("TreeNode", cls<Expandbox>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Docksection>() { static Type ty("Docksection", cls<Tabber>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dockline>() { static Type ty("Dockline", cls<GridSheet>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dockbox>() { static Type ty("Dockbox", cls<Window>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<DropdownInput>() { static Type ty("DropdownInput", cls<Dropdown>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Dir>() { static Type ty("Dir", cls<MultiButton>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<File>() { static Type ty("File", cls<MultiButton>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<FileNode>() { static Type ty("FileNode", cls<TreeNode>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<DirectoryNode>() { static Type ty("DirectoryNode", cls<TreeNode>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Canvas>() { static Type ty("Canvas", cls<ScrollPlan>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<Menu>() { static Type ty("Menu", cls<Dropdown>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<TypedownInput>() { static Type ty("TypedownInput", cls<DropdownInput>()); return ty; }
	template <> TOY_UI_EXPORT Type& cls<ToolButton>() { static Type ty("ToolButton", cls<DropdownInput>()); return ty; }
#endif
    
    
    // Base Types
    
    // Enums
	template <>
	struct Reflection<Dimension> : public Meta
	{
        string m_name = "Dimension";
        size_t m_size = sizeof(Dimension);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "DIM_X", "DIM_Y", "DIM_XX", "DIM_YY", "DIM_NULL" }; // std::array<string, 5>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3, 4 }; // std::array<size_t, 5> 
        
        Reflection() : Meta(cls<Dimension>()) { this->initRefMethods<Dimension>(); this->initString<Dimension>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Direction> : public Meta
	{
        string m_name = "Direction";
        size_t m_size = sizeof(Direction);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "DIRECTION_NONE", "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL" }; // std::array<string, 5>
		std::vector<size_t> m_enumValues = { 4, 0, 1, 2, 3 }; // std::array<size_t, 5> 
        
        Reflection() : Meta(cls<Direction>()) { this->initRefMethods<Direction>(); this->initString<Direction>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Pivot> : public Meta
	{
        string m_name = "Pivot";
        size_t m_size = sizeof(Pivot);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "FORWARD", "REVERSE" }; // std::array<string, 2>
		std::vector<size_t> m_enumValues = { 0, 1 }; // std::array<size_t, 2> 
        
        Reflection() : Meta(cls<Pivot>()) { this->initRefMethods<Pivot>(); this->initString<Pivot>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Align> : public Meta
	{
        string m_name = "Align";
        size_t m_size = sizeof(Align);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "LEFT", "CENTER", "RIGHT", "OUT_LEFT", "OUT_RIGHT" }; // std::array<string, 5>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3, 4 }; // std::array<size_t, 5> 
        
        Reflection() : Meta(cls<Align>()) { this->initRefMethods<Align>(); this->initString<Align>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<FrameType> : public Meta
	{
        string m_name = "FrameType";
        size_t m_size = sizeof(FrameType);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "FRAME", "LAYER", "MASTER_LAYER", "SPACE_LAYER" }; // std::array<string, 4>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3 }; // std::array<size_t, 4> 
        
        Reflection() : Meta(cls<FrameType>()) { this->initRefMethods<FrameType>(); this->initString<FrameType>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<LayoutSolver> : public Meta
	{
        string m_name = "LayoutSolver";
        size_t m_size = sizeof(LayoutSolver);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" }; // std::array<string, 4>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3 }; // std::array<size_t, 4> 
        
        Reflection() : Meta(cls<LayoutSolver>()) { this->initRefMethods<LayoutSolver>(); this->initString<LayoutSolver>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<AutoLayout> : public Meta
	{
        string m_name = "AutoLayout";
        size_t m_size = sizeof(AutoLayout);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" }; // std::array<string, 3>
		std::vector<size_t> m_enumValues = { 0, 1, 2 }; // std::array<size_t, 3> 
        
        Reflection() : Meta(cls<AutoLayout>()) { this->initRefMethods<AutoLayout>(); this->initString<AutoLayout>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Flow> : public Meta
	{
        string m_name = "Flow";
        size_t m_size = sizeof(Flow);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "FLOW", "OVERLAY", "ALIGN", "FREE" }; // std::array<string, 4>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3 }; // std::array<size_t, 4> 
        
        Reflection() : Meta(cls<Flow>()) { this->initRefMethods<Flow>(); this->initString<Flow>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Sizing> : public Meta
	{
        string m_name = "Sizing";
        size_t m_size = sizeof(Sizing);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "FIXED", "SHRINK", "WRAP", "EXPAND" }; // std::array<string, 4>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3 }; // std::array<size_t, 4> 
        
        Reflection() : Meta(cls<Sizing>()) { this->initRefMethods<Sizing>(); this->initString<Sizing>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<SpacePreset> : public Meta
	{
        string m_name = "SpacePreset";
        size_t m_size = sizeof(SpacePreset);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD", "LAYOUT" }; // std::array<string, 11>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // std::array<size_t, 11> 
        
        Reflection() : Meta(cls<SpacePreset>()) { this->initRefMethods<SpacePreset>(); this->initString<SpacePreset>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Clipping> : public Meta
	{
        string m_name = "Clipping";
        size_t m_size = sizeof(Clipping);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "NOCLIP", "CLIP" }; // std::array<string, 2>
		std::vector<size_t> m_enumValues = { 0, 1 }; // std::array<size_t, 2> 
        
        Reflection() : Meta(cls<Clipping>()) { this->initRefMethods<Clipping>(); this->initString<Clipping>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<Opacity> : public Meta
	{
        string m_name = "Opacity";
        size_t m_size = sizeof(Opacity);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "OPAQUE", "CLEAR", "HOLLOW" }; // std::array<string, 3>
		std::vector<size_t> m_enumValues = { 0, 1, 2 }; // std::array<size_t, 3> 
        
        Reflection() : Meta(cls<Opacity>()) { this->initRefMethods<Opacity>(); this->initString<Opacity>(); this->setup(*this); }
    };
    
	template <>
	struct Reflection<WidgetState> : public Meta
	{
        string m_name = "WidgetState";
        size_t m_size = sizeof(WidgetState);
        TypeClass m_typeClass = ENUM;
        std::vector<string> m_enumIds = { "NOSTATE", "FOCUSED", "TRIGGERED", "ACTIVATED", "SELECTED", "DRAGGED", "DISABLED", "ACTIVE", "CONTROL", "MODAL" }; // std::array<string, 10>
		std::vector<size_t> m_enumValues = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256 }; // std::array<size_t, 10> 
        
        Reflection() : Meta(cls<WidgetState>()) { this->initRefMethods<WidgetState>(); this->initString<WidgetState>(); this->setup(*this); }
    };
    
    
    // Sequences
	template <>
	struct Reflection<std::vector<Widget*>> : public Meta
	{
        string m_name = "std::vector<Widget*>";
        size_t m_size = sizeof(std::vector<Widget*>);
        TypeClass m_typeClass = SEQUENCE;
        Type* m_content = &cls<Widget>();
        
        Reflection() : Meta(cls<std::vector<Widget*>>()) { this->initRefMethods<std::vector<Widget*>>(); this->initVector<Widget*>(); this->setup(*this); }
    };
    
    
    // Stores
    
    
    
    // Space
	template <>
	struct Reflection<Space> : public Meta
	{
        string m_name = "Space";
        size_t m_size = sizeof(Space);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        struct {
            Member direction = { cls<Space>(), member_var(&Space::direction), cls<Direction>(), "direction", member_getter<Direction>(&Space::direction), nullptr, MEMBER_VALUE };
            Member sizingLength = { cls<Space>(), member_var(&Space::sizingLength), cls<Sizing>(), "sizingLength", member_getter<Sizing>(&Space::sizingLength), nullptr, MEMBER_VALUE };
            Member sizingDepth = { cls<Space>(), member_var(&Space::sizingDepth), cls<Sizing>(), "sizingDepth", member_getter<Sizing>(&Space::sizingDepth), nullptr, MEMBER_VALUE };
        } member;
        std::vector<Member> m_members = { member.direction, member.sizingLength, member.sizingDepth };
        
        Reflection() : Meta(cls<Space>()) { this->setup(*this); }
    };
        
    
    // Dim<size_t>
	template <>
	struct Reflection<Dim<size_t>> : public Meta
	{
        string m_name = "Dim<size_t>";
        size_t m_size = sizeof(Dim<size_t>);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<Dim<size_t>>(), member_var(&Dim<size_t>::x), cls<uint32_t>(), "x", member_getter<size_t>(&Dim<size_t>::x), nullptr, MEMBER_VALUE };
            Member y = { cls<Dim<size_t>>(), member_var(&Dim<size_t>::y), cls<uint32_t>(), "y", member_getter<size_t>(&Dim<size_t>::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Dim<size_t>>() = Dim<size_t>( args[0].val<size_t>(), args[1].val<size_t>() ); };
            Constructor constructor_0 = { cls<Dim<size_t>>(), construct_0, ParamVector({ Param("x", var(size_t()), false, INPUT_PARAM), Param("y", var(size_t()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Dim<size_t>>() = Dim<size_t>(  ); };
            Constructor constructor_1 = { cls<Dim<size_t>>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Dim<size_t>>()) { this->initRefMethods<Dim<size_t>>(); this->initString<Dim<size_t>>(); this->setup(*this); }
    };
        
    
    // Dim<AutoLayout>
	template <>
	struct Reflection<Dim<AutoLayout>> : public Meta
	{
        string m_name = "Dim<AutoLayout>";
        size_t m_size = sizeof(Dim<AutoLayout>);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<Dim<AutoLayout>>(), member_var(&Dim<AutoLayout>::x), cls<AutoLayout>(), "x", member_getter<AutoLayout>(&Dim<AutoLayout>::x), nullptr, MEMBER_VALUE };
            Member y = { cls<Dim<AutoLayout>>(), member_var(&Dim<AutoLayout>::y), cls<AutoLayout>(), "y", member_getter<AutoLayout>(&Dim<AutoLayout>::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Dim<AutoLayout>>() = Dim<AutoLayout>( args[0].val<AutoLayout>(), args[1].val<AutoLayout>() ); };
            Constructor constructor_0 = { cls<Dim<AutoLayout>>(), construct_0, ParamVector({ Param("x", var(AutoLayout()), false, INPUT_PARAM), Param("y", var(AutoLayout()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Dim<AutoLayout>>() = Dim<AutoLayout>(  ); };
            Constructor constructor_1 = { cls<Dim<AutoLayout>>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Dim<AutoLayout>>()) { this->initRefMethods<Dim<AutoLayout>>(); this->initString<Dim<AutoLayout>>(); this->setup(*this); }
    };
        
    
    // Dim<Sizing>
	template <>
	struct Reflection<Dim<Sizing>> : public Meta
	{
        string m_name = "Dim<Sizing>";
        size_t m_size = sizeof(Dim<Sizing>);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<Dim<Sizing>>(), member_var(&Dim<Sizing>::x), cls<Sizing>(), "x", member_getter<Sizing>(&Dim<Sizing>::x), nullptr, MEMBER_VALUE };
            Member y = { cls<Dim<Sizing>>(), member_var(&Dim<Sizing>::y), cls<Sizing>(), "y", member_getter<Sizing>(&Dim<Sizing>::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Dim<Sizing>>() = Dim<Sizing>( args[0].val<Sizing>(), args[1].val<Sizing>() ); };
            Constructor constructor_0 = { cls<Dim<Sizing>>(), construct_0, ParamVector({ Param("x", var(Sizing()), false, INPUT_PARAM), Param("y", var(Sizing()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Dim<Sizing>>() = Dim<Sizing>(  ); };
            Constructor constructor_1 = { cls<Dim<Sizing>>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Dim<Sizing>>()) { this->initRefMethods<Dim<Sizing>>(); this->initString<Dim<Sizing>>(); this->setup(*this); }
    };
        
    
    // Dim<Align>
	template <>
	struct Reflection<Dim<Align>> : public Meta
	{
        string m_name = "Dim<Align>";
        size_t m_size = sizeof(Dim<Align>);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<Dim<Align>>(), member_var(&Dim<Align>::x), cls<Align>(), "x", member_getter<Align>(&Dim<Align>::x), nullptr, MEMBER_VALUE };
            Member y = { cls<Dim<Align>>(), member_var(&Dim<Align>::y), cls<Align>(), "y", member_getter<Align>(&Dim<Align>::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Dim<Align>>() = Dim<Align>( args[0].val<Align>(), args[1].val<Align>() ); };
            Constructor constructor_0 = { cls<Dim<Align>>(), construct_0, ParamVector({ Param("x", var(Align()), false, INPUT_PARAM), Param("y", var(Align()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Dim<Align>>() = Dim<Align>(  ); };
            Constructor constructor_1 = { cls<Dim<Align>>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Dim<Align>>()) { this->initRefMethods<Dim<Align>>(); this->initString<Dim<Align>>(); this->setup(*this); }
    };
        
    
    // Dim<Pivot>
	template <>
	struct Reflection<Dim<Pivot>> : public Meta
	{
        string m_name = "Dim<Pivot>";
        size_t m_size = sizeof(Dim<Pivot>);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<Dim<Pivot>>(), member_var(&Dim<Pivot>::x), cls<Pivot>(), "x", member_getter<Pivot>(&Dim<Pivot>::x), nullptr, MEMBER_VALUE };
            Member y = { cls<Dim<Pivot>>(), member_var(&Dim<Pivot>::y), cls<Pivot>(), "y", member_getter<Pivot>(&Dim<Pivot>::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Dim<Pivot>>() = Dim<Pivot>( args[0].val<Pivot>(), args[1].val<Pivot>() ); };
            Constructor constructor_0 = { cls<Dim<Pivot>>(), construct_0, ParamVector({ Param("x", var(Pivot()), false, INPUT_PARAM), Param("y", var(Pivot()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Dim<Pivot>>() = Dim<Pivot>(  ); };
            Constructor constructor_1 = { cls<Dim<Pivot>>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Dim<Pivot>>()) { this->initRefMethods<Dim<Pivot>>(); this->initString<Dim<Pivot>>(); this->setup(*this); }
    };
        
    
    // DimFloat
	template <>
	struct Reflection<DimFloat> : public Meta
	{
        string m_name = "DimFloat";
        size_t m_size = sizeof(DimFloat);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<DimFloat>(), member_var(&DimFloat::x), cls<float>(), "x", member_getter<float>(&DimFloat::x), nullptr, MEMBER_VALUE };
            Member y = { cls<DimFloat>(), member_var(&DimFloat::y), cls<float>(), "y", member_getter<float>(&DimFloat::y), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<DimFloat>() = DimFloat( args[0].val<float>(), args[1].val<float>() ); };
            Constructor constructor_0 = { cls<DimFloat>(), construct_0, ParamVector({ Param("x", var(float()), false, INPUT_PARAM), Param("y", var(float()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) {  ref.val<DimFloat>() = DimFloat( args[0].val<float>() ); };
            Constructor constructor_1 = { cls<DimFloat>(), construct_1, ParamVector({ Param("val", var(float()), false, INPUT_PARAM) }) };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<DimFloat>()) { this->initRefMethods<DimFloat>(); this->initString<DimFloat>(); this->setup(*this); }
    };
        
    
    // BoxFloat
	template <>
	struct Reflection<BoxFloat> : public Meta
	{
        string m_name = "BoxFloat";
        size_t m_size = sizeof(BoxFloat);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member x = { cls<BoxFloat>(), member_var(&BoxFloat::x), cls<float>(), "x", member_getter<float>(&BoxFloat::x), nullptr, MEMBER_VALUE };
            Member y = { cls<BoxFloat>(), member_var(&BoxFloat::y), cls<float>(), "y", member_getter<float>(&BoxFloat::y), nullptr, MEMBER_VALUE };
            Member w = { cls<BoxFloat>(), member_var(&BoxFloat::w), cls<float>(), "w", member_getter<float>(&BoxFloat::w), nullptr, MEMBER_VALUE };
            Member h = { cls<BoxFloat>(), member_var(&BoxFloat::h), cls<float>(), "h", member_getter<float>(&BoxFloat::h), nullptr, MEMBER_VALUE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<BoxFloat>() = BoxFloat( args[0].val<float>(), args[1].val<float>(), args[2].val<float>(), args[3].val<float>() ); };
            Constructor constructor_0 = { cls<BoxFloat>(), construct_0, ParamVector({ Param("x0", var(float()), false, INPUT_PARAM), Param("y0", var(float()), false, INPUT_PARAM), Param("x1", var(float()), false, INPUT_PARAM), Param("y1", var(float()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) {  ref.val<BoxFloat>() = BoxFloat( args[0].val<float>() ); };
            Constructor constructor_1 = { cls<BoxFloat>(), construct_1, ParamVector({ Param("uniform", var(float()), false, INPUT_PARAM) }) };
        } constructor;
        std::vector<Member> m_members = { member.x, member.y, member.w, member.h };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<BoxFloat>()) { this->initRefMethods<BoxFloat>(); this->initString<BoxFloat>(); this->setup(*this); }
    };
        
    
    // Image
	template <>
	struct Reflection<Image> : public Meta
	{
        string m_name = "Image";
        size_t m_size = sizeof(Image);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member d_name = { cls<Image>(), member_var(&Image::d_name), cls<string>(), "d_name", member_getter<string>(&Image::d_name), nullptr, MEMBER_VALUE };
            Member d_path = { cls<Image>(), member_var(&Image::d_path), cls<string>(), "d_path", member_getter<string>(&Image::d_path), nullptr, MEMBER_VALUE };
        } member;
        std::vector<Member> m_members = { member.d_name, member.d_path };
        
        Reflection() : Meta(cls<Image>()) { this->initRefMethods<Image>(); this->setup(*this); }
    };
        
    
    // ImageSkin
	template <>
	struct Reflection<ImageSkin> : public Meta
	{
        string m_name = "ImageSkin";
        size_t m_size = sizeof(ImageSkin);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member d_image = { cls<ImageSkin>(), member_var(&ImageSkin::d_image), cls<Image>(), "d_image", member_getter<Image>(&ImageSkin::d_image), member_setter<Image*>(&ImageSkin::d_image), MEMBER_MUTABLE };
            Member d_left = { cls<ImageSkin>(), member_var(&ImageSkin::d_left), cls<int>(), "d_left", member_getter<int>(&ImageSkin::d_left), member_setter<int>(&ImageSkin::d_left), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_top = { cls<ImageSkin>(), member_var(&ImageSkin::d_top), cls<int>(), "d_top", member_getter<int>(&ImageSkin::d_top), member_setter<int>(&ImageSkin::d_top), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_right = { cls<ImageSkin>(), member_var(&ImageSkin::d_right), cls<int>(), "d_right", member_getter<int>(&ImageSkin::d_right), member_setter<int>(&ImageSkin::d_right), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_bottom = { cls<ImageSkin>(), member_var(&ImageSkin::d_bottom), cls<int>(), "d_bottom", member_getter<int>(&ImageSkin::d_bottom), member_setter<int>(&ImageSkin::d_bottom), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_margin = { cls<ImageSkin>(), member_var(&ImageSkin::m_margin), cls<int>(), "margin", member_getter<int>(&ImageSkin::m_margin), member_setter<int>(&ImageSkin::m_margin), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_stretch = { cls<ImageSkin>(), member_var(&ImageSkin::d_stretch), cls<Dimension>(), "d_stretch", member_getter<Dimension>(&ImageSkin::d_stretch), member_setter<Dimension>(&ImageSkin::d_stretch), MEMBER_VALUE|MEMBER_MUTABLE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<ImageSkin>() = ImageSkin( args[0].val<Image>(), args[1].val<int>(), args[2].val<int>(), args[3].val<int>(), args[4].val<int>(), args[5].val<int>(), args[6].val<Dimension>() ); };
            Constructor constructor_0 = { cls<ImageSkin>(), construct_0, ParamVector({ Param("image", var(Image()), false, INPUT_PARAM), Param("left", var(int()), false, INPUT_PARAM), Param("top", var(int()), false, INPUT_PARAM), Param("right", var(int()), false, INPUT_PARAM), Param("bottom", var(int()), false, INPUT_PARAM), Param("margin", var(int(0)), false, INPUT_PARAM), Param("stretch", var(Dimension()), false, INPUT_PARAM) }) };
        } constructor;
        std::vector<Member> m_members = { member.d_image, member.d_left, member.d_top, member.d_right, member.d_bottom, member.m_margin, member.d_stretch };
        std::vector<Constructor> m_constructors = { constructor.constructor_0 };
        
        Reflection() : Meta(cls<ImageSkin>()) { this->initRefMethods<ImageSkin>(); this->setup(*this); }
    };
        
    
    // Shadow
	template <>
	struct Reflection<Shadow> : public Meta
	{
        string m_name = "Shadow";
        size_t m_size = sizeof(Shadow);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member d_xpos = { cls<Shadow>(), member_var(&Shadow::d_xpos), cls<float>(), "d_xpos", member_getter<float>(&Shadow::d_xpos), member_setter<float>(&Shadow::d_xpos), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_ypos = { cls<Shadow>(), member_var(&Shadow::d_ypos), cls<float>(), "d_ypos", member_getter<float>(&Shadow::d_ypos), member_setter<float>(&Shadow::d_ypos), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_blur = { cls<Shadow>(), member_var(&Shadow::d_blur), cls<float>(), "d_blur", member_getter<float>(&Shadow::d_blur), member_setter<float>(&Shadow::d_blur), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_spread = { cls<Shadow>(), member_var(&Shadow::d_spread), cls<float>(), "d_spread", member_getter<float>(&Shadow::d_spread), member_setter<float>(&Shadow::d_spread), MEMBER_VALUE|MEMBER_MUTABLE };
            Member d_colour = { cls<Shadow>(), member_var(&Shadow::d_colour), cls<Colour>(), "d_colour", member_getter<Colour>(&Shadow::d_colour), member_setter<Colour>(&Shadow::d_colour), MEMBER_VALUE|MEMBER_MUTABLE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Shadow>() = Shadow( args[0].val<float>(), args[1].val<float>(), args[2].val<float>(), args[3].val<float>(), args[4].val<Colour>() ); };
            Constructor constructor_0 = { cls<Shadow>(), construct_0, ParamVector({ Param("xpos", var(float()), false, INPUT_PARAM), Param("ypos", var(float()), false, INPUT_PARAM), Param("blur", var(float()), false, INPUT_PARAM), Param("spread", var(float()), false, INPUT_PARAM), Param("colour", var(Colour()), false, INPUT_PARAM) }) };
            ConstructorFunc construct_1 = [](Ref ref, Var* args) { UNUSED(args); ref.val<Shadow>() = Shadow(  ); };
            Constructor constructor_1 = { cls<Shadow>(), construct_1, {} };
        } constructor;
        std::vector<Member> m_members = { member.d_xpos, member.d_ypos, member.d_blur, member.d_spread, member.d_colour };
        std::vector<Constructor> m_constructors = { constructor.constructor_0, constructor.constructor_1 };
        
        Reflection() : Meta(cls<Shadow>()) { this->initRefMethods<Shadow>(); this->setup(*this); }
    };
        
    
    // Paint
	template <>
	struct Reflection<Paint> : public Meta
	{
        string m_name = "Paint";
        size_t m_size = sizeof(Paint);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Paint>()) { this->initRefMethods<Paint>(); this->setup(*this); }
    };
        
    
    // Layout
	template <>
	struct Reflection<Layout> : public Meta
	{
        string m_name = "Layout";
        size_t m_size = sizeof(Layout);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member m_name = { cls<Layout>(), member_var(&Layout::m_name), cls<string>(), "name", member_getter<string>(&Layout::m_name), member_setter<string>(&Layout::m_name), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_solver = { cls<Layout>(), member_var(&Layout::m_solver), cls<LayoutSolver>(), "solver", member_getter<LayoutSolver>(&Layout::m_solver), member_setter<LayoutSolver>(&Layout::m_solver), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_layout = { cls<Layout>(), member_var(&Layout::m_layout), cls<Dim<AutoLayout>>(), "layout", member_getter<Dim<AutoLayout>>(&Layout::m_layout), member_setter<Dim<AutoLayout>>(&Layout::m_layout), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_flow = { cls<Layout>(), member_var(&Layout::m_flow), cls<Flow>(), "flow", member_getter<Flow>(&Layout::m_flow), member_setter<Flow>(&Layout::m_flow), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_space = { cls<Layout>(), member_var(&Layout::m_space), cls<Space>(), "space", member_getter<Space>(&Layout::m_space), member_setter<Space>(&Layout::m_space), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_clipping = { cls<Layout>(), member_var(&Layout::m_clipping), cls<Clipping>(), "clipping", member_getter<Clipping>(&Layout::m_clipping), member_setter<Clipping>(&Layout::m_clipping), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_opacity = { cls<Layout>(), member_var(&Layout::m_opacity), cls<Opacity>(), "opacity", member_getter<Opacity>(&Layout::m_opacity), member_setter<Opacity>(&Layout::m_opacity), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_align = { cls<Layout>(), member_var(&Layout::m_align), cls<Dim<Align>>(), "align", member_getter<Dim<Align>>(&Layout::m_align), member_setter<Dim<Align>>(&Layout::m_align), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_span = { cls<Layout>(), member_var(&Layout::m_span), cls<DimFloat>(), "span", member_getter<DimFloat>(&Layout::m_span), member_setter<DimFloat>(&Layout::m_span), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_size = { cls<Layout>(), member_var(&Layout::m_size), cls<DimFloat>(), "size", member_getter<DimFloat>(&Layout::m_size), member_setter<DimFloat>(&Layout::m_size), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_padding = { cls<Layout>(), member_var(&Layout::m_padding), cls<BoxFloat>(), "padding", member_getter<BoxFloat>(&Layout::m_padding), member_setter<BoxFloat>(&Layout::m_padding), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_margin = { cls<Layout>(), member_var(&Layout::m_margin), cls<DimFloat>(), "margin", member_getter<DimFloat>(&Layout::m_margin), member_setter<DimFloat>(&Layout::m_margin), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_spacing = { cls<Layout>(), member_var(&Layout::m_spacing), cls<DimFloat>(), "spacing", member_getter<DimFloat>(&Layout::m_spacing), member_setter<DimFloat>(&Layout::m_spacing), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_pivot = { cls<Layout>(), member_var(&Layout::m_pivot), cls<Dim<Pivot>>(), "pivot", member_getter<Dim<Pivot>>(&Layout::m_pivot), member_setter<Dim<Pivot>>(&Layout::m_pivot), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_zorder = { cls<Layout>(), member_var(&Layout::m_zorder), cls<int>(), "zorder", member_getter<int>(&Layout::m_zorder), member_setter<int>(&Layout::m_zorder), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_updated = { cls<Layout>(), member_var(&Layout::m_updated), cls<uint32_t>(), "updated", member_getter<size_t>(&Layout::m_updated), member_setter<size_t>(&Layout::m_updated), MEMBER_VALUE|MEMBER_MUTABLE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<Layout>() = Layout( args[0].val<string>() ); };
            Constructor constructor_0 = { cls<Layout>(), construct_0, ParamVector({ Param("name", var(string()), false, INPUT_PARAM) }) };
        } constructor;
        std::vector<Member> m_members = { member.m_name, member.m_solver, member.m_layout, member.m_flow, member.m_space, member.m_clipping, member.m_opacity, member.m_align, member.m_span, member.m_size, member.m_padding, member.m_margin, member.m_spacing, member.m_pivot, member.m_zorder, member.m_updated };
        std::vector<Constructor> m_constructors = { constructor.constructor_0 };
        
        Reflection() : Meta(cls<Layout>()) { this->initRefMethods<Layout>(); this->setup(*this); }
    };
        
    
    // InkStyle
	template <>
	struct Reflection<InkStyle> : public Meta
	{
        string m_name = "InkStyle";
        size_t m_size = sizeof(InkStyle);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member m_name = { cls<InkStyle>(), member_var(&InkStyle::m_name), cls<string>(), "name", member_getter<string>(&InkStyle::m_name), member_setter<string>(&InkStyle::m_name), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_empty = { cls<InkStyle>(), member_var(&InkStyle::m_empty), cls<bool>(), "empty", member_getter<bool>(&InkStyle::m_empty), member_setter<bool>(&InkStyle::m_empty), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_background_colour = { cls<InkStyle>(), member_var(&InkStyle::m_background_colour), cls<Colour>(), "background_colour", member_getter<Colour>(&InkStyle::m_background_colour), member_setter<Colour>(&InkStyle::m_background_colour), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_border_colour = { cls<InkStyle>(), member_var(&InkStyle::m_border_colour), cls<Colour>(), "border_colour", member_getter<Colour>(&InkStyle::m_border_colour), member_setter<Colour>(&InkStyle::m_border_colour), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_image_colour = { cls<InkStyle>(), member_var(&InkStyle::m_image_colour), cls<Colour>(), "image_colour", member_getter<Colour>(&InkStyle::m_image_colour), member_setter<Colour>(&InkStyle::m_image_colour), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_text_colour = { cls<InkStyle>(), member_var(&InkStyle::m_text_colour), cls<Colour>(), "text_colour", member_getter<Colour>(&InkStyle::m_text_colour), member_setter<Colour>(&InkStyle::m_text_colour), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_text_font = { cls<InkStyle>(), member_var(&InkStyle::m_text_font), cls<string>(), "text_font", member_getter<string>(&InkStyle::m_text_font), member_setter<string>(&InkStyle::m_text_font), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_text_size = { cls<InkStyle>(), member_var(&InkStyle::m_text_size), cls<float>(), "text_size", member_getter<float>(&InkStyle::m_text_size), member_setter<float>(&InkStyle::m_text_size), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_text_break = { cls<InkStyle>(), member_var(&InkStyle::m_text_break), cls<bool>(), "text_break", member_getter<bool>(&InkStyle::m_text_break), member_setter<bool>(&InkStyle::m_text_break), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_text_wrap = { cls<InkStyle>(), member_var(&InkStyle::m_text_wrap), cls<bool>(), "text_wrap", member_getter<bool>(&InkStyle::m_text_wrap), member_setter<bool>(&InkStyle::m_text_wrap), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_border_width = { cls<InkStyle>(), member_var(&InkStyle::m_border_width), cls<BoxFloat>(), "border_width", member_getter<BoxFloat>(&InkStyle::m_border_width), member_setter<BoxFloat>(&InkStyle::m_border_width), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_corner_radius = { cls<InkStyle>(), member_var(&InkStyle::m_corner_radius), cls<BoxFloat>(), "corner_radius", member_getter<BoxFloat>(&InkStyle::m_corner_radius), member_setter<BoxFloat>(&InkStyle::m_corner_radius), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_weak_corners = { cls<InkStyle>(), member_var(&InkStyle::m_weak_corners), cls<bool>(), "weak_corners", member_getter<bool>(&InkStyle::m_weak_corners), member_setter<bool>(&InkStyle::m_weak_corners), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_padding = { cls<InkStyle>(), member_var(&InkStyle::m_padding), cls<BoxFloat>(), "padding", member_getter<BoxFloat>(&InkStyle::m_padding), member_setter<BoxFloat>(&InkStyle::m_padding), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_margin = { cls<InkStyle>(), member_var(&InkStyle::m_margin), cls<BoxFloat>(), "margin", member_getter<BoxFloat>(&InkStyle::m_margin), member_setter<BoxFloat>(&InkStyle::m_margin), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_align = { cls<InkStyle>(), member_var(&InkStyle::m_align), cls<Dim<Align>>(), "align", member_getter<Dim<Align>>(&InkStyle::m_align), member_setter<Dim<Align>>(&InkStyle::m_align), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_linear_gradient = { cls<InkStyle>(), member_var(&InkStyle::m_linear_gradient), cls<DimFloat>(), "linear_gradient", member_getter<DimFloat>(&InkStyle::m_linear_gradient), member_setter<DimFloat>(&InkStyle::m_linear_gradient), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_linear_gradient_dim = { cls<InkStyle>(), member_var(&InkStyle::m_linear_gradient_dim), cls<Dimension>(), "linear_gradient_dim", member_getter<Dimension>(&InkStyle::m_linear_gradient_dim), member_setter<Dimension>(&InkStyle::m_linear_gradient_dim), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_image = { cls<InkStyle>(), member_var(&InkStyle::m_image), cls<Image>(), "image", member_getter<Image>(&InkStyle::m_image), member_setter<Image*>(&InkStyle::m_image), MEMBER_MUTABLE };
            Member m_overlay = { cls<InkStyle>(), member_var(&InkStyle::m_overlay), cls<Image>(), "overlay", member_getter<Image>(&InkStyle::m_overlay), member_setter<Image*>(&InkStyle::m_overlay), MEMBER_MUTABLE };
            Member m_tile = { cls<InkStyle>(), member_var(&InkStyle::m_tile), cls<Image>(), "tile", member_getter<Image>(&InkStyle::m_tile), member_setter<Image*>(&InkStyle::m_tile), MEMBER_MUTABLE };
            Member m_image_skin = { cls<InkStyle>(), member_var(&InkStyle::m_image_skin), cls<ImageSkin>(), "image_skin", member_getter<ImageSkin>(&InkStyle::m_image_skin), member_setter<ImageSkin>(&InkStyle::m_image_skin), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_shadow = { cls<InkStyle>(), member_var(&InkStyle::m_shadow), cls<Shadow>(), "shadow", member_getter<Shadow>(&InkStyle::m_shadow), member_setter<Shadow>(&InkStyle::m_shadow), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_shadow_colour = { cls<InkStyle>(), member_var(&InkStyle::m_shadow_colour), cls<Colour>(), "shadow_colour", member_getter<Colour>(&InkStyle::m_shadow_colour), member_setter<Colour>(&InkStyle::m_shadow_colour), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_hover_cursor = { cls<InkStyle>(), member_var(&InkStyle::m_hover_cursor), cls<Style>(), "hover_cursor", member_getter<Style>(&InkStyle::m_hover_cursor), member_setter<Style*>(&InkStyle::m_hover_cursor), MEMBER_MUTABLE };
        } member;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, Var* args) {  ref.val<InkStyle>() = InkStyle( args[0].val<string>() ); };
            Constructor constructor_0 = { cls<InkStyle>(), construct_0, ParamVector({ Param("name", var(string()), false, INPUT_PARAM) }) };
        } constructor;
        std::vector<Member> m_members = { member.m_name, member.m_empty, member.m_background_colour, member.m_border_colour, member.m_image_colour, member.m_text_colour, member.m_text_font, member.m_text_size, member.m_text_break, member.m_text_wrap, member.m_border_width, member.m_corner_radius, member.m_weak_corners, member.m_padding, member.m_margin, member.m_align, member.m_linear_gradient, member.m_linear_gradient_dim, member.m_image, member.m_overlay, member.m_tile, member.m_image_skin, member.m_shadow, member.m_shadow_colour, member.m_hover_cursor };
        std::vector<Constructor> m_constructors = { constructor.constructor_0 };
        
        Reflection() : Meta(cls<InkStyle>()) { this->initRefMethods<InkStyle>(); this->setup(*this); }
    };
        
    
    // Style
	template <>
	struct Reflection<Style> : public Meta
	{
        string m_name = "Style";
        size_t m_size = sizeof(Style);
        TypeClass m_typeClass = STRUCT;
        bool m_serializable = false;
        struct {
            Member m_style_type = { cls<Style>(), member_var(&Style::m_style_type), cls<Type>(), "style_type", member_getter<Type>(&Style::m_style_type), nullptr, 0 };
            Member m_base = { cls<Style>(), member_var(&Style::m_base), cls<Style>(), "base", member_getter<Style>(&Style::m_base), nullptr, 0 };
            Member m_name = { cls<Style>(), member_var(&Style::m_name), cls<string>(), "name", member_getter<string>(&Style::m_name), nullptr, MEMBER_VALUE };
            Member m_layout = { cls<Style>(), member_var(&Style::m_layout), cls<Layout>(), "layout", member_getter<Layout>(&Style::m_layout), nullptr, MEMBER_VALUE };
            Member m_skin = { cls<Style>(), member_var(&Style::m_skin), cls<InkStyle>(), "skin", member_getter<InkStyle>(&Style::m_skin), nullptr, MEMBER_VALUE };
        } member;
        std::vector<Member> m_members = { member.m_style_type, member.m_base, member.m_name, member.m_layout, member.m_skin };
        
        Reflection() : Meta(cls<Style>()) { this->initRefMethods<Style>(); this->setup(*this); }
    };
        
    
    // Caption
	template <>
	struct Reflection<Caption> : public Meta
	{
        string m_name = "Caption";
        size_t m_size = sizeof(Caption);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Caption>()) { this->setup(*this); }
    };
        
    
    // Frame
	template <>
	struct Reflection<Frame> : public Meta
	{
        string m_name = "Frame";
        size_t m_size = sizeof(Frame);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Frame>()) { this->setup(*this); }
    };
        
    
    // Widget
	template <>
	struct Reflection<Widget> : public Meta
	{
        string m_name = "Widget";
        size_t m_size = sizeof(Widget);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        struct {
            Member m_parent = { cls<Widget>(), member_var(&Widget::m_parent), cls<Wedge>(), "parent", member_getter<Wedge>(&Widget::m_parent), nullptr, 0 };
            Member m_container = { cls<Widget>(), member_var(&Widget::m_container), cls<Wedge>(), "container", member_getter<Wedge>(&Widget::m_container), nullptr, 0 };
            Member m_index = { cls<Widget>(), member_var(&Widget::m_index), cls<uint32_t>(), "index", member_getter<size_t>(&Widget::m_index), nullptr, MEMBER_VALUE };
            Member m_style = { cls<Widget>(), member_var(&Widget::m_style), cls<Style>(), "style", member_getter<Style>(&Widget::m_style), member_setter<Style*>(&Widget::setStyle), MEMBER_MUTABLE };
            Member m_state = { cls<Widget>(), member_var(&Widget::m_state), cls<WidgetState>(), "state", member_getter<WidgetState>(&Widget::m_state), nullptr, MEMBER_VALUE };
        } member;
        std::vector<Member> m_members = { member.m_parent, member.m_container, member.m_index, member.m_style, member.m_state };
        
        Reflection() : Meta(cls<Widget>()) { this->setup(*this); }
    };
        
    
    // RenderTarget
	template <>
	struct Reflection<RenderTarget> : public Meta
	{
        string m_name = "RenderTarget";
        size_t m_size = sizeof(RenderTarget);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<RenderTarget>()) { this->setup(*this); }
    };
        
    
    // UiWindow
	template <>
	struct Reflection<UiWindow> : public Meta
	{
        string m_name = "UiWindow";
        size_t m_size = sizeof(UiWindow);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<UiWindow>()) { this->setup(*this); }
    };
        
    
    // Styler
	template <>
	struct Reflection<Styler> : public Meta
	{
        string m_name = "Styler";
        size_t m_size = sizeof(Styler);
        TypeClass m_typeClass = OBJECT;
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Styler>()) { this->setup(*this); }
    };
        
    
    // Layer
	template <>
	struct Reflection<Layer> : public Meta
	{
        string m_name = "Layer";
        size_t m_size = sizeof(Layer);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Frame>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Layer>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Wedge
	template <>
	struct Reflection<Wedge> : public Meta
	{
        string m_name = "Wedge";
        size_t m_size = sizeof(Wedge);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        struct {
            Member m_contents = { cls<Wedge>(), member_var(&Wedge::m_contents), cls<std::vector<Widget*>>(), "contents", member_getter<std::vector<Widget*>>(&Wedge::m_contents), nullptr, MEMBER_VALUE|MEMBER_STRUCTURE };
        } member;
        std::vector<Member> m_members = { member.m_contents };
        
        Reflection() : Meta(cls<Wedge>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Label
	template <>
	struct Reflection<Label> : public Meta
	{
        string m_name = "Label";
        size_t m_size = sizeof(Label);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Label>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Button
	template <>
	struct Reflection<Button> : public Meta
	{
        string m_name = "Button";
        size_t m_size = sizeof(Button);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Button>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Toggle
	template <>
	struct Reflection<Toggle> : public Meta
	{
        string m_name = "Toggle";
        size_t m_size = sizeof(Toggle);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Toggle>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // WindowSizer
	template <>
	struct Reflection<WindowSizer> : public Meta
	{
        string m_name = "WindowSizer";
        size_t m_size = sizeof(WindowSizer);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<WindowSizer>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NodeKnob
	template <>
	struct Reflection<NodeKnob> : public Meta
	{
        string m_name = "NodeKnob";
        size_t m_size = sizeof(NodeKnob);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NodeKnob>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // GridSheet
	template <>
	struct Reflection<GridSheet> : public Meta
	{
        string m_name = "GridSheet";
        size_t m_size = sizeof(GridSheet);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<GridSheet>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Tooltip
	template <>
	struct Reflection<Tooltip> : public Meta
	{
        string m_name = "Tooltip";
        size_t m_size = sizeof(Tooltip);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Tooltip>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Rectangle
	template <>
	struct Reflection<Rectangle> : public Meta
	{
        string m_name = "Rectangle";
        size_t m_size = sizeof(Rectangle);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Rectangle>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Cursor
	template <>
	struct Reflection<Cursor> : public Meta
	{
        string m_name = "Cursor";
        size_t m_size = sizeof(Cursor);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Cursor>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // RootSheet
	template <>
	struct Reflection<RootSheet> : public Meta
	{
        string m_name = "RootSheet";
        size_t m_size = sizeof(RootSheet);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<RootSheet>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // WrapButton
	template <>
	struct Reflection<WrapButton> : public Meta
	{
        string m_name = "WrapButton";
        size_t m_size = sizeof(WrapButton);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<WrapButton>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Slider
	template <>
	struct Reflection<Slider> : public Meta
	{
        string m_name = "Slider";
        size_t m_size = sizeof(Slider);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Slider>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Scrollbar
	template <>
	struct Reflection<Scrollbar> : public Meta
	{
        string m_name = "Scrollbar";
        size_t m_size = sizeof(Scrollbar);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Scrollbar>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Fillbar
	template <>
	struct Reflection<Fillbar> : public Meta
	{
        string m_name = "Fillbar";
        size_t m_size = sizeof(Fillbar);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Fillbar>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Checkbox
	template <>
	struct Reflection<Checkbox> : public Meta
	{
        string m_name = "Checkbox";
        size_t m_size = sizeof(Checkbox);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Toggle>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Checkbox>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // ScrollSheet
	template <>
	struct Reflection<ScrollSheet> : public Meta
	{
        string m_name = "ScrollSheet";
        size_t m_size = sizeof(ScrollSheet);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<ScrollSheet>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Popup
	template <>
	struct Reflection<Popup> : public Meta
	{
        string m_name = "Popup";
        size_t m_size = sizeof(Popup);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Popup>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // TypeIn
	template <>
	struct Reflection<TypeIn> : public Meta
	{
        string m_name = "TypeIn";
        size_t m_size = sizeof(TypeIn);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<TypeIn>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // RadioSwitch
	template <>
	struct Reflection<RadioSwitch> : public Meta
	{
        string m_name = "RadioSwitch";
        size_t m_size = sizeof(RadioSwitch);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<RadioSwitch>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // SliderInput<float>
	template <>
	struct Reflection<SliderInput<float>> : public Meta
	{
        string m_name = "SliderInput<float>";
        size_t m_size = sizeof(SliderInput<float>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<SliderInput<float>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // SliderInput<int>
	template <>
	struct Reflection<SliderInput<int>> : public Meta
	{
        string m_name = "SliderInput<int>";
        size_t m_size = sizeof(SliderInput<int>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<SliderInput<int>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NumberInput<unsigned int>
	template <>
	struct Reflection<NumberInput<unsigned int>> : public Meta
	{
        string m_name = "NumberInput<unsigned int>";
        size_t m_size = sizeof(NumberInput<unsigned int>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NumberInput<unsigned int>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NumberInput<int>
	template <>
	struct Reflection<NumberInput<int>> : public Meta
	{
        string m_name = "NumberInput<int>";
        size_t m_size = sizeof(NumberInput<int>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NumberInput<int>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NumberInput<float>
	template <>
	struct Reflection<NumberInput<float>> : public Meta
	{
        string m_name = "NumberInput<float>";
        size_t m_size = sizeof(NumberInput<float>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NumberInput<float>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NumberInput<double>
	template <>
	struct Reflection<NumberInput<double>> : public Meta
	{
        string m_name = "NumberInput<double>";
        size_t m_size = sizeof(NumberInput<double>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NumberInput<double>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<bool>
	template <>
	struct Reflection<Input<bool>> : public Meta
	{
        string m_name = "Input<bool>";
        size_t m_size = sizeof(Input<bool>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<bool>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<Colour>
	template <>
	struct Reflection<Input<Colour>> : public Meta
	{
        string m_name = "Input<Colour>";
        size_t m_size = sizeof(Input<Colour>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<Colour>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Expandbox
	template <>
	struct Reflection<Expandbox> : public Meta
	{
        string m_name = "Expandbox";
        size_t m_size = sizeof(Expandbox);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Expandbox>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Tree
	template <>
	struct Reflection<Tree> : public Meta
	{
        string m_name = "Tree";
        size_t m_size = sizeof(Tree);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Tree>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Table
	template <>
	struct Reflection<Table> : public Meta
	{
        string m_name = "Table";
        size_t m_size = sizeof(Table);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Table>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Tab
	template <>
	struct Reflection<Tab> : public Meta
	{
        string m_name = "Tab";
        size_t m_size = sizeof(Tab);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Tab>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Tabber
	template <>
	struct Reflection<Tabber> : public Meta
	{
        string m_name = "Tabber";
        size_t m_size = sizeof(Tabber);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Tabber>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Directory
	template <>
	struct Reflection<Directory> : public Meta
	{
        string m_name = "Directory";
        size_t m_size = sizeof(Directory);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Directory>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // FileBrowser
	template <>
	struct Reflection<FileBrowser> : public Meta
	{
        string m_name = "FileBrowser";
        size_t m_size = sizeof(FileBrowser);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<FileBrowser>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dockspace
	template <>
	struct Reflection<Dockspace> : public Meta
	{
        string m_name = "Dockspace";
        size_t m_size = sizeof(Dockspace);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dockspace>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // WindowHeader
	template <>
	struct Reflection<WindowHeader> : public Meta
	{
        string m_name = "WindowHeader";
        size_t m_size = sizeof(WindowHeader);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<WindowHeader>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // WindowFooter
	template <>
	struct Reflection<WindowFooter> : public Meta
	{
        string m_name = "WindowFooter";
        size_t m_size = sizeof(WindowFooter);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<WindowFooter>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Window
	template <>
	struct Reflection<Window> : public Meta
	{
        string m_name = "Window";
        size_t m_size = sizeof(Window);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Window>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dockbar
	template <>
	struct Reflection<Dockbar> : public Meta
	{
        string m_name = "Dockbar";
        size_t m_size = sizeof(Dockbar);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dockbar>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NodePlug
	template <>
	struct Reflection<NodePlug> : public Meta
	{
        string m_name = "NodePlug";
        size_t m_size = sizeof(NodePlug);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NodePlug>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NodeCable
	template <>
	struct Reflection<NodeCable> : public Meta
	{
        string m_name = "NodeCable";
        size_t m_size = sizeof(NodeCable);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NodeCable>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // NodeHeader
	template <>
	struct Reflection<NodeHeader> : public Meta
	{
        string m_name = "NodeHeader";
        size_t m_size = sizeof(NodeHeader);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<NodeHeader>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Node
	template <>
	struct Reflection<Node> : public Meta
	{
        string m_name = "Node";
        size_t m_size = sizeof(Node);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Node>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Menubar
	template <>
	struct Reflection<Menubar> : public Meta
	{
        string m_name = "Menubar";
        size_t m_size = sizeof(Menubar);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Menubar>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Tooldock
	template <>
	struct Reflection<Tooldock> : public Meta
	{
        string m_name = "Tooldock";
        size_t m_size = sizeof(Tooldock);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Tooldock>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Toolbar
	template <>
	struct Reflection<Toolbar> : public Meta
	{
        string m_name = "Toolbar";
        size_t m_size = sizeof(Toolbar);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Toolbar>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // MultiButton
	template <>
	struct Reflection<MultiButton> : public Meta
	{
        string m_name = "MultiButton";
        size_t m_size = sizeof(MultiButton);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<MultiButton>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // ScrollPlan
	template <>
	struct Reflection<ScrollPlan> : public Meta
	{
        string m_name = "ScrollPlan";
        size_t m_size = sizeof(ScrollPlan);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<ScrollSheet>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<ScrollPlan>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // SelectList
	template <>
	struct Reflection<SelectList> : public Meta
	{
        string m_name = "SelectList";
        size_t m_size = sizeof(SelectList);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<ScrollSheet>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<SelectList>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dropdown
	template <>
	struct Reflection<Dropdown> : public Meta
	{
        string m_name = "Dropdown";
        size_t m_size = sizeof(Dropdown);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dropdown>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // FilterInput
	template <>
	struct Reflection<FilterInput> : public Meta
	{
        string m_name = "FilterInput";
        size_t m_size = sizeof(FilterInput);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<TypeIn>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<FilterInput>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Textbox
	template <>
	struct Reflection<Textbox> : public Meta
	{
        string m_name = "Textbox";
        size_t m_size = sizeof(Textbox);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<TypeIn>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Textbox>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<unsigned int>
	template <>
	struct Reflection<Input<unsigned int>> : public Meta
	{
        string m_name = "Input<unsigned int>";
        size_t m_size = sizeof(Input<unsigned int>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<NumberInput<unsigned int>>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<unsigned int>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<int>
	template <>
	struct Reflection<Input<int>> : public Meta
	{
        string m_name = "Input<int>";
        size_t m_size = sizeof(Input<int>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<NumberInput<int>>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<int>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<float>
	template <>
	struct Reflection<Input<float>> : public Meta
	{
        string m_name = "Input<float>";
        size_t m_size = sizeof(Input<float>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<NumberInput<float>>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<float>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<double>
	template <>
	struct Reflection<Input<double>> : public Meta
	{
        string m_name = "Input<double>";
        size_t m_size = sizeof(Input<double>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<NumberInput<double>>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<double>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Input<string>
	template <>
	struct Reflection<Input<string>> : public Meta
	{
        string m_name = "Input<string>";
        size_t m_size = sizeof(Input<string>);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<TypeIn>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Input<string>>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // TreeNode
	template <>
	struct Reflection<TreeNode> : public Meta
	{
        string m_name = "TreeNode";
        size_t m_size = sizeof(TreeNode);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Expandbox>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<TreeNode>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Docksection
	template <>
	struct Reflection<Docksection> : public Meta
	{
        string m_name = "Docksection";
        size_t m_size = sizeof(Docksection);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Tabber>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Docksection>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dockline
	template <>
	struct Reflection<Dockline> : public Meta
	{
        string m_name = "Dockline";
        size_t m_size = sizeof(Dockline);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<GridSheet>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dockline>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dockbox
	template <>
	struct Reflection<Dockbox> : public Meta
	{
        string m_name = "Dockbox";
        size_t m_size = sizeof(Dockbox);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Window>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dockbox>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // DropdownInput
	template <>
	struct Reflection<DropdownInput> : public Meta
	{
        string m_name = "DropdownInput";
        size_t m_size = sizeof(DropdownInput);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Dropdown>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<DropdownInput>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Dir
	template <>
	struct Reflection<Dir> : public Meta
	{
        string m_name = "Dir";
        size_t m_size = sizeof(Dir);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<MultiButton>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Dir>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // File
	template <>
	struct Reflection<File> : public Meta
	{
        string m_name = "File";
        size_t m_size = sizeof(File);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<MultiButton>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<File>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // FileNode
	template <>
	struct Reflection<FileNode> : public Meta
	{
        string m_name = "FileNode";
        size_t m_size = sizeof(FileNode);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<TreeNode>(), &cls<Expandbox>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<FileNode>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // DirectoryNode
	template <>
	struct Reflection<DirectoryNode> : public Meta
	{
        string m_name = "DirectoryNode";
        size_t m_size = sizeof(DirectoryNode);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<TreeNode>(), &cls<Expandbox>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<DirectoryNode>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Canvas
	template <>
	struct Reflection<Canvas> : public Meta
	{
        string m_name = "Canvas";
        size_t m_size = sizeof(Canvas);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<ScrollPlan>(), &cls<ScrollSheet>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Canvas>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // Menu
	template <>
	struct Reflection<Menu> : public Meta
	{
        string m_name = "Menu";
        size_t m_size = sizeof(Menu);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<Dropdown>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<Menu>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // TypedownInput
	template <>
	struct Reflection<TypedownInput> : public Meta
	{
        string m_name = "TypedownInput";
        size_t m_size = sizeof(TypedownInput);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<DropdownInput>(), &cls<Dropdown>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<TypedownInput>()) { this->setup(*this); this->inherit(m_bases); }
    };
        
    
    // ToolButton
	template <>
	struct Reflection<ToolButton> : public Meta
	{
        string m_name = "ToolButton";
        size_t m_size = sizeof(ToolButton);
        TypeClass m_typeClass = OBJECT;
        std::vector<Type*> m_bases = { &cls<DropdownInput>(), &cls<Dropdown>(), &cls<WrapButton>(), &cls<Wedge>(), &cls<Widget>() };
        bool m_serializable = false;
        
        Reflection() : Meta(cls<ToolButton>()) { this->setup(*this); this->inherit(m_bases); }
    };
        

    
    template <> inline void from_string(const string& str, Dimension& val) { val = static_cast<Dimension>(rfl<Dimension>().enumValue(str)); };
    template <> inline void to_string(const Dimension& val, string& str) { str = rfl<Dimension>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Direction& val) { val = static_cast<Direction>(rfl<Direction>().enumValue(str)); };
    template <> inline void to_string(const Direction& val, string& str) { str = rfl<Direction>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Pivot& val) { val = static_cast<Pivot>(rfl<Pivot>().enumValue(str)); };
    template <> inline void to_string(const Pivot& val, string& str) { str = rfl<Pivot>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Align& val) { val = static_cast<Align>(rfl<Align>().enumValue(str)); };
    template <> inline void to_string(const Align& val, string& str) { str = rfl<Align>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, FrameType& val) { val = static_cast<FrameType>(rfl<FrameType>().enumValue(str)); };
    template <> inline void to_string(const FrameType& val, string& str) { str = rfl<FrameType>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, LayoutSolver& val) { val = static_cast<LayoutSolver>(rfl<LayoutSolver>().enumValue(str)); };
    template <> inline void to_string(const LayoutSolver& val, string& str) { str = rfl<LayoutSolver>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, AutoLayout& val) { val = static_cast<AutoLayout>(rfl<AutoLayout>().enumValue(str)); };
    template <> inline void to_string(const AutoLayout& val, string& str) { str = rfl<AutoLayout>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Flow& val) { val = static_cast<Flow>(rfl<Flow>().enumValue(str)); };
    template <> inline void to_string(const Flow& val, string& str) { str = rfl<Flow>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Sizing& val) { val = static_cast<Sizing>(rfl<Sizing>().enumValue(str)); };
    template <> inline void to_string(const Sizing& val, string& str) { str = rfl<Sizing>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, SpacePreset& val) { val = static_cast<SpacePreset>(rfl<SpacePreset>().enumValue(str)); };
    template <> inline void to_string(const SpacePreset& val, string& str) { str = rfl<SpacePreset>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Clipping& val) { val = static_cast<Clipping>(rfl<Clipping>().enumValue(str)); };
    template <> inline void to_string(const Clipping& val, string& str) { str = rfl<Clipping>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, Opacity& val) { val = static_cast<Opacity>(rfl<Opacity>().enumValue(str)); };
    template <> inline void to_string(const Opacity& val, string& str) { str = rfl<Opacity>().m_enumMap[val]; };
    
    template <> inline void from_string(const string& str, WidgetState& val) { val = static_cast<WidgetState>(rfl<WidgetState>().enumValue(str)); };
    template <> inline void to_string(const WidgetState& val, string& str) { str = rfl<WidgetState>().m_enumMap[val]; };
    
    
        
    template <> inline void from_string(const string& str, Dim<size_t>& val) { string_to_fixed_vector<Dim<size_t>, uint32_t>(str, val); };
    template <> inline void to_string(const Dim<size_t>& val, string& str) { fixed_vector_to_string<Dim<size_t>, 2>(val, str); };
        
    template <> inline void from_string(const string& str, Dim<AutoLayout>& val) { string_to_fixed_vector<Dim<AutoLayout>, AutoLayout>(str, val); };
    template <> inline void to_string(const Dim<AutoLayout>& val, string& str) { fixed_vector_to_string<Dim<AutoLayout>, 2>(val, str); };
        
    template <> inline void from_string(const string& str, Dim<Sizing>& val) { string_to_fixed_vector<Dim<Sizing>, Sizing>(str, val); };
    template <> inline void to_string(const Dim<Sizing>& val, string& str) { fixed_vector_to_string<Dim<Sizing>, 2>(val, str); };
        
    template <> inline void from_string(const string& str, Dim<Align>& val) { string_to_fixed_vector<Dim<Align>, Align>(str, val); };
    template <> inline void to_string(const Dim<Align>& val, string& str) { fixed_vector_to_string<Dim<Align>, 2>(val, str); };
        
    template <> inline void from_string(const string& str, Dim<Pivot>& val) { string_to_fixed_vector<Dim<Pivot>, Pivot>(str, val); };
    template <> inline void to_string(const Dim<Pivot>& val, string& str) { fixed_vector_to_string<Dim<Pivot>, 2>(val, str); };
        
    template <> inline void from_string(const string& str, DimFloat& val) { string_to_fixed_vector<DimFloat, float>(str, val); };
    template <> inline void to_string(const DimFloat& val, string& str) { fixed_vector_to_string<DimFloat, 2>(val, str); };
        
    template <> inline void from_string(const string& str, BoxFloat& val) { string_to_fixed_vector<BoxFloat, float>(str, val); };
    template <> inline void to_string(const BoxFloat& val, string& str) { fixed_vector_to_string<BoxFloat, 4>(val, str); };
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
#ifdef TOYUI_REFLECTION_IMPL
    void toyuiCarbon(Module& module)
    {   
        rfl<Dimension>();
        rfl<Direction>();
        rfl<Pivot>();
        rfl<Align>();
        rfl<FrameType>();
        rfl<LayoutSolver>();
        rfl<AutoLayout>();
        rfl<Flow>();
        rfl<Sizing>();
        rfl<Space>();
        rfl<SpacePreset>();
        rfl<Clipping>();
        rfl<Opacity>();
        rfl<Dim<size_t>>();
        rfl<Dim<AutoLayout>>();
        rfl<Dim<Sizing>>();
        rfl<Dim<Align>>();
        rfl<Dim<Pivot>>();
        rfl<DimFloat>();
        rfl<BoxFloat>();
        rfl<Image>();
        rfl<ImageSkin>();
        rfl<Shadow>();
        rfl<Paint>();
        rfl<Layout>();
        rfl<InkStyle>();
        rfl<Style>();
        rfl<Caption>();
        rfl<Frame>();
        rfl<Layer>();
        rfl<WidgetState>();
        rfl<Widget>();
        rfl<Wedge>();
        rfl<std::vector<Widget*>>();
        rfl<GridSheet>();
        rfl<Tooltip>();
        rfl<Rectangle>();
        rfl<Cursor>();
        rfl<RootSheet>();
        rfl<Label>();
        rfl<Button>();
        rfl<WrapButton>();
        rfl<MultiButton>();
        rfl<Toggle>();
        rfl<Slider>();
        rfl<Scrollbar>();
        rfl<Fillbar>();
        rfl<Checkbox>();
        rfl<ScrollSheet>();
        rfl<ScrollPlan>();
        rfl<SelectList>();
        rfl<Popup>();
        rfl<Dropdown>();
        rfl<DropdownInput>();
        rfl<TypeIn>();
        rfl<FilterInput>();
        rfl<TypedownInput>();
        rfl<RadioSwitch>();
        rfl<Textbox>();
        rfl<SliderInput<float>>();
        rfl<SliderInput<int>>();
        rfl<NumberInput<unsigned int>>();
        rfl<NumberInput<int>>();
        rfl<NumberInput<float>>();
        rfl<NumberInput<double>>();
        rfl<Input<unsigned int>>();
        rfl<Input<int>>();
        rfl<Input<float>>();
        rfl<Input<double>>();
        rfl<Input<bool>>();
        rfl<Input<string>>();
        rfl<Input<Colour>>();
        rfl<Expandbox>();
        rfl<TreeNode>();
        rfl<Tree>();
        rfl<Table>();
        rfl<Tab>();
        rfl<Tabber>();
        rfl<Dir>();
        rfl<File>();
        rfl<Directory>();
        rfl<FileBrowser>();
        rfl<FileNode>();
        rfl<DirectoryNode>();
        rfl<Docksection>();
        rfl<Dockline>();
        rfl<Dockspace>();
        rfl<WindowHeader>();
        rfl<WindowSizer>();
        rfl<WindowFooter>();
        rfl<Window>();
        rfl<Dockbox>();
        rfl<Dockbar>();
        rfl<NodeKnob>();
        rfl<NodePlug>();
        rfl<NodeCable>();
        rfl<NodeHeader>();
        rfl<Node>();
        rfl<Canvas>();
        rfl<Menu>();
        rfl<Menubar>();
        rfl<ToolButton>();
        rfl<Tooldock>();
        rfl<Toolbar>();
        rfl<RenderTarget>();
        rfl<UiWindow>();
        rfl<Styler>();
    
        module.m_types.push_back(&cls<Dimension>());
        module.m_types.push_back(&cls<Direction>());
        module.m_types.push_back(&cls<Pivot>());
        module.m_types.push_back(&cls<Align>());
        module.m_types.push_back(&cls<FrameType>());
        module.m_types.push_back(&cls<LayoutSolver>());
        module.m_types.push_back(&cls<AutoLayout>());
        module.m_types.push_back(&cls<Flow>());
        module.m_types.push_back(&cls<Sizing>());
        module.m_types.push_back(&cls<Space>());
        module.m_types.push_back(&cls<SpacePreset>());
        module.m_types.push_back(&cls<Clipping>());
        module.m_types.push_back(&cls<Opacity>());
        module.m_types.push_back(&cls<Dim<size_t>>());
        module.m_types.push_back(&cls<Dim<AutoLayout>>());
        module.m_types.push_back(&cls<Dim<Sizing>>());
        module.m_types.push_back(&cls<Dim<Align>>());
        module.m_types.push_back(&cls<Dim<Pivot>>());
        module.m_types.push_back(&cls<DimFloat>());
        module.m_types.push_back(&cls<BoxFloat>());
        module.m_types.push_back(&cls<Image>());
        module.m_types.push_back(&cls<ImageSkin>());
        module.m_types.push_back(&cls<Shadow>());
        module.m_types.push_back(&cls<Paint>());
        module.m_types.push_back(&cls<Layout>());
        module.m_types.push_back(&cls<InkStyle>());
        module.m_types.push_back(&cls<Style>());
        module.m_types.push_back(&cls<Caption>());
        module.m_types.push_back(&cls<Frame>());
        module.m_types.push_back(&cls<Layer>());
        module.m_types.push_back(&cls<WidgetState>());
        module.m_types.push_back(&cls<Widget>());
        module.m_types.push_back(&cls<Wedge>());
        module.m_types.push_back(&cls<std::vector<Widget*>>());
        module.m_types.push_back(&cls<GridSheet>());
        module.m_types.push_back(&cls<Tooltip>());
        module.m_types.push_back(&cls<Rectangle>());
        module.m_types.push_back(&cls<Cursor>());
        module.m_types.push_back(&cls<RootSheet>());
        module.m_types.push_back(&cls<Label>());
        module.m_types.push_back(&cls<Button>());
        module.m_types.push_back(&cls<WrapButton>());
        module.m_types.push_back(&cls<MultiButton>());
        module.m_types.push_back(&cls<Toggle>());
        module.m_types.push_back(&cls<Slider>());
        module.m_types.push_back(&cls<Scrollbar>());
        module.m_types.push_back(&cls<Fillbar>());
        module.m_types.push_back(&cls<Checkbox>());
        module.m_types.push_back(&cls<ScrollSheet>());
        module.m_types.push_back(&cls<ScrollPlan>());
        module.m_types.push_back(&cls<SelectList>());
        module.m_types.push_back(&cls<Popup>());
        module.m_types.push_back(&cls<Dropdown>());
        module.m_types.push_back(&cls<DropdownInput>());
        module.m_types.push_back(&cls<TypeIn>());
        module.m_types.push_back(&cls<FilterInput>());
        module.m_types.push_back(&cls<TypedownInput>());
        module.m_types.push_back(&cls<RadioSwitch>());
        module.m_types.push_back(&cls<Textbox>());
        module.m_types.push_back(&cls<SliderInput<float>>());
        module.m_types.push_back(&cls<SliderInput<int>>());
        module.m_types.push_back(&cls<NumberInput<unsigned int>>());
        module.m_types.push_back(&cls<NumberInput<int>>());
        module.m_types.push_back(&cls<NumberInput<float>>());
        module.m_types.push_back(&cls<NumberInput<double>>());
        module.m_types.push_back(&cls<Input<unsigned int>>());
        module.m_types.push_back(&cls<Input<int>>());
        module.m_types.push_back(&cls<Input<float>>());
        module.m_types.push_back(&cls<Input<double>>());
        module.m_types.push_back(&cls<Input<bool>>());
        module.m_types.push_back(&cls<Input<string>>());
        module.m_types.push_back(&cls<Input<Colour>>());
        module.m_types.push_back(&cls<Expandbox>());
        module.m_types.push_back(&cls<TreeNode>());
        module.m_types.push_back(&cls<Tree>());
        module.m_types.push_back(&cls<Table>());
        module.m_types.push_back(&cls<Tab>());
        module.m_types.push_back(&cls<Tabber>());
        module.m_types.push_back(&cls<Dir>());
        module.m_types.push_back(&cls<File>());
        module.m_types.push_back(&cls<Directory>());
        module.m_types.push_back(&cls<FileBrowser>());
        module.m_types.push_back(&cls<FileNode>());
        module.m_types.push_back(&cls<DirectoryNode>());
        module.m_types.push_back(&cls<Docksection>());
        module.m_types.push_back(&cls<Dockline>());
        module.m_types.push_back(&cls<Dockspace>());
        module.m_types.push_back(&cls<WindowHeader>());
        module.m_types.push_back(&cls<WindowSizer>());
        module.m_types.push_back(&cls<WindowFooter>());
        module.m_types.push_back(&cls<Window>());
        module.m_types.push_back(&cls<Dockbox>());
        module.m_types.push_back(&cls<Dockbar>());
        module.m_types.push_back(&cls<NodeKnob>());
        module.m_types.push_back(&cls<NodePlug>());
        module.m_types.push_back(&cls<NodeCable>());
        module.m_types.push_back(&cls<NodeHeader>());
        module.m_types.push_back(&cls<Node>());
        module.m_types.push_back(&cls<Canvas>());
        module.m_types.push_back(&cls<Menu>());
        module.m_types.push_back(&cls<Menubar>());
        module.m_types.push_back(&cls<ToolButton>());
        module.m_types.push_back(&cls<Tooldock>());
        module.m_types.push_back(&cls<Toolbar>());
        module.m_types.push_back(&cls<RenderTarget>());
        module.m_types.push_back(&cls<UiWindow>());
        module.m_types.push_back(&cls<Styler>());
    
    }
#endif

}

#endif // TOYUI_S_H
