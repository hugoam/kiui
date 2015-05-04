//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Style/mkStyleParser.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkTimer.h>

#include <Ui/mkUiLayout.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Style/yaml/yaml.h>

namespace mk
{
	template <> Flow fromString<Flow>(const string& str) { if(str == "FLOW") return FLOW; else if(str == "OVERLAY") return OVERLAY; return FLOW; }
	template <> Space fromString<Space>(const string& str) { if(str == "AUTO") return AUTO; if(str == "BLOCK") return BLOCK; else if(str == "FIT") return FIT; else if(str == "DIV") return DIV; else if(str == "SPACE") return SPACE; else if(str == "BOARD") return BOARD; return AUTO; }
	template <> Clipping fromString<Clipping>(const string& str) { if(str == "NOCLIP") return NOCLIP; else if(str == "CLIP") return CLIP; return NOCLIP; }
	template <> Opacity fromString<Opacity>(const string& str) { if(str == "OPAQUE") return OPAQUE; else if(str == "VOID") return VOID; return OPAQUE; }
	template <> Dimension fromString<Dimension>(const string& str) { if(str == "DIM_X") return DIM_X; else if(str == "DIM_Y") return DIM_Y; return DIM_X; }
	template <> Sizing fromString<Sizing>(const string& str) { if(str == "FIXED") return FIXED; else if(str == "MANUAL") return MANUAL; else if(str == "SHRINK") return SHRINK; else if(str == "EXPAND") return EXPAND; return FIXED; }
	template <> Align fromString<Align>(const string& str) { if(str == "CENTER") return CENTER; else if(str == "LEFT") return LEFT; else if(str == "RIGHT") return RIGHT; return LEFT; }
	template <> Pivot fromString<Pivot>(const string& str) { if(str == "FORWARD") return FORWARD; else if(str == "REVERSE") return REVERSE; return FORWARD; }
	template <> Weight fromString<Weight>(const string& str) { if(str == "LIST") return LIST; else if(str == "TABLE") return TABLE; return LIST; }

	template <> DimSizing fromString<DimSizing>(const string& str) { std::vector<string> dimStr = splitString(str, ","); return DimSizing(fromString<Sizing>(dimStr[0]), fromString<Sizing>(dimStr[1])); }
	template <> DimPivot fromString<DimPivot>(const string& str) { std::vector<string> dimStr = splitString(str, ","); return DimPivot(fromString<Pivot>(dimStr[0]), fromString<Pivot>(dimStr[1])); }
	template <> DimAlign fromString<DimAlign>(const string& str) { std::vector<string> dimStr = splitString(str, ","); return DimAlign(fromString<Align>(dimStr[0]), fromString<Align>(dimStr[1])); }

	template <> inline void fromString<DimFloat>(const string& str, DimFloat& vec) { string_to_fixed_vector<DimFloat, float>(str, vec); }
	template <> inline void toString<DimFloat>(const DimFloat& val, string& str) { return fixed_vector_to_string<DimFloat, 2>(val, str); }

	template <> inline void fromString<BoxFloat>(const string& str, BoxFloat& vec) { string_to_fixed_vector<BoxFloat, float>(str, vec); }
	template <> inline void toString<BoxFloat>(const BoxFloat& val, string& str) { return fixed_vector_to_string<BoxFloat, 4>(val, str); }

	template <> WidgetState fromString<WidgetState>(const string& str)
	{
		int state = 0;
		std::vector<string> names = splitString(str, "|");
		std::vector<WidgetState> states;
		for(const string& name : names)
		{
			if(name == "unbound") state |= UNBOUND;
			else if(name == "bound") state |= BOUND;
			else if(name == "hovered") state |= HOVERED;
			else if(name == "triggered") state |= TRIGGERED;
			else if(name == "activated") state |= ACTIVATED;
			else if(name == "focused") state |= FOCUSED;
			else if(name == "pressed") state |= PRESSED;
			else if(name == "dragged") state |= DRAGGED;
			else if(name == "modal") state |= MODAL;
		}

		return static_cast<WidgetState>(state);
	}

	class StyleParser::Impl
	{
	public:
		Impl()
		{
			yaml_parser_initialize(&mParser);
		}

		~Impl()
		{
			yaml_parser_delete(&mParser);
		}

		yaml_parser_t mParser;
	};

	StyleParser::StyleParser(Styler& styler)
		: mStyler(styler)
		, mState(IN_DOCUMENT)
		, mKeyState(IN_KEY_DEFINITION)
		, mPimpl(make_unique<Impl>())
	{}

