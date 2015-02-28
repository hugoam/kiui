//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WSLIDER_H
#define MK_WSLIDER_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkWButton.h>

namespace mk
{
	class MK_UI_EXPORT WSlideButton : public WButton 
	{
	public:
		WSlideButton(string clas, Dimension dim = DIM_X);

		float offset(float pos);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

	protected:
		Dimension mDim;
		float mStartPos;
		float mStartOffset;
	};

	class MK_UI_EXPORT WSlider : public Sheet
	{
	public:
		WSlider(Dimension dim = DIM_X, string clas = "", Trigger onUpdated = nullptr);

		void build();

		Widget* spaceBefore() { return mSpaceBefore; }
		WSlideButton* slider() { return mButton; }
		Widget* spaceAfter() { return mSpaceAfter; }

		float val() { return mVal; }

		string clas() { return mDim == DIM_X ? "xslider" : "yslider"; }

		void updateMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetValue(float val);

		void offsetChange(float offset, bool ended);
		
		void updateKnob();

		virtual void sliderStep(float value, bool ended) { UNUSED(value); UNUSED(ended); mOnUpdated(this); }

	protected:
		Dimension mDim;
		Widget* mSpaceBefore;
		WSlideButton* mButton;
		Widget* mSpaceAfter;

		float mMin;
		float mMax;
		float mVal;
		float mStepLength;
		float mKnobLength;

		float mNumSteps;
		int mStep;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT WStatSlider : public Sheet
	{
	public:
		WStatSlider(Form* form, Lref& stat, Dimension dim = DIM_X);

		void build();

		void onUpdate();

		virtual void updateValue() = 0;
		virtual void updateSlider() = 0;

	protected:
		Lref& mStat;
		Dimension mDim;
		WSlider* mSlider;
		WLabel* mDisplay;
	};

	class MK_UI_EXPORT WIntSlider : public WStatSlider
	{
	public:
		WIntSlider(FIntStat* form);

		int value(float offset);

		void updateSlider();
		void updateValue();
	};

	class MK_UI_EXPORT WFloatSlider : public WStatSlider
	{
	public:
		WFloatSlider(FFloatStat* form);

		float value(float offset);

		void updateSlider();
		void updateValue();
	};
}

#endif
