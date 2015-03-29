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
		this->makeappend<WIcon>("folder_20.png");
		this->makeappend<WLabel>(mName);
	}

	void WDir::trigger()
	{
		if(mName == ".")
			return;
		if(mName == "..")
			mParent->parent()->as<WDirectory>()->moveOut();
		else
			mParent->parent()->as<WDirectory>()->moveIn(mName);
			
	}

	WFile::WFile(const string& name)
		: WWrapButton(nullptr, styleCls())
		, mName(name)
	{}

	void WFile::build()
	{
		this->makeappend<WIcon>("file_20.png");
		this->makeappend<WLabel>(mName);
	}

	void WFile::trigger()
	{}

	WDirectory::WDirectory(const string& path)
		: ScrollSheet(styleCls())
		, mPath(path)
	{
		char buffer[PATH_MAX];
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
			if(ent->d_type & DT_DIR && string(ent->d_name) != ".")
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

	WFileBrowser::WFileBrowser(const string& path)
		: Sheet(styleCls())
		, mPath(path)
	{}

	void WFileBrowser::build()
	{
		mDirectory = this->makeappend<WDirectory>(mPath);
	}

	WFileNode::WFileNode(const string& name)
		: WTreeNode(nullptr, "file_20.png", name, true)
	{}

	WDirectoryNode::WDirectoryNode(const string& path, const string& name, bool collapsed)
		: WTreeNode(nullptr, "folder_20.png", name, collapsed)
		, mPath(path)
	{}

	void WDirectoryNode::build()
	{
		WTreeNode::build();

		if(mParent->type() != WDirectoryNode::cls() || !mParent->as<WDirectoryNode>()->mCollapsed)
			this->update();
	}

	void WDirectoryNode::update()
	{
		DIR* dir = opendir(mPath.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
				this->vmakeappend<WDirectoryNode>(mPath + "/" + ent->d_name, ent->d_name, true);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->vmakeappend<WFileNode>(ent->d_name);

		closedir(dir);
	}
}
