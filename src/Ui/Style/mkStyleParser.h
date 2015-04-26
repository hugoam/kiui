//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STYLEPARSER_H_INCLUDED
#define MK_STYLEPARSER_H_INCLUDED

/* mk */
#include <Ui/mkUiForward.h>
#include <Object/Util/mkMake.h>

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
		Styler& mStyler;
		ParserState mState;
		ParserKeyState mKeyState;
		Style* mStyle;
		InkStyle* mSkin;
		LayoutStyle* mLayoutStyle;
		InkStyle* mInkStyle;
		string mKey;

		class Impl;
		unique_ptr<Impl> mPimpl;
	};
}

#endif // MK_STYLEPARSER_H_INCLUDED
