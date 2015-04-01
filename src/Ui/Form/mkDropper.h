//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DROPPER_H_INCLUDED
#define MK_DROPPER_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT Dropper
	{
	public:
		Dropper();

		virtual Form* swapdrop(Form* form, Dropper* source) = 0;
		virtual bool candrop(Form* form, Dropper* source) = 0;
		virtual void dropin(Form* form, Dropper* source, size_t index) = 0;
		virtual void dropout(Form* form, Dropper* source) = 0;

		void drop(Form* form, size_t position);

	protected:
		Form* mForm;
	};
}

#endif // MK_DROPPER_H_INCLUDED
