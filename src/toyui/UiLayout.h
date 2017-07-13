//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UILAYOUT_H
#define TOY_UILAYOUT_H

/* toy */
#include <toyui/Forward.h>
#include <toyobj/Object.h>
#include <toyobj/Util/Colour.h>
#include <toyobj/String/String.h>
#include <toyui/Style/Style.h>

/* standard */
#include <map>

namespace toy
{
	using StyleInitializer = std::function<void(Styler&)>;

	class TOY_UI_EXPORT Styler : public Object
	{
	public:
		Styler(UiWindow& uiWindow);
		~Styler();

		UiWindow& uiWindow() { return m_uiWindow; }

		void addInitializer(const StyleInitializer& initializer) { m_initializers.push_back(initializer); }

		void clear();
		void reset();

		void defaultLayout();

		Style& styledef(Type& type);
		Style& styledef(const string& name);

		Style& style(Type& type);
		Style& style(const string& name);

		void initStyle(Type& type);
		void prepareStyle(Style& style);

		static Type& cls() { static Type ty; return ty; }

	protected:
		UiWindow& m_uiWindow;

		std::map<string, object_ptr<Style>> m_styledefs;
		std::map<string, object_ptr<Style>> m_styles;

		std::vector<StyleInitializer> m_initializers;
	};
}

#endif