	StyleParser::~StyleParser()
	{}

	void StyleParser::loadDefaultStyle()
	{
		mStyler.reset();
		mStyler.defaultSkins();
		mStyler.prepare();
	}

	void StyleParser::loadStyleSheet(const string& path)
	{
		mStyler.reset();

		yaml_token_t token;

		int done = 0;

		FILE *input = fopen(path.c_str(), "rb");
		yaml_parser_set_input_file(&mPimpl->mParser, input);

		while(!done)
		{
			if(!yaml_parser_scan(&mPimpl->mParser, &token))
				return;

			switch(token.type)
			{
			case YAML_KEY_TOKEN:
				mKeyState = IN_KEY_DEFINITION;
				break;
			case YAML_VALUE_TOKEN:
				mKeyState = IN_VALUE_DEFINITION;
				break;
			case YAML_BLOCK_MAPPING_START_TOKEN:
			case YAML_FLOW_MAPPING_START_TOKEN:
				if(mState == IN_DOCUMENT)
					mState = IN_MAIN_BLOCK;
				else if(mState == IN_MAIN_BLOCK)
					this->startStyle(mKey);
				else if(mState == IN_STYLE_DEFINITION)
					this->startSubskin(mKey);
				break;
			case YAML_BLOCK_END_TOKEN:
			case YAML_FLOW_MAPPING_END_TOKEN:
				if(mState == IN_STYLE_DEFINITION)
					mState = IN_MAIN_BLOCK;
				if(mState == IN_SUBSKIN_DEFINITION)
					mState = IN_STYLE_DEFINITION;
				break;
			case YAML_SCALAR_TOKEN:
				if(mKeyState == IN_KEY_DEFINITION)
					mKey = reinterpret_cast<const char*>(token.data.scalar.value);
				else if(mKeyState == IN_VALUE_DEFINITION)
					this->parseValue(mKey, reinterpret_cast<const char*>(token.data.scalar.value));
				break;
			default:
				break;
			}

			done = (token.type == YAML_STREAM_END_TOKEN);
			yaml_token_delete(&token);
		}

		mStyler.prepare();
	}

	void StyleParser::startStyle(const string& name)
	{
		mState = IN_STYLE_DEFINITION;
		mStyle = &mStyler.dynamicStyle(name);
		mStyle->setUpdated(mStyle->updated() + 1);
		mSkin = &mStyle->skin();
		mStyle->skin().mEmpty = false;
	}

	void StyleParser::startSubskin(const string& name)
	{
		mState = IN_SUBSKIN_DEFINITION;
		string clean = replaceAll(name, " ", "");
		WidgetState state = fromString<WidgetState>(clean);
		mSkin = &mStyle->decline(state);
	}

	void StyleParser::declineImage(const string& strStates)
	{
		std::vector<string> states = splitString(strStates, ",");
		for(const string& strState : states)
		{
			WidgetState state = fromString<WidgetState>(strState);
			string suffix = "_" + replaceAll(strState, "|", "_");
			mStyle->decline(state).mImage = Image(mSkin->image().d_name + suffix);
		}
	}
	
	void StyleParser::declineImageSkin(const string& strStates)
	{
		std::vector<string> states = splitString(strStates, ",");
		for(const string& strState : states)
		{
			WidgetState state = fromString<WidgetState>(strState);
			string suffix = "_" + replaceAll(strState, "|", "_");
			InkStyle& inkstyle = mStyle->decline(state);
			inkstyle.mImageSkin = mSkin->mImageSkin;
			inkstyle.mImageSkin.val.setImage(Image(mSkin->mImageSkin.val.d_image.d_name + suffix));
		}
	}

