//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SCHEME_H_INCLUDED
#define MK_SCHEME_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>

#include <functional>
#include <memory>

namespace mk
{
	typedef std::function<unique_ptr<Widget>()> SchemeMapper;

	class Scheme
	{
	public:
		Scheme(Form* form, SchemeMapper mapper);

		Form* form() { return mForm; }

		unique_ptr<Widget> makeWidget();

		void append(Form* form);
		void remove(Form* form);

		void reset(SchemeMapper mapper);
		void apply();
		void clear();

		void setMapper(SchemeMapper mapper) { mMapper = mapper; }
		void setSheet(Sheet* sheet) { mSheet = sheet; }
		void setCollection(Collection* collection) { mCollection = collection; }
		Collection* collection() { return mCollection; }

	protected:
		Form* mForm;
		Sheet* mSheet;
		
		SchemeMapper mMapper;

		Collection* mCollection;
	};
}

#endif // MK_SCHEME_H_INCLUDED
