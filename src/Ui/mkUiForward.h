//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UIFORWARD_H_INCLUDED
#define MK_UIFORWARD_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>

struct NVGcontext;
struct GLFWwindow;

namespace mk
{
	//enum MouseButton;
	//enum KeyCode;

	enum Dimension : unsigned int;
	enum FrameType : unsigned int;
	enum Sizing : unsigned int;
	enum Flow : unsigned int;
	enum Overflow : unsigned int;
	enum BoxLayer : unsigned int;
	enum Opacity : unsigned int;

	class User;

	class InputDispatcher;
	class InputReceiver;
	class InputPropagator;
	class InputWidget;

	class Form;
	class RootForm;

	class Button;
	class Label;
	class Image;
	class DynamicImage;

	class WDynamicImage;

	class Dropper;

	class Tooltip;
	class Bar;

	class Collection;
	class Scheme;

	class List;
	class Tabber;
	class Dropdown;
	class Expandbox;
	class RadioSwitch;

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
	class LayoutStyle;

	enum WidgetState : unsigned short;

	class Widget;
	class Sheet;
	class RootSheet;

	class WLabel;
	class WButton;
	class WWrapButton;
	class WToggle;
	class WSlider;
	class WSlideButton;
	class WScroller;
	class WScrollbar;

	class WDropdown;
	class WDropdownBox;

	class WExpandbox;

	class WTabber;
	class WWindow;

	class WDocksection;
	class WDockline;
	class WDockspace;

	class Cursor;

	class UiInker;
	class UiSkinner;
	class UiLayout;
	class UiWindow;
	
	class FMethod;
	class FMethodBind;
	class FMethodCall;

	class FValue;
	class FBool;
	class FInt;
	class FFloat;
	class FIntStat;
	class FFloatStat;
	class FString;

	class Hook;
	class FObjectEdit;
	class FStem;
	class FMember;
	class FPartEdit;
	class FStore;

	class NanoInk;
	class NanoLayer;
	class NanoTarget;
	class NanoGl;
	class NanoWindow;

	class GlWindow;

	class Controller;
}

#endif // MK_UIFORWARD_H_INCLUDED
