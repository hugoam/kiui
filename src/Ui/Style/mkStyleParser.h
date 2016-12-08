//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STYLEPARSER_H
#define MK_STYLEPARSER_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Object/Util/mkUnique.h>

namespace mk
{
	enum ParserState
	{
		IN_DOCUMENT,
		IN_MAIN_BLOCK,
		IN_STYLE_DEFINITION,
		IN_SUBSKIN_DEFINITION,
	};

	enum ParserKeyState
	{
		IN_KEY_DEFINITION,
		IN_VALUE_DEFINITION
	};

	class MK_UI_EXPORT StyleParser
	{
	public:
		StyleParser(Styler& styler);
		~StyleParser();

		void loadDefaultStyle();
		void loadStyleSheet(const string& path);
		
		void startStyle(const string& name);
		void startSubskin(const string& name);
		void parseValue(const string& key, const string& value);

		void declineImage(const string& states);
		void declineImageSkin(const string& states);

	protected:
		Styler& m_styler;
		ParserState m_state;
		ParserKeyState m_keyState;
		Style* m_style;
		InkStyle* m_skin;
		LayoutStyle* m_layoutStyle;
		InkStyle* m_inkStyle;
		string m_key;

		class Impl;
		unique_ptr<Impl> m_pimpl;
	};
}

#endif // MK_STYLEPARSER_H
