//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STYLE_H_INCLUDED
#define MK_STYLE_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/mkIndexer.h>
#include <Object/Util/mkColour.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkDim.h>
#include <Ui/Style/mkImageSkin.h>

/* Standards */
#include <array>
#include <map>

namespace mk
{
	class MK_UI_EXPORT _I_ LayoutStyle : public IdStruct, public Indexed<LayoutStyle>
	{
	public:
		LayoutStyle(const string& name, Flow flow, Opacity opacity, bool div, DimSizing sizing = DimSizing(SHRINK, SHRINK), DimFloat span = DimFloat(1.f, 1.f), Dimension layoutDim = DIM_X, Overflow overflow = CLIP)
			: IdStruct(cls())
			, d_name(name), d_flow(flow), d_opacity(opacity), d_div(div), d_layoutDim(layoutDim)
			, d_overflow(overflow), d_span(span), d_size(0.f, 0.f), d_padding(0.f, 0.f, 0.f, 0.f), d_margin(0.f, 0.f), d_spacing(0.f, 0.f), d_pivot(FORWARD, FORWARD), d_updated(0)
		{}

		LayoutStyle()
			: IdStruct(cls())
		{}

		LayoutStyle& operator=(const LayoutStyle&) = default;
		void copy(LayoutStyle* other) { string name = d_name; *this = *other; d_name = name; }

		_A_ _M_ const string& name() { return d_name; }
		void setName(const string& name) { d_name = name; }

		string d_name;

		_A_ _M_ Flow d_flow;
		_A_ _M_ Overflow d_overflow;
		_A_ _M_ Opacity d_opacity;
		_A_ _M_ bool d_div;
		_A_ _M_ Dimension d_layoutDim;
		_A_ _M_ DimSizing d_sizing;
		_A_ _M_ DimFloat d_span;
		_A_ _M_ DimFloat d_size;
		_A_ _M_ BoxFloat d_padding;
		_A_ _M_ DimFloat d_margin;
		_A_ _M_ DimFloat d_spacing;
		_A_ _M_ DimPivot d_pivot;
		_A_ _M_ Weight d_weight;
		_A_ _M_ std::vector<float> d_weights;

		_A_ _M_ size_t d_updated;
	};

	class MK_UI_EXPORT _I_ InkStyle : public IdStruct, public Indexed<InkStyle>
	{
	public:
		_C_ InkStyle(string name, Colour background, Colour text)
			: IdStruct(cls())
			, mName(name), mEmpty(false), mBackgroundColour(background), mBorderColour(), mTextColour(text), mImageColour(1.f, 1.f, 1.f)
			, mBorderWidth(0.f), mMargin(0.f, 0.f, 0.f, 0.f), mPadding(0.f, 0.f), mImage(""), mCornerRadius(0.f)
		{}

		InkStyle(string name = "")
			: IdStruct(cls())
			, mBackgroundColour(Colour::Transparent), mTextColour(Colour::Transparent), mBorderColour(Colour::Transparent)
			, mName(name), mEmpty(true)
		{}

		InkStyle& operator=(const InkStyle&) = default;
		void copy(InkStyle* other) { string name = mName; *this = *other; mName = name; }

		string mName;

		_A_ _M_ const string& name() { return mName; }

		_A_ _M_ bool mEmpty;
		_A_ _M_ Colour mBackgroundColour;
		_A_ _M_ Colour mBorderColour;
		_A_ _M_ Colour mImageColour;
		_A_ _M_ Colour mTextColour;
		_A_ _M_ BoxFloat mBorderWidth;
		_A_ _M_ BoxFloat mCornerRadius;
		_A_ _M_ BoxFloat mMargin;
		_A_ _M_ DimFloat mPadding;
		_A_ _M_ string mImage;
		_A_ _M_ ImageSkin mImageSkin;

		void setName(const string& name) { mName = name; }
	};

	typedef std::vector<Style*> StyleVector;

	class MK_UI_EXPORT SubSkin
	{
	public:
		SubSkin() {}
		SubSkin(WidgetState state) : mState(state) {}
		SubSkin(WidgetState state, const InkStyle& skin) : mState(state), mSkin(skin) {}

		WidgetState mState;
		InkStyle mSkin;
	};

	typedef std::vector<SubSkin> StyleTable;

	class MK_UI_EXPORT _I_ Style : public IdStruct, public Indexed<Style>, public NonCopy
	{
	public:
		Style(Type* type);
		Style(const string& name);
		~Style();

		_A_ const string& name() { return mName.empty() ? mStyleType->name() : mName; }
		_A_ LayoutStyle* layout() { return &mLayout; }
		_A_ InkStyle* skin() { return &mSkin; }

		Type* styleType() { return mStyleType; }
		const StyleTable& subskins() { return mSubskins; }
		
		InkStyle* subskin(WidgetState state);
		InkStyle* decline(WidgetState state);

		void inheritLayout(Style* base);
		void inheritSkins(Style* base);

	protected:
		Type* mStyleType;
		string mName;
		LayoutStyle mLayout;
		InkStyle mSkin;
		StyleTable mSubskins;
	};

	template <class T>
	class Styled
	{
	public:
		static Style* styleCls() { return &sStyle; }

		static Style sStyle;
	};

	template <class T>
	Style Styled<T>::sStyle(T::cls());
}

#endif // MK_STYLE_H_INCLUDED
