//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INK_H
#define MK_INK_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Style/mkStyle.h>

namespace mk
{
	class MK_UI_EXPORT InkWindow : public Object, public Typed<InkWindow>
	{
	public:
		virtual InkTarget* screenTarget() = 0;
		//virtual InkTarget* spaceTarget(Camera* camera, int width, int height) = 0;
	};

	class MK_UI_EXPORT InkTarget : public Object, public Typed<InkTarget>
	{
	public:
		virtual unique_ptr<InkLayer> layer(Frame* frame, size_t z = 0) = 0;
	};
	
	class MK_UI_EXPORT InkLayer : public Object, public Typed<InkLayer>
	{
	public:
		InkLayer(InkTarget* target) : mTarget(target) {}
		virtual ~InkLayer() {}

		InkTarget* target() { return mTarget; }

		virtual unique_ptr<Inkbox> inkbox(Frame* frame) = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void moveToTop() = 0;

	protected:
		InkTarget* mTarget;
	};

	class MK_UI_EXPORT Inkbox
	{
	public:
		Inkbox(Frame* frame) : mFrame(frame), mVisible(frame->visible()) {}
		virtual ~Inkbox() {}

		Frame* frame() { return mFrame; }
		bool visible() { return mVisible; }

		virtual void show() = 0;
		virtual void hide() = 0;

		virtual void updateContent() = 0;
		virtual void updateStyle() = 0;
		virtual void updateFrame() = 0;

		virtual float contentSize(Dimension dim) = 0;
		virtual size_t caretIndex(float x, float y) = 0;
		virtual void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight) = 0;

	protected:
		Frame* mFrame;
		bool mVisible;
	};
}

#endif
