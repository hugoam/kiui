//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UILAYOUT_H
#define MK_UILAYOUT_H

/* mk Front */
#include <Ui/mkUiForward.h>
#include <Object/Store/mkRegistry.h>
#include <Object/Store/mkArray.h>
#include <Object/Util/mkColour.h>
#include <Object/String/mkString.h>

/* standard */
#include <map>

namespace mk
{
	class MK_UI_EXPORT UiSkinner
	{
	public:
		UiSkinner();

		void add(string name);
		void add(string name, Colour colour);
		void add(string name, string base);
		void add(StringVector names, string base);

		void addOverride(string stem, string name, string skin);
		bool hasOverrides(string stem);

		InkStyle* skin(string name);

		InkStyle* elementSkin(string clas, string overrider);

	protected:
		Named<Registry<InkStyle>> mSkins;
		std::map<string, std::vector<string>> mOverrides;
	};

	class MK_UI_EXPORT UiLayout
	{
	public:
		UiLayout();

		void add(string name);
		void add(string name, string base);
		void add(StringVector names, string base);

		void addOverride(string stem, string name, string skin);
		bool hasOverrides(string stem);

		LayoutStyle* style(string name);

		LayoutStyle* elementStyle(string clas, string overrider);

	protected:
		Named<Registry<LayoutStyle>> mLayoutStyles;
		std::map<string, std::vector<string>> mOverrides;
	};

	void setupUiLayout(UiSkinner* skinner, UiLayout* layout);
}

#endif
