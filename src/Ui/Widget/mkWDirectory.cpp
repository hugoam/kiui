//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWDirectory.h>

#include <Ui/Widget/mkWButton.h>

#include <dirent.h>

#include <iostream>

namespace mk
{
	WDir::WDir(const string& name)
		: WWrapButton(nullptr, styleCls())
		, mName(name)
	{}

	void WDir::build()
	{
		this->makeappend<WIcon>("dir");
		this->makeappend<WLabel>(mName);
	}

	void WDir::trigger()
	{
		if(mName != "..")
			mParent->parent()->as<WDirectory>()->moveIn(mName);
		else
			mParent->parent()->as<WDirectory>()->moveOut();
	}

	WFile::WFile(const string& name)
		: WWrapButton(nullptr, styleCls())
		, mName(name)
	{}

	void WFile::build()
	{
		this->makeappend<WIcon>("file");
		this->makeappend<WLabel>(mName);
	}

	void WFile::trigger()
	{}

	WDirectory::WDirectory(const string& path)
		: ScrollSheet(styleCls())
		, mPath(path)
	{
		mPath = replaceAll(mPath, "/", "\\");
	}

	void WDirectory::build()
	{
		ScrollSheet::build();

		this->update();
	}

	void WDirectory::update()
	{
		DIR* dir = opendir(mPath.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR)
				this->vmakeappend<WDir>(ent->d_name);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->vmakeappend<WFile>(ent->d_name);

		closedir(dir);
	}

	void WDirectory::setLocation(const string& path)
	{
		mPath = path;
		mSheet->clear();
		this->update();
	}

	void WDirectory::moveIn(const string& subdir)
	{
		this->setLocation(mPath + "\\" + subdir);
	}

	void WDirectory::moveOut()
	{
		size_t pos = mPath.rfind("\\");
		this->setLocation(mPath.substr(0, pos));
	}
}
