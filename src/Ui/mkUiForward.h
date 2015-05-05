//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UIFORWARD_H_INCLUDED
#define MK_UIFORWARD_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>

struct NVGcontext;
struct NVGdisplayList;
struct GLFWwindow;

namespace mk
{
	//enum MouseButton;
	//enum KeyCode;

	enum Dimension : unsigned int;
	enum FrameType : unsigned int;
	enum Sizing : unsigned int;
	enum Flow : unsigned int;
	enum BoxLayer : unsigned int;
	enum Opacity : unsigned int;

	class User;

	class InputDispatcher;
	class InputReceiver;
	class InputPropagator;
	class InputWidget;

	class Style;

	class Form;
	class RootForm;

	class Button;
	class Label;
	class Image;
	class DynamicImage;

	class Dropper;

	class Tooltip;
	class Bar;

	class Collection;
	class Scheme;

	class Tabber;
	class Dropdown;
	class Expandbox;
	class RadioSwitch;

	class List;
	class Table;
	class Tree;
	class TreeNode;

	class Window;
	class Dockspace;

	class Inkbox;
	class InkStyle;
	class InkStyle;
	class InkTarget;
	class InkLayer;
	class InkWindow;

	class Uibox;
	class Frame;
	class Stripe;
	class Layer;
	class LayoutStyle;

	enum WidgetState : unsigned int;

	class Widget;
	class Sheet;
	class RootSheet;

	class Label;
	class Title;
	class Icon;
	class Button;
	class WrapButton;
	class Toggle;
	class Slider;
	class SliderKnob;
	class Scroller;
	class Scrollbar;
	class ScrollArea;

	template <class T>
	class StatSlider;

	class Dropdown;
	class DropdownList;

	class Menu;
	class MenuList;

	class Expandbox;

	class Tabber;
	class Window;

	class Docksection;
	class Dockline;
	class Dockspace;

	class Dockbox;
	class Dockbar;

	class Cursor;

	class Skinner;
	class Styler;
	class UiWindow;
	
	class FMethod;
	class FMethodBind;
	class FMethodCall;

	class WValue;

	class Hook;

	class NanoInk;
	class NanoLayer;
	class NanoTarget;
	class NanoGl;
	class NanoWindow;

	class GlWindow;

	class Controller;
}

#endif // MK_UIFORWARD_H_INCLUDED
