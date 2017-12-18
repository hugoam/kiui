#ifndef TOYUI_TYPES_GEN_H
#define TOYUI_TYPES_GEN_H

#include <toyui/Config.h>
#include <toyui/Forward.h>

#include <toyobj/Type.h>

namespace toy
{   
    // Exported types
    template <> TOY_UI_EXPORT Type& cls<Dimension>();
    template <> TOY_UI_EXPORT Type& cls<Direction>();
    template <> TOY_UI_EXPORT Type& cls<Pivot>();
    template <> TOY_UI_EXPORT Type& cls<Align>();
    template <> TOY_UI_EXPORT Type& cls<FrameType>();
    template <> TOY_UI_EXPORT Type& cls<LayoutSolver>();
    template <> TOY_UI_EXPORT Type& cls<AutoLayout>();
    template <> TOY_UI_EXPORT Type& cls<Flow>();
    template <> TOY_UI_EXPORT Type& cls<Sizing>();
    template <> TOY_UI_EXPORT Type& cls<SpacePreset>();
    template <> TOY_UI_EXPORT Type& cls<Clipping>();
    template <> TOY_UI_EXPORT Type& cls<Opacity>();
    template <> TOY_UI_EXPORT Type& cls<WidgetState>();
    template <> TOY_UI_EXPORT Type& cls<std::vector<Widget*>>();
    
