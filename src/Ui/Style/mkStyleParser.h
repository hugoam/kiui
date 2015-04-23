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

	/*
	styleid :
	    inherit : parentid
		override : parentid, overridenid

		flow : FLOW | MANUAL
		clipping : NOCLIP | CLIP
		opacity : OPAQUE | VOID
		layout_dim : DIM_X | DIM_Y
		sizing : FIXED | SHRINK | EXPAND | WRAP, idem
		span : 1.0, 1.0
		size : 123.0, 321.0
		padding : left, right, top, bottom
		margin : x, y
		spacing : x, y
		pivot : FORWARD | REVERSE, idem
		weight : LIST | TABLE
		weights : 0.3, 0.4, 0.3

		background_colour : r, g, b, a
		border_colour : r, g, b, a
		image_colour : r, g, b, a
		text_colour : r, g, b, a
		border_width : top, right, bottom, left
		corner_radius : topleft, topright, bottomright, bottomleft
		margin : x, y
		padding : x, y
		image : image.png
		image_skin : image.png
	*/

}

#endif // MK_STYLEPARSER_H_INCLUDED
