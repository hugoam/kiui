//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INK_H
#define MK_INK_H

/* mk Front */
#include <Object/Util/mkColour.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkUibox.h>

namespace mk
{
	class MK_UI_EXPORT InkWindow : public Object, public Typed<InkWindow>
	{
	public:
		virtual InkTarget* screenTarget() = 0;
		//virtual InkTarget* spaceTarget(Camera* camera, int width, int height) = 0;
	};

	class MK_UI_EXPORT InkLayer : public Object, public Typed<InkLayer>
	{
	public:
		virtual unique_ptr<Inkbox> inkbox(Frame* frame) = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void moveToTop() = 0;
	};

	class MK_UI_EXPORT InkTarget : public Object, public Typed<InkTarget>
	{
	public:
		virtual unique_ptr<InkLayer> layer(Frame* frame, size_t z = 0) = 0;
	};

	class MK_UI_EXPORT _I_ InkStyle : public Struct, public Typed<InkStyle>
	{
	public:
		_C_ InkStyle(string name, Colour background, Colour text)
			: mName(name), mEmpty(false), mBackgroundColour(background), mBorderColour(), mTextColour(text), mImageColour(1.f, 1.f, 1.f)
			, mBorderWidth(0.f), mMargin(0.f, 0.f, 0.f, 0.f), mPadding(0.f, 0.f), mImage(""), mCornerRadius(0.f)
		{}

		InkStyle(string name)
			: mName(name), mEmpty(true)
		{}

		InkStyle()
		{}

		InkStyle& operator=(const InkStyle&) = default;
		void copy(InkStyle* other) { string name = mName; *this = *other; mName = name; }

		const string& name() { return mName; }

		_A_ _M_ string mName;
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

		std::map<WidgetState, InkStyle*> mSubInks;
	};

	class MK_UI_EXPORT Inkbox
	{
	public:
		Inkbox(Frame* frame) : mFrame(frame) {}
		virtual ~Inkbox() {}

		Frame* frame() { return mFrame; }

		virtual void show() = 0;
		virtual void hide() = 0;

		virtual void updateContent() = 0;
		virtual void updateStyle() = 0;
		virtual void updateFrame() = 0;

		virtual float contentSize(Dimension dim) = 0;

	protected:
		Frame* mFrame;
	};
}

#endif
