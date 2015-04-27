//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INK_H
#define MK_INK_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Style/mkStyle.h>

namespace mk
{
	class MK_UI_EXPORT InkWindow : public Object
	{
	public:
		virtual InkTarget& screenTarget() = 0;
		//virtual InkTarget* spaceTarget(Camera* camera, int width, int height) = 0;

		static Type& cls() { static Type ty; return ty; }
	};

	class MK_UI_EXPORT InkTarget : public Object
	{
	public:
		InkTarget(size_t layers) : mZMax(0), mLayers(layers) {}

		size_t zmax() { return mZMax; }
		size_t ztop() { return mLayers.size() - 1; }

		unique_ptr<InkLayer> addLayer(Layer& layer, size_t z);
		void removeLayer(InkLayer& layer);
		void moveToTop(InkLayer& layer);

		static Type& cls() { static Type ty; return ty; }

	protected:
		virtual unique_ptr<InkLayer> createLayer(Layer& layer, size_t z) = 0;

	protected:
		size_t mZMax;
		std::vector<std::vector<InkLayer*>> mLayers;
	};
	
	class MK_UI_EXPORT InkLayer : public Object
	{
	public:
		InkLayer(Layer& layer, InkTarget& target, size_t index) : mLayer(layer), mTarget(target), mIndex(index) {}
		virtual ~InkLayer() { mTarget.removeLayer(*this); }

		Layer& layer() { return mLayer; }
		InkTarget& target() { return mTarget; }
		size_t index() { return mIndex; }
		void setIndex(size_t index) { mIndex = index; this->moved(index); }

		void moveToTop() { mTarget.moveToTop(*this); }

		virtual unique_ptr<Inkbox> createInkbox(Frame& frame) = 0;

		virtual void moved(size_t index) { UNUSED(index); }
		virtual void show() = 0;
		virtual void hide() = 0;

		static Type& cls() { static Type ty; return ty; }

	protected:
		Layer& mLayer;
		InkTarget& mTarget;
		size_t mIndex;
	};

	class MK_UI_EXPORT Inkbox : public NonCopy
	{
	public:
		Inkbox(Frame& frame) : mFrame(frame), mVisible(frame.visible()), mSelectFirst(0), mSelectSecond(0) {}
		virtual ~Inkbox() {}

		Frame& frame() { return mFrame; }
		bool visible() { return mVisible; }
		size_t selectStart() { return mSelectFirst < mSelectSecond ? mSelectFirst : mSelectSecond; }
		size_t selectEnd() { return mSelectSecond > mSelectFirst ? mSelectSecond : mSelectFirst; }

		inline InkStyle& skin() { return mFrame.inkstyle(); }

		virtual void show() = 0;
		virtual void hide() = 0;

		virtual void updateContent() = 0;
		virtual void updateStyle() = 0;
		virtual void updateFrame() = 0;

		void selectCaret(size_t index) { mSelectFirst = index; mSelectSecond = index; }
		void selectFirst(size_t start) { mSelectFirst = start; mSelectSecond = start; }
		void selectSecond(size_t end) { mSelectSecond = end; }

		virtual float contentSize(Dimension dim) = 0;
		virtual size_t caretIndex(float x, float y) = 0;
		virtual void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight) = 0;

	protected:
		Frame& mFrame;
		bool mVisible;
		size_t mSelectFirst;
		size_t mSelectSecond;
	};
}

#endif
