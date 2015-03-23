//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDIRECTORY_H
#define MK_WDIRECTORY_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>

struct dirent;

namespace mk
{
	class MK_UI_EXPORT _I_ WDir : public WWrapButton, public Typed<WDir>, public Styled<WDir>
	{
	public:
		WDir(const string& name);

		void build();

		void trigger();

		using Typed<WDir>::cls;

	protected:
		string mName;
	};

	class MK_UI_EXPORT _I_ WFile : public WWrapButton, public Typed<WFile>, public Styled<WFile>
	{
	public:
		WFile(const string& name);

		void build();

		void trigger();

		using Typed<WFile>::cls;

	protected:
		string mName;
	};

	class MK_UI_EXPORT _I_ WDirectory : public ScrollSheet, public Typed<WDirectory>, public Styled<WDirectory>
	{
	public:
		WDirectory(const string& path);

		void build();

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

		using Typed<WDirectory>::cls;

	protected:
		string mPath;
	};
}

#endif
