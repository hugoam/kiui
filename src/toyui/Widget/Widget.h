//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WIDGET_H
#define TOY_WIDGET_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyobj/Reflect/Member.h>
#include <toyui/Types.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Style/Style.h>

#include <functional>
#include <memory>

namespace toy
{
	enum _refl_ WidgetState : unsigned int
	{
		NOSTATE   = 0,			// default state
		FOCUSED   = 1 << 0,		// under input device focus
		TRIGGERED = 1 << 1,		// triggered by input device (e.g. pressed)
		ACTIVATED = 1 << 2,		// activated state
		SELECTED  = 1 << 3,		// selected state
		DRAGGED   = 1 << 4,		// dragged by input device
		DISABLED  = 1 << 5,		// disabled state
		ACTIVE    = 1 << 6,		// for the unique currently active widget
		CONTROL   = 1 << 7,		// widget is in the control stack
		MODAL     = 1 << 8		// widget is modal in the control stack
	};

#ifdef TOY_WIDGET_STATES_CONVERT_IMPL
	template <> inline void from_string(const string& str, WidgetStates& val)
	{
		std::vector<string> names = splitString(toUpper(str), "|");
		for(const string& name : names)
			val.value |= from_string<WidgetState>(name);
	};

	template <> inline void to_string(const WidgetStates& val, string& str)
	{
		for(WidgetState state = FOCUSED; state < (1 << 9); state = static_cast<WidgetState>(state << 1))
			if(val.value & state)
				str += (str.empty() ? "" : "|") + to_string<WidgetState>(state);
	};
#endif

	class _refl_ TOY_UI_EXPORT Widget : public TypeObject, public InputAdapter
	{
	public:
		struct Params
		{
			Params(Wedge* parent = nullptr, Style* style = nullptr, FrameType frameType = FRAME)
				: m_parent(parent), m_type(nullptr), m_style(style), m_frameType(frameType) {}
			Params(const Params& params, Type* type = nullptr, Style* style = nullptr)
				: m_parent(params.m_parent), m_type(params.m_type ? params.m_type : type), m_style(params.m_style ? params.m_style : style), m_frameType(params.m_frameType) {}
			Params(const Params& params, Type* type, FrameType frameType)
				: m_parent(params.m_parent), m_type(params.m_type ? params.m_type : type), m_style(params.m_style), m_frameType(frameType) {}
			Wedge* m_parent = nullptr;
			Type* m_type = nullptr;
			Style* m_style = nullptr;
			FrameType m_frameType = FRAME;
		};

	public:
		Widget(const Params& params = {});
		Widget(const Params& params, const string& content);
		~Widget();

		inline Frame& frame() { return *m_frame; }

		void setContent(const string& content);

		virtual const string& tooltip() { static string str; return str; }
		virtual const string& label();

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();
		ControlSwitch& rootController();

		void show();
		void hide();

		virtual void destroyed() {}

		void bind(Wedge& parent, size_t index);
		void unbind();

		virtual void makeSolver();

		void destroyTree();
		void destroySelf();
		void destroy();

		virtual void extract() { this->destroy(); }

		template <class T>
		T* findContainer() { Widget* widget = this->findContainer(cls<T>()); return widget ? &as<T>(*widget) : nullptr; }

		Widget* findContainer(Type& type);

		using Visitor = std::function<void(Widget&, bool& visit)>;
		virtual void visit(const Visitor& visitor);

		void updateStyle();

		void setStyle(Style& style, bool hard = true);
		void setStyle(Style* style) { this->setStyle(*style); }

		void toggleState(WidgetState state);

		void enableState(WidgetState state);
		void disableState(WidgetState state);

		void control(bool modal);
		void uncontrol(bool modal);

		virtual void active() {}
		virtual void inactive() {}

		Widget* pinpoint(DimFloat pos);
		Widget* pinpoint(DimFloat pos, const Frame::Filter& filter);

		virtual void dirtyLayout();

		virtual bool customDraw(Renderer& renderer) { UNUSED(renderer); return false; }

		void transformEvent(InputEvent& inputEvent);
		virtual InputReceiver* controlEvent(InputEvent& inputEvent);
		virtual InputReceiver* receiveEvent(InputEvent& inputEvent);

		void makeActive();

		void giveControl(InputReceiver& receiver, ControlMode mode, DeviceType device = DEVICE_ALL);
		void takeControl(ControlMode mode, DeviceType device = DEVICE_ALL);
		void yieldControl();

		virtual bool mouseEntered(MouseEvent& mouseEvent);
		virtual bool mouseLeaved(MouseEvent& mouseEvent);

		virtual bool mousePressed(MouseEvent& mouseEvent);
		virtual bool mouseReleased(MouseEvent& mouseEvent);

		using Callback = std::function<void(Widget&)>;

	public:
		_attr_ Wedge* m_parent;
		_attr_ Wedge* m_container;
		_attr_ size_t m_index;
		_attr_ _mut_ Style* m_style;
		/*_attr_*/ object_ptr<Frame> m_frame; // @todo make this a member, separate Layer, and separate caption and image (only for Items)
		_attr_ WidgetState m_state;

		Ref m_object;

		static Styles& styles() { static Styles styles; return styles; }
		static std::map<string, Style*> s_styles;
	};
}

#endif // TOY_WIDGET_H
