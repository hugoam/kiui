//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UILAYOUT_H
#define TOY_UILAYOUT_H

/* toy Front */
#include <toyui/Forward.h>
#include <toyobj/Util/Colour.h>
#include <toyobj/Util/NonCopy.h>
#include <toyobj/String/String.h>
#include <toyui/Style/Style.h>

/* standard */
#include <map>

namespace toy
{
	struct TOY_UI_EXPORT StyleOverride : public NonCopy
	{
	public:
		StyleOverride(Style& style, Style& overrider) : m_style(style), m_override(overrider) {}
		StyleOverride(StyleOverride&& other) : m_style(other.m_style), m_override(other.m_override) {}
		//StyleOverride& operator=(StyleOverride&&other) { m_style = other.m_style; m_override = other.m_override; return *this; }

		Style& m_style;
		Style& m_override;
	};

	typedef std::map<WidgetState, string> InkIdMap;

	class TOY_UI_EXPORT Styler : public NonCopy
	{
	public:
		Styler();
		~Styler();

		void prepare();
		void reset();

		void defaultLayout();
		void defaultSkins();

		void override(Style& stem, Style& style, Style& overrider);
		void override(const string& stem, const string& style, const string& overrider);

		Style* fetchOverride(Style& style, Style& overrider);

		Style& dynamicStyle(const string& name);
		Style* fetchStyle(const string& name);

	protected:
		std::vector<std::unique_ptr<Style>> m_dynamicStyles;
		std::vector<std::vector<StyleOverride>> m_overrides;
	};

	class TOY_UI_EXPORT EmptyStyle : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("Empty"); return ty; }
	};
}

#endif
