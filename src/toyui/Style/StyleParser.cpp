//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#define TOY_WIDGET_STATES_CONVERT_IMPL

#include <toyui/Config.h>
#include <toyui/Style/StyleParser.h>

#include <toyobj/Serial/Serial.h>

#include <toyobj/Generated/Meta.h>
#include <toyui/Generated/Meta.h>
#include <toyobj/String/StringConvert.h>

#include <toyui/Widget/Widget.h>
#include <toyui/UiLayout.h>
#include <toyui/UiWindow.h>

namespace toy
{
	void load_style(Styler& styler, const string& name, const json& json_style);

	void from_json(const json& j, Colour& col)
	{
		col = { j[0], j[1], j[2], j[3] };
	}

	void to_json(json& j, const Colour& col)
	{
		j = { col.m_r, col.m_g, col.m_b, col.m_a };
	}

	void decline(const string& strStates)
	{
		/*for(auto& image : m_styler.m_uiWindow.m_images)
		{

		}

		std::vector<string> states = splitString(strStates, ",");
		for(const string& strState : states)
		{
			WidgetState state = widgetState(strState);
			string suffix = "_" + replaceAll(strState, "|", "_");
			InkStyle& inkstyle = m_style->decline(state);
			if(inkstyle.m_image)
				inkstyle.m_image = &m_styler.m_uiWindow.findImage(m_skin->m_image->d_name + suffix);
			if(!inkstyle.m_image_skin.null())
				inkstyle.m_image_skin = ImageSkin(m_styler.m_uiWindow.findImage(m_skin->m_image_skin.d_image->d_name + suffix), m_skin->m_image_skin);
		}*/
	}

	FromJson style_unpacker(UiWindow& uiWindow)
	{
		FromJson unpacker;
		unpacker.func<Image>([&](Ref ref, const json& json) -> Var
		{
			return Ref(json == "null" ? (Image*) nullptr
									  : &uiWindow.findImage(json));
		});
		return unpacker;
	}

	void load_default_style_sheet(Styler& styler)
	{
		styler.setup();
	}

	void load_member(Styler& styler, Options& definition, Member& member, const json& json_value)
	{
		static FromJson unpacker = style_unpacker(styler.m_uiWindow);
		Var value = unpack(unpacker, *member.m_type, json_value);
		definition.set(member.m_index, value);
	}

	void load_style_attr(Styler& styler, const string& style, Options& layout_def, Options& skin_def, string key, const json& json_value)
	{
		string skin_key = replaceAll(key, "skin_", "");

		if(key == "style" || key == "reset_skin")
			;
		else if(key == "copy_skin")
			skin_def.merge(styler.m_skin_definitions[json_value.get<string>()]);
		//else if(key == "reset_skin")
		//	m_style->m_skin.m_base = nullptr;
		else if(key == "decline")
			decline(json_value.get<string>());
		else if(meta<Layout>().hasMember(key))
			load_member(styler, layout_def, meta<Layout>().member(key), json_value);
		else if(meta<InkStyle>().hasMember(skin_key))
			load_member(styler, skin_def, meta<InkStyle>().member(skin_key), json_value);
		else // if(vector_has(meta<WidgetState>().m_enumIds, toUpper(key)))
		{
			WidgetStates state = fromString<WidgetStates>(key);
			string substyle = style + ":" + key;
			load_style(styler, substyle, json_value);
		}
	}

	void load_style(Styler& styler, const string& name, const json& json_style)
	{
		Options& layout_def = styler.m_layout_definitions[name];
		Options& skin_def = styler.m_skin_definitions[name];

		for(json::const_iterator attr_it = json_style.begin(); attr_it != json_style.end(); ++attr_it)
			load_style_attr(styler, name, layout_def, skin_def, attr_it.key(), attr_it.value());
	}

	void replace_colours(const std::map<string, Colour>& colours, json& json_value)
	{
		visit_json(json_value, [&](json& json_value)
		{
			if(json_value.is_string() && colours.find(json_value.get<string>()) != colours.end())
				json_value = colours.at(json_value.get<string>());
		});
	}

	void load_colours(std::map<string, Colour>& colours, const json& json_colours)
	{
		for(json::const_iterator colour_it = json_colours.begin(); colour_it != json_colours.end(); ++colour_it)
			colours[colour_it.key()] = colour_it.value();
	}

	void load_style_sheet(Styler& styler, const string& path)
	{
		styler.clear();

		json content = parse_json_file(path);

		std::map<string, Colour> colours;

		load_colours(colours, content["colours"]);
		replace_colours(colours, content["styles"]);

		json styles = content["styles"];
		for(json::const_iterator style_it = styles.begin(); style_it != styles.end(); ++style_it)
			load_style(styler, (*style_it)["style"], *style_it);

		styler.setup();
	}
}
