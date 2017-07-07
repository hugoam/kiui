//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UIFORWARD_H
#define TOY_UIFORWARD_H

/* toy */
#include <toyobj/Forward.h>

struct NVGcontext;
struct NVGdisplayList;
struct GLFWwindow;

namespace toy
{
	//enum MouseButton;
	//enum KeyCode;

	enum Direction : unsigned int;
	enum Pivot : unsigned int;
	enum Align : unsigned int;
	enum AutoLayout : unsigned int;
	enum SpacePreset : unsigned int;
	enum Clipping : unsigned int;
	enum Dimension : unsigned int;
	enum FrameType : unsigned int;
	enum LayoutType : unsigned int;
	enum Sizing : unsigned int;
	enum Flow : unsigned int;
	enum BoxLayer : unsigned int;
	enum Opacity : unsigned int;
	enum LayoutSolver : unsigned int;

	struct Space;

	enum InputModifier : unsigned int;

	class BoxFloat;

	class User;

	class InputDevice;
	class Keyboard;
	class Mouse;
	class MouseButton;

	struct InputEvent;
	struct MouseEvent;
	struct KeyEvent;

	class ControlNode;

	class InputReceiver;
	class InputAdapter;

	class Controller;

	class Style;

	class Content;
	class Caption;
	class Icon;

	class Shadow;
	class ImageSkin;
	class Paint;
	class InkStyle;

	class FrameSolver;
	class RowSolver;
	class GridSolver;

	class UiRect;
	class Frame;
	class Layer;

	class LayoutStyle;

	enum WidgetState : unsigned int;

	class WidgetStore;

	class Widget;
	class Wedge;
	class RootSheet;
	class Cursor;

	class Tooltip;

	class Label;
	class Title;
	class DynamicImage;
	class Button;
	class WrapButton;
	class Toggle;
	class TypeIn;
	class FilterInput;

	class Board;

	class Slider;
	class SliderKnob;
	class Scroller;
	class Scrollbar;

	class ScrollZone;
	class ScrollSheet;
	class ScrollPlan;

	template <class T>
	class StatSlider;

	class Dropper;

	class Tabber;
	class Dropdown;
	class Expandbox;
	class RadioSwitch;

	class List;
	class Table;
	class Tree;
	class TreeNode;

	class Window;

	class Node;
	class NodeCable;
	class Canvas;

	class Dropdown;
	class DropdownInput;
	class TypedownInput;
	class DropdownList;

	class Menu;
	class MenuList;

	class Docksection;
	class Dockline;
	class Dockspace;

	class Dockbox;
	class Dockbar;

	class Directory;
	class Dir;
	class File;

	class Image;
	class ImageAtlas;

	class Renderer;
	class RenderTarget;

	class Skinner;
	class Styler;

	class RenderWindow;
	class InputWindow;
	class Context;
	class RenderSystem;

	class UiWindow;

	class Device;
	class RootDevice;

	// Renderer
	class NanoRenderer;
	class GlRenderer;
	
	// Contexts
	class GlfwRenderWindow;
	class GlfwInputWindow;
	class GlfwContext;
	class GlfwRenderSystem;

	class OgreRenderWindow;
	class OISInputWindow;
	class OgreContext;
	class OgreRenderSystem;
}

#endif // TOY_UIFORWARD_H
