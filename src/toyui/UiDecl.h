//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UI_DECL_H
#define TOY_UI_DECL_H

/* toy */
#include <toyui/Types.h>
#include <toyobj/Graph/Node.h>
#include <toyui/Bundle.h>


namespace toy
{
	using Callback = std::function<void()>;

	struct TOY_UI_EXPORT Binding
	{
		Binding() {}
		Binding(Wedge& wedge) : widget(&wedge), body(&wedge) {}
		Binding(Widget& widget) : widget(&widget) {}
		Binding(Wedge& wedge, Wedge& body) : widget(&wedge), body(&body) {}
		Binding(Wedge* body) : body(body) {}

		Widget* widget = nullptr;
		Wedge* body = nullptr;
	};
	
	inline Binding label(Wedge& parent, const string& name, Style* style = nullptr)
	{
		return { parent.emplace_style<Label>(*style, name) };
	}

	inline Binding button(Wedge& parent, const string& name, Button::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace_style<Button>(*style, name, callback) };
	}

	inline Binding multibutton(Wedge& parent, const StringVector& elements, MultiButton::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace_style<MultiButton>(*style, elements, callback) };
	}

	inline Binding radioswitch(Wedge& parent, const StringVector& elements, RadioSwitch::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace_style<RadioSwitch>(*style, elements, callback) };
	}

	inline Binding dropdown(Wedge& parent, const StringVector& elements, DropdownInput::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace_style<DropdownInput>(*style, elements, callback) };
	}

	inline Binding wedge(Wedge& parent, Style* style = nullptr)
	{
		UNUSED(style);
		return { parent.emplace_style<Wedge>(Widget::styles().wedge) };
	}

	inline Binding sheet(Wedge& parent)
	{
		return { parent.emplace_style<Wedge>(Widget::styles().sheet) };
	}

	inline Binding layout(Wedge& parent)
	{
		return { parent.emplace_style<Wedge>(Widget::styles().layout) };
	}

	inline Binding layout_span(Wedge& parent, float span)
	{
		Wedge& layout = parent.emplace_style<Wedge>(Widget::styles().layout);
		layout.frame().setSpanDim(DIM_X, span);
		return { layout };
	}

	inline Binding board(Wedge& parent)
	{
		return{ parent.emplace_style<Wedge>(Widget::styles().board) };
	}

	inline Binding stack(Wedge& parent)
	{
		return { parent.emplace_style<Wedge>(Widget::styles().stack) };
	}

	inline Binding list(Wedge& parent)
	{
		return { parent.emplace_style<Wedge>(Widget::styles().list) };
	}

	inline Binding row(Wedge& parent)
	{
		return { parent.emplace_style<Wedge>(Widget::styles().row) };
	}

	inline Binding scrollsheet(Wedge& parent, Style* style = nullptr)
	{
		ScrollSheet& scrollsheet = parent.emplace_style<ScrollSheet>(*style);
		return { scrollsheet, scrollsheet.m_body};
	}

	inline Binding select_list(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace_style<SelectList>(*style) };
	}

	inline Binding expandbox(Wedge& parent, const StringVector& elements, Style* style = nullptr)
	{
		Expandbox& expandbox = parent.emplace_style<Expandbox>(*style, elements);
		return { expandbox, expandbox.m_body };
	}

	inline Binding table(Wedge& parent, const StringVector& elements, const std::vector<float>& spans, Style* style = nullptr)
	{
		Table& table = parent.emplace_style<Table>(*style, elements, spans);
		return{ table, table };
	}

	inline Binding toolbar(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace_style<Toolbar>(*style) };
	}

	inline Binding tooldock(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace_style<Tooldock>(*style) };
	}

	inline Binding menu(Wedge& parent, const string& name, Style* style = nullptr)
	{
		return { parent.emplace_style<Menu>(*style, name) };
	}

	inline Binding menubar(Wedge& parent, Style* style = nullptr)
	{
		return{ parent.emplace_style<Menubar>(*style) };
	}

	inline Binding tabber(Wedge& parent, Style* style = nullptr)
	{
		Tabber& tabber = parent.emplace_style<Tabber>(*style);
		return { tabber };
	}

	inline Binding window(Wedge& parent, const string& name, Style* style = nullptr)
	{
		Window& window = parent.emplace_style<Window>(*style, name);
		return { window, window.m_body };
	}

	inline Binding popup(Wedge& parent, const Callback& onClose, Style* style = nullptr)
	{
		return { parent.emplace_style<Popup>(*style, [&](Widget&) { onClose(); }) };
	}

	inline Binding dockspace(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace_style<Dockspace>(*style) };
	}

	inline Binding canvas(Wedge& parent, const string& name, Widget::Callback callback, Style* style = nullptr)
	{
		Canvas& canvas = parent.emplace_style<Canvas>(*style, name, callback);
		return { canvas, canvas.m_body };
	}

	inline Binding node(Wedge& parent, const string& name, int order, Style* style = nullptr)
	{
		return { parent.emplace_style<Node>(*style, name, order) };
	}


	using QueryFunc = std::function<void(UiNode&, const std::function<void(Var)>&)>;

	template <class T_Value>
	using TQueryFunc = std::function<void(UiNode&, const std::function<void(T_Value)>&)>;

	struct Query
	{
		Query(QueryFunc decl) : m_decl(decl) {}
		bool m_done = false;
		QueryFunc m_decl = nullptr;
		Var m_result = {};
	};

	struct Modal
	{
		Modal() : m_current_step(0) {}

		template <class... T_Args>
		void init(const TQueryFunc<T_Args>&... funcs, const std::function<void(T_Args...)>& callback)
		{
			m_callback = polymer_func(callback);
			swallow{ (query(funcs), 1)... };
		}

		template <class T_Value>
		void query(const TQueryFunc<T_Value>& decl)
		{
			m_queries.emplace_back([decl](UiNode& node, const std::function<void(Var)>& callback)
			{
				decl(node, typed_func<T_Value>(callback));
			});
		}

		void decl(UiNode& node);
		void done();

		std::vector<Query> m_queries;
		size_t m_current_step;
		std::function<void(VarVector)> m_callback;
	};


	struct TOY_UI_EXPORT UiNode : Graph<UiNode>
	{
		UiNode() : Graph() {}
		UiNode(UiNode* parent, size_t index, uint64_t id) : Graph(parent, index, id), m_binding(parent->m_binding.body) {}
		~UiNode() {}
		
		UiNode(UiNode&& other) = default;
		UiNode& operator=(UiNode&& other) = default;

		Binding m_binding;
		int m_mode = 0;
		string m_name;
		std::function<Wedge&(Wedge&, UiNode&)> m_inserter;

		std::vector<Modal> m_modals;

		void pump()
		{
			for(Modal& modal : m_modals)
				modal.decl(*this);
		}

		void destroy()
		{
			for(auto& node : m_nodes)
				node->destroy();
			if(m_binding.widget)
				m_binding.widget->extract();
		}

		template <class T_WidgetFunc, class... T_Args>
		inline UiNode& widget(T_WidgetFunc func, T_Args&&... args)
		{
			if(m_binding.widget) return *this;
			if(m_parent->m_inserter)
				m_binding = func(m_parent->m_inserter(*m_binding.body, *this), std::forward<T_Args>(args)...);
			else
				m_binding = func(*m_binding.body, std::forward<T_Args>(args)...);
			return *this;
		}

		template <class T_Inserter>
		inline UiNode& inserter(T_Inserter inserter)
		{
			if(m_inserter) return *this;
			m_inserter = inserter;
			return *this;
		}

		inline UiNode& name(const string& name)
		{
			if(!m_name.empty()) return *this;
			m_name = name;
			return *this;
		}

		template <class T_RefreshFunc, class... T_Args>
		inline UiNode& refresh(T_RefreshFunc func, T_Args&&... args)
		{
			func(m_binding, std::forward<T_Args>(args)...);
			return *this;
		}

		template <class T_DeclFunc, class... T_Args>
		inline UiNode& submode(int current_mode, int target_mode, T_DeclFunc func, T_Args&&... args)
		{
			if(current_mode == target_mode)
				return subid(current_mode).decl(func, std::forward<T_Args>(args)...);
			return *this;
		}

		template <class... T_Args>
		inline UiNode& modal(const TQueryFunc<T_Args>&... funcs, const std::function<void(T_Args...)>& callback)
		{
			m_modals.emplace_back();
			m_modals.back().init<T_Args...>(funcs..., callback);
			return *this;
		}
	};

	inline Wedge& tabber_insert(Wedge& wedge, UiNode& child)
	{
		return as<Tabber>(wedge).addTab(child.m_name);
	}

	struct TOY_UI_EXPORT TriggerState : public NodeState
	{
		bool m_active;
	};

	inline void trigger(UiNode& node, const string& name, Callback callback)
	{
		TriggerState& state = node.state<TriggerState>();
		node.widget(button, name, [&](Widget&) { state.m_active = true; }, nullptr);
		if(state.m_active)
		{
			state.m_active = false;
			callback();
		}
	}
}

#endif
