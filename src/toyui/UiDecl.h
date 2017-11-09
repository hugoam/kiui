//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UI_DECL_H
#define TOY_UI_DECL_H

/* toy */
#include <toyui/Forward.h>
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
		return { parent.emplace<Label>(name) };
	}

	inline Binding button(Wedge& parent, const string& name, Button::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace<Button>(name, callback) };
	}

	inline Binding multibutton(Wedge& parent, const StringVector& elements, MultiButton::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace<MultiButton>(elements, callback) };
	}

	inline Binding radioswitch(Wedge& parent, const StringVector& elements, RadioSwitch::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace<RadioSwitch>(elements, callback) };
	}

	inline Binding dropdown(Wedge& parent, const StringVector& elements, DropdownInput::Callback callback, Style* style = nullptr)
	{
		return { parent.emplace<DropdownInput>(elements, callback) };
	}

	inline Binding wedge(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Wedge>(Wedge::cls()) };
	}

	inline Binding sheet(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Wedge>(Wedge::Sheet()) };
	}

	inline Binding layout(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Wedge>(Wedge::Layout()) };
	}

	inline Binding layout_span(Wedge& parent, float span)
	{
		Wedge& layout = parent.emplace<Wedge>(Wedge::Layout());
		layout.frame().setSpanDim(DIM_X, span);
		return { layout };
	}

	inline Binding board(Wedge& parent, Style* style = nullptr)
	{
		return{ parent.emplace<Wedge>(Wedge::Board()) };
	}

	inline Binding list(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Wedge>(Wedge::List()) };
	}

	inline Binding row(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Wedge>(Wedge::Row()) };
	}

	inline Binding scrollsheet(Wedge& parent, Style* style = nullptr)
	{
		ScrollSheet& scrollsheet = parent.emplace<ScrollSheet>();
		return { scrollsheet, scrollsheet.m_body};
	}

	inline Binding select_list(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<SelectList>() };
	}

	inline Binding expandbox(Wedge& parent, const StringVector& elements, Style* style = nullptr)
	{
		Expandbox& expandbox = parent.emplace<Expandbox>(elements);
		return { expandbox, expandbox.m_body };
	}

	inline Binding toolbar(Wedge& parent, Style* style = nullptr)
	{
		return { parent.emplace<Toolbar>() };
	}

	inline Binding tabber(Wedge& parent, Style* style = nullptr)
	{
		Tabber& tabber = parent.emplace<Tabber>();
		return { tabber };
	}

	inline Binding window(Wedge& parent, const string& name, Style* style = nullptr)
	{
		Window& window = parent.emplace<Window>(name);
		return { window, window.m_body };
	}

	inline Binding canvas(Wedge& parent, const string& name, Widget::Callback callback, Style* style = nullptr)
	{
		Canvas& canvas = parent.emplace<Canvas>(name, callback);
		return { canvas, canvas.m_body };
	}

	inline Binding node(Wedge& parent, const string& name, int order, Style* style = nullptr)
	{
		return { parent.emplace<Node>(name, order) };
	}


	using QueryFunc = std::function<void(UiNode&, const std::function<void(Lref)>&)>;

	template <class T_Value>
	using TQueryFunc = std::function<void(UiNode&, const std::function<void(T_Value)>&)>;

	struct Query
	{
		Query(QueryFunc decl) : m_decl(decl) {}

		void decl(UiNode& node) { m_decl(node, [this](Lref value) { m_result = value; m_done = true; }); }

		bool m_done = false;
		QueryFunc m_decl = nullptr;
		Lref m_result = {};
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
			m_queries.emplace_back([decl](UiNode& node, const std::function<void(Lref)>& callback)
			{
				decl(node, typed_func<T_Value>(callback));
			});
		}

		virtual void decl(UiNode& node) final
		{
			Query& current_query = m_queries[m_current_step];
			current_query.decl(node);
			if(current_query.m_done)
				m_current_step++;
			if(m_current_step == m_queries.size())
				this->done();
		}

		void done()
		{
			LrefVector results;
			for(Query& query : m_queries)
				results.push_back(query.m_result);
			m_callback(results);
		}

		std::vector<Query> m_queries;
		size_t m_current_step;
		std::function<void(LrefVector)> m_callback;
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

		std::vector<Modal> m_modals;

		void pump()
		{
			for(Modal& modal : m_modals)
				modal.decl(*this);
		}

		void destroy()
		{
			if(m_binding.widget)
				m_binding.widget->extract();
		}

		template <class T_WidgetFunc, class... T_Args>
		inline void widget(T_WidgetFunc func, T_Args&&... args)
		{
			if(m_binding.widget) return;
			m_binding = func(*m_binding.body, std::forward<T_Args>(args)...);
		}

		template <class T_RefreshFunc, class... T_Args>
		inline void refresh(T_RefreshFunc func, T_Args&&... args)
		{
			func(m_binding, std::forward<T_Args>(args)...);
		}

		template <class T_DeclFunc, class... T_Args>
		inline void mode(int mode, T_DeclFunc func, T_Args&&... args)
		{
			if(m_mode == mode)
				decl(func, std::forward<T_Args>(args)...);
		}

		template <class... T_Args>
		inline void modal(const TQueryFunc<T_Args>&... funcs, const std::function<void(T_Args...)>& callback)
		{
			m_modals.emplace_back();
			m_modals.back().init<T_Args...>(funcs..., callback);
		}
	};

	struct TOY_UI_EXPORT TriggerState : public NodeState
	{
		bool m_active;
	};

	inline void trigger(UiNode& node, const string& name, Callback callback)
	{
		TriggerState& state = node.state<TriggerState>();
		node.widget(button, name, [&state](Widget&) { state.m_active = true; }, nullptr);
		if(state.m_active)
		{
			state.m_active = false;
			callback();
		}
	}
}

#endif