	void StyleParser::parseValue(const string& key, const string& valueRaw)
	{
		string value = replaceAll(valueRaw, " ", "");
		std::vector<string> values = splitString(value, ",");

		if(key == "inherit")
			mStyle->rebase(*mStyler.fetchStyle(value));
		if(key == "inherit_skin")
			mStyle->rebaseSkins(*mStyler.fetchStyle(value));
		if(key == "copy_skin")
			mStyle->copySkins(*mStyler.fetchStyle(value));
		else if(key == "override")
			mStyler.override(values[0], values[1], mStyle->name());

		else if(key == "flow")
			mStyle->layout().d_flow = fromString<Flow>(value); // FLOW | OVERLAY | FLOAT
		else if(key == "clipping")
			mStyle->layout().d_clipping = fromString<Clipping>(value); // NOCLIP | CLIP
		else if(key == "opacity")
			mStyle->layout().d_opacity = fromString<Opacity>(value); // OPAQUE | VOID
		else if(key == "space")
			mStyle->layout().d_space = fromString<Space>(value); // AUTO | BLOCK | FIT | DIV | SPACE | BOARD
		else if(key == "sizing")
			mStyle->layout().d_sizing = fromString<DimSizing>(value); // FIXED | SHRINK | EXPAND
		else if(key == "layout_dim")
			mStyle->layout().d_layoutDim = fromString<Dimension>(value); // DIM_X | DIM_Y
		else if(key == "align")
			mStyle->layout().d_align = fromString<DimAlign>(value); // x, y
		else if(key == "need")
			mStyle->layout().d_space = fromString<Space>(value); // BLOCK | SPACE | BOARD
		else if(key == "span")
			mStyle->layout().d_span = fromString<DimFloat>(value); // 1.0, 1.0
		else if(key == "size")
			mStyle->layout().d_size = fromString<DimFloat>(value); // 123.0, 123.0
		else if(key == "padding")
			mStyle->layout().d_padding = fromString<BoxFloat>(value); // left, right, top, bottom
		else if(key == "margin")
			mStyle->layout().d_margin = fromString<DimFloat>(value); // x, y
		else if(key == "spacing")
			mStyle->layout().d_spacing = fromString<DimFloat>(value); // x, y
		else if(key == "pivot")
			mStyle->layout().d_pivot = fromString<DimPivot>(value);// FORWARD | REVERSE
		else if(key == "weight")
			mStyle->layout().d_weight = fromString<Weight>(value); // LIST | TABLE
		else if(key == "weights")
			mStyle->layout().d_weights = fromString<std::vector<float>>(value); // : 0.3, 0.4, 0.3

		else if(key == "empty")
			mSkin->mEmpty = (value == "false" ? false : true);
		else if(key == "background_colour")
			mSkin->mBackgroundColour = fromString<Colour>(value); // r, g, b, a
		else if(key == "border_colour")
			mSkin->mBorderColour = fromString<Colour>(value); // r, g, b, a
		else if(key == "image_colour")
			mSkin->mImageColour = fromString<Colour>(value); // r, g, b, a
		else if(key == "text_colour")
			mSkin->mTextColour = fromString<Colour>(value); // r, g, b, a
		else if(key == "text_size")
			mSkin->mTextSize = fromString<float>(value); // 0.0
		else if(key == "text_colour")
			mSkin->mTextFont = value; // fontname
		else if(key == "border_width")
			mSkin->mBorderWidth = fromString<BoxFloat>(value); // top, right, bottom, left
		else if(key == "corner_radius")
			mSkin->mCornerRadius = fromString<BoxFloat>(value); // topleft, topright, bottomright, bottomleft
		else if(key == "weak_corners")
			mSkin->mWeakCorners = (value == "false" ? false : true); // true | false
		else if(key == "skin_align")
			mSkin->mAlign = fromString<DimAlign>(value); // x, y
		else if(key == "skin_padding")
			mSkin->mPadding = fromString<BoxFloat>(value); // left, right, top, bottom
		else if(key == "skin_margin")
			mSkin->mMargin = fromString<BoxFloat>(value); // x, y, z, w
		else if(key == "topdown_gradient")
			mSkin->mTopdownGradient = fromString<DimFloat>(value); // top, down
		else if(key == "image")
			mSkin->mImage = Image(value); // image.png
		else if(key == "overlay")
			mSkin->mOverlay = Image(value); // image.png
		else if(key == "tile")
			mSkin->mTile = Image(value); // image.png
		else if(key == "image_skin")
			mSkin->mImageSkin = ImageSkin(values[0],	fromString<int>(values[1]), fromString<int>(values[2]),
														fromString<int>(values[3]), fromString<int>(values[4]),
														values.size() > 5 ? fromString<int>(values[5]) : 0,
														values.size() > 6 ? fromString<Dimension>(values[6]) : DIM_NULL); // : image.png
		else if(key == "shadow")
			mSkin->mShadow = Shadow(	fromString<float>(values[0]), fromString<float>(values[1]),
										fromString<float>(values[2]), fromString<float>(values[3])); // : xoffset, yoffset, blur, spread
		else if(key == "no_shadow")
			mSkin->mShadow = Shadow();
		else if(key == "shadow_colour")
			mSkin->mShadow.val.d_colour = fromString<Colour>(value);
		else if(key == "decline_image")
			this->declineImage(value);
		else if(key == "decline_image_skin")
			this->declineImageSkin(value);
	}
}
