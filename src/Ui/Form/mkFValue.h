//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FVALUE_H_INCLUDED
#define MK_FVALUE_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
#include <Object/mkObjectForward.h>
#include <Ui/Form/mkForm.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT ValueForm : public HashDispatch<ValueForm, Form*, Form*>
	{};

	class MK_UI_EXPORT FValue : public Form
	{
	public:
		FValue(Lref& lref, const string& cls, bool edit = false);
		FValue(Lref&& lref, const string& cls, bool edit = false);

		void nextFrame(size_t tick, size_t delta);

		Lref& valref() { return mLref; }

		string toString();
		void setString(const string& value);

		virtual void updateValue();

	protected:
		Lref mValue;
		Lref& mLref;
		int mUpdate;
		bool mEdit;
	};

	class MK_UI_EXPORT FInt : public FValue, public Typed<FInt>
	{
	public:
		FInt(Lref& value, bool edit = true);
		FInt(int value);

		void updateValue();

		using Typed<FInt>::cls;
	};

	class MK_UI_EXPORT FFloat : public FValue, public Typed<FFloat>
	{
	public:
		FFloat(Lref& value, bool edit = true);
		FFloat(float value);

		void updateValue();

		using Typed<FFloat>::cls;
	};

	class MK_UI_EXPORT FIntStat : public FValue, public Typed<FIntStat>
	{
	public:
		FIntStat(Lref& value, bool edit = true);
		FIntStat(Stat<int> value);

		using Typed<FIntStat>::cls;
	};

	class MK_UI_EXPORT FFloatStat : public FValue, public Typed<FFloatStat>
	{
	public:
		FFloatStat(Lref& value, bool edit = true);
		FFloatStat(Stat<float> value);

		using Typed<FFloatStat>::cls;
	};

	class MK_UI_EXPORT FBool : public FValue, public Typed<FBool>
	{
	public:
		FBool(Lref& value, bool edit = true);
		FBool(bool value);

		using Typed<FBool>::cls;
	};

	class MK_UI_EXPORT FString : public FValue, public Typed<FString>
	{
	public:
		FString(Lref& value, bool edit = true);
		FString(string value);

		using Typed<FString>::cls;
	};

	class MK_UI_EXPORT InputInt : public Form
	{
	public:
		InputInt(const string& label, int value); //, IntCallback callback);
	};

	class MK_UI_EXPORT InputFloat : public Form
	{
	public:
		InputFloat(const string& label, float value); //, FloatCallback callback);
	};

	class MK_UI_EXPORT InputBool : public Form
	{
	public:
		InputBool(const string& label, bool value);
	};

	class MK_UI_EXPORT InputText : public Form
	{
	public:
		InputText(const string& label, const string& text);
	};
	
	class MK_UI_EXPORT SliderInt : public Form
	{
	public:
		SliderInt(const string& label, Stat<int> value); //, IntCallback callback);
	};

	class MK_UI_EXPORT SliderFloat : public Form
	{
	public:
		SliderFloat(const string& label, Stat<float> value); //, FloatCallback callback);
	};
}

#endif // MK_FOBJECT_H_INCLUDED
