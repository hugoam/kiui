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

	enum Dimension : unsigned int;
	enum FrameType : unsigned int;
	enum Sizing : unsigned int;
	enum Flow : unsigned int;
	enum BoxLayer : unsigned int;
	enum Opacity : unsigned int;

	class BoxFloat;
	class DimFloat;

	class User;

	class InputDevice;
	class Keyboard;
	class Mouse;
	class MouseButton;

	struct InputEvent;
	struct MouseEvent;
	struct KeyEvent;

	class InputReceiver;
	class InputFrame;
	class InputWidget;

	class Controller;

	class Style;

	class DrawFrame;
	class Stencil;
	class Caption;

	class Shadow;
	class ImageSkin;
	class InkStyle;

	class Uibox;
	class Frame;
	class Stripe;
	class Layer;
	class MasterLayer;
	class LayoutStyle;

	enum WidgetState : unsigned int;

	class Widget;
	class Sheet;
	class RootSheet;
	class Cursor;

	class Tooltip;

	class Label;
	class Title;
	class Icon;
	class DynamicImage;
	class Button;
	class WrapButton;
	class Toggle;

	class Bar;
	class Band;
	class Board;

	class Slider;
	class SliderKnob;
	class Scroller;
	class Scrollbar;
	class ScrollArea;

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
	class DropdownList;

	class Menu;
	class MenuList;

	class Docksection;
	class Dockline;
	class Dockspace;

	class Dockbox;
	class Dockbar;

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

	class WValue;

	class Device;
	class DeviceType;
	class Response;
	class Hook;
	class RootDevice;
	class DeviceMapper;
	class DeviceMapping;

	class Stack;
	class SelectStack;
	class PickStack;

	// Renderer
	class NanoContext;
	class NanoRenderer;

	class GlRenderer;
	class GlWindow;

	// Edit Devices
	class DProcessInput;
	class DProcessOutput;
	class DProcess;
	class DScriptCanvas;
	class DScriptEditor;

	class DMethod;
	class DMethodBind;
	class DMethodCall;

	class DValue;
	class DSequence;
	class DLink;
	class DEnum;

	class DStructure;

	class DObjectEdit;
	class DMemberEdit;
	class DModularEdit;
	class DEdit;

	class DRootObjectCreate;
	class DObjectCreate;
}

#endif // TOY_UIFORWARD_H
