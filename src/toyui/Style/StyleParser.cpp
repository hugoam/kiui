//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#define TOY_WIDGET_STATES_CONVERT_IMPL

#include <toyui/Config.h>
#include <toyui/Style/StyleParser.h>

#include <toyobj/Serial/Serial.h>

#include <toyui/Style/Style.h>
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

	void decline_images(Styler& styler, const string& style, Options& skin_def, const string& state)
	{
		for(size_t i = 0; i < skin_def.m_fields.size(); ++i)
			if(!skin_def.m_fields[i].none() && (skin_def.m_fields[i].type().is<Image>()
												|| skin_def.m_fields[i].type().is<ImageSkin>()))
			{
				Member& member = meta<InkStyle>().m_members[i];


				Var value = skin_def.m_fields[member.m_index];
				Options& declined_skin_def = styler.m_skin_definitions[style + ":" + state];

				if(value.type().is<Image>())
				{
					Image& declined_image = styler.m_uiWindow.findImage(value.val<Image>().d_name + "_" + replaceAll(state, "|", "_"));
					declined_skin_def.set(member.m_index, Ref(&declined_image));
				}
				else if(value.type().is<ImageSkin>())
				{
					Image& declined_image = styler.m_uiWindow.findImage(value.val<ImageSkin>().d_image->d_name + "_" + replaceAll(state, "|", "_"));
					declined_skin_def.set(member.m_index, var(ImageSkin(declined_image, value.val<ImageSkin>())));
				}
			}
	}

	void decline(Styler& styler, const string& style, Options& skin_def, const json& json_states)
	{
		for(json::const_iterator state_it = json_states.begin(); state_it != json_states.end(); ++state_it)
			decline_images(styler, style, skin_def, state_it->get<string>());
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

	void load_member(Styler& styler, Options& definition, Member& member, const json& json_value)
	{
		static FromJson unpacker = style_unpacker(styler.m_uiWindow);
		Var value = unpack(unpacker, *member.m_type, json_value);
		definition.set(member.m_index, value);
	}

	void load_style_attr(Styler& styler, const string& style, Options& layout_def, Options& skin_def, string key, const json& json_value)
	{
		string skin_key = replaceAll(key, "skin_", "");

		if(key == "selector" || key == "reset_skin")
			;
		else if(key == "copy_skin")
			skin_def.merge(styler.m_skin_definitions[json_value.get<string>()]);
		else if(key == "decline")
			decline(styler, style, skin_def, json_value);
		else if(meta<Layout>().hasMember(key))
			load_member(styler, layout_def, meta<Layout>().member(key), json_value);
		else if(meta<InkStyle>().hasMember(skin_key))
			load_member(styler, skin_def, meta<InkStyle>().member(skin_key), json_value);
		else if(key.find("comment") != string::npos)
			;
		else // if(vector_has(meta<WidgetState>().m_enumIds, toUpper(key)))
		{
			std::vector<string> states = splitString(replaceAll(key, " ", ""), ",");
			
			for(const string& state : states)
				load_style(styler, style + ":" + state, json_value);
		}
	}

	void load_style(Styler& styler, const string& selector, const json& json_style)
	{
		std::vector<string> names = splitString(replaceAll(selector, " ", ""), ",");
		
		for(const string& name : names)
		{
			Options& layout_def = styler.m_layout_definitions[name];
			Options& skin_def = styler.m_skin_definitions[name];

			for(json::const_iterator attr_it = json_style.begin(); attr_it != json_style.end(); ++attr_it)
				load_style_attr(styler, name, layout_def, skin_def, attr_it.key(), attr_it.value());
		}
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
		json style_sheet = parse_json_file(path);

		json includes = style_sheet["includes"];
		for(json::const_iterator style_it = includes.begin(); style_it != includes.end(); ++style_it)
			load_style_sheet(styler, styler.m_uiWindow.m_resourcePath + "interface/styles/" + style_it->get<string>());

		std::map<string, Colour> colours;
		load_colours(colours, style_sheet["colours"]);
		replace_colours(colours, style_sheet["styles"]);

		json styles = style_sheet["styles"];
		for(json::const_iterator style_it = styles.begin(); style_it != styles.end(); ++style_it)
			load_style(styler, (*style_it)["selector"], *style_it);
	}

	void set_style_sheet(Styler& styler, const string& path)
	{
		styler.clear();

		load_style_sheet(styler, path);

		styler.setup();
	}

	void set_default_style_sheet(Styler& styler)
	{
		styler.clear();
		styler.setup();
	}
}