    template <> TOY_UI_EXPORT Type& cls<Space>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Space>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Space>>();
    template <> TOY_UI_EXPORT Type& cls<Dim<size_t>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<size_t>>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<size_t>>>();
    template <> TOY_UI_EXPORT Type& cls<Dim<AutoLayout>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<AutoLayout>>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<AutoLayout>>>();
    template <> TOY_UI_EXPORT Type& cls<Dim<Sizing>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Sizing>>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Sizing>>>();
    template <> TOY_UI_EXPORT Type& cls<Dim<Align>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Align>>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Align>>>();
    template <> TOY_UI_EXPORT Type& cls<Dim<Pivot>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Dim<Pivot>>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Dim<Pivot>>>();
    template <> TOY_UI_EXPORT Type& cls<DimFloat>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<DimFloat>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<DimFloat>>();
    template <> TOY_UI_EXPORT Type& cls<BoxFloat>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<BoxFloat>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<BoxFloat>>();
    template <> TOY_UI_EXPORT Type& cls<Image>();
    template <> TOY_UI_EXPORT Type& cls<ImageSkin>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<ImageSkin>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<ImageSkin>>();
    template <> TOY_UI_EXPORT Type& cls<Shadow>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Shadow>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Shadow>>();
    template <> TOY_UI_EXPORT Type& cls<Paint>();
    template <> TOY_UI_EXPORT Type& cls<Layout>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Layout>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Layout>>();
    template <> TOY_UI_EXPORT Type& cls<InkStyle>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<InkStyle>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<InkStyle>>();
    template <> TOY_UI_EXPORT Type& cls<Style>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Style>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Style>>();
    template <> TOY_UI_EXPORT Type& cls<Caption>();
    template <> TOY_UI_EXPORT Type& cls<Frame>();
    template <> TOY_UI_EXPORT Type& cls<Widget>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Widget>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Widget>>();
    template <> TOY_UI_EXPORT Type& cls<RenderTarget>();
    template <> TOY_UI_EXPORT Type& cls<RenderSystem>();
    template <> TOY_UI_EXPORT Type& cls<Context>();
    template <> TOY_UI_EXPORT Type& cls<UiWindow>();
    template <> TOY_UI_EXPORT Type& cls<Styler>();
    template <> TOY_UI_EXPORT Type& cls<Layer>();
    template <> TOY_UI_EXPORT Type& cls<Wedge>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Wedge>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Wedge>>();
    template <> TOY_UI_EXPORT Type& cls<Label>();
    template <> TOY_UI_EXPORT Type& cls<Button>();
    template <> TOY_UI_EXPORT Type& cls<Toggle>();
    template <> TOY_UI_EXPORT Type& cls<WindowSizer>();
    template <> TOY_UI_EXPORT Type& cls<NodeKnob>();
    template <> TOY_UI_EXPORT Type& cls<GridSheet>();
    template <> TOY_UI_EXPORT Type& cls<Tooltip>();
    template <> TOY_UI_EXPORT Type& cls<Rectangle>();
    template <> TOY_UI_EXPORT Type& cls<Cursor>();
    template <> TOY_UI_EXPORT Type& cls<RootSheet>();
    template <> TOY_UI_EXPORT Type& cls<WrapButton>();
    template <> TOY_UI_EXPORT Type& cls<Slider>();
    template <> TOY_UI_EXPORT Type& cls<Scrollbar>();
    template <> TOY_UI_EXPORT Type& cls<Checkbox>();
    template <> TOY_UI_EXPORT Type& cls<ScrollSheet>();
    template <> TOY_UI_EXPORT Type& cls<Popup>();
    template <> TOY_UI_EXPORT Type& cls<TypeIn>();
    template <> TOY_UI_EXPORT Type& cls<RadioSwitch>();
    template <> TOY_UI_EXPORT Type& cls<Input<bool>>();
    template <> TOY_UI_EXPORT Type& cls<Input<Colour>>();
    template <> TOY_UI_EXPORT Type& cls<Expandbox>();
    template <> TOY_UI_EXPORT Type& cls<Tree>();
    template <> TOY_UI_EXPORT Type& cls<Table>();
    template <> TOY_UI_EXPORT Type& cls<Tab>();
    template <> TOY_UI_EXPORT Type& cls<Tabber>();
    template <> TOY_UI_EXPORT Type& cls<Directory>();
    template <> TOY_UI_EXPORT Type& cls<FileBrowser>();
    template <> TOY_UI_EXPORT Type& cls<Dockspace>();
    template <> TOY_UI_EXPORT Type& cls<WindowHeader>();
    template <> TOY_UI_EXPORT Type& cls<WindowFooter>();
    template <> TOY_UI_EXPORT Type& cls<Window>();
    template <> TOY_UI_EXPORT Type& cls<Docker>();
    template <> TOY_UI_EXPORT Type& cls<Dockbar>();
    template <> TOY_UI_EXPORT Type& cls<NodePlug>();
    template <> TOY_UI_EXPORT Type& cls<NodeCable>();
    template <> TOY_UI_EXPORT Type& cls<NodeHeader>();
    template <> TOY_UI_EXPORT Type& cls<Node>();
    template <> TOY_UI_EXPORT Type& cls<Menubar>();
    template <> TOY_UI_EXPORT Type& cls<Tooldock>();
    template <> TOY_UI_EXPORT Type& cls<Toolbar>();
    template <> TOY_UI_EXPORT Type& cls<MultiButton>();
    template <> TOY_UI_EXPORT Type& cls<ScrollPlan>();
    template <> TOY_UI_EXPORT Type& cls<SelectList>();
    template <> TOY_UI_EXPORT Type& cls<Dropdown>();
    template <> TOY_UI_EXPORT Type& cls<Textbox>();
    template <> TOY_UI_EXPORT Type& cls<Input<string>>();
    template <> TOY_UI_EXPORT Type& cls<TreeNode>();
    template <> TOY_UI_EXPORT Type& cls<Docksection>();
    template <> TOY_UI_EXPORT Type& cls<Dockline>();
    template <> TOY_UI_EXPORT Type& cls<Dockbox>();
    template <> TOY_UI_EXPORT Type& cls<DropdownInput>();
    template <> TOY_UI_EXPORT Type& cls<Dir>();
    template <> TOY_UI_EXPORT Type& cls<File>();
    template <> TOY_UI_EXPORT Type& cls<FileNode>();
    template <> TOY_UI_EXPORT Type& cls<DirectoryNode>();
    template <> TOY_UI_EXPORT Type& cls<Canvas>();
    template <> TOY_UI_EXPORT Type& cls<Menu>();
    template <> TOY_UI_EXPORT Type& cls<ToolButton>();
}

#endif // TOYUI_TYPES_GEN_H
