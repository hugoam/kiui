//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkDirectory.h>

#include <Ui/Widget/mkButton.h>

#include <dirent.h>

#include <iostream>

namespace mk
{
	Dir::Dir(const string& name)
		: WrapButton(nullptr, styleCls())
		, mName(name)
	{
		this->makeappend<Icon>("folder_20.png");
		this->makeappend<Label>(mName);
	}

	void Dir::trigger()
	{
		if(mName == ".")
			return;
		if(mName == "..")
			mParent->parent()->as<Directory>()->moveOut();
		else
			mParent->parent()->as<Directory>()->moveIn(mName);
			
	}

	File::File(const string& name)
		: WrapButton(nullptr, styleCls())
		, mName(name)
	{
		this->makeappend<Icon>("file_20.png");
		this->makeappend<Label>(mName);
	}

	void File::trigger()
	{}

	Directory::Directory(const string& path)
		: ScrollSheet(styleCls())
		, mPath(path)
	{
		char buffer[PATH_MAX];
		mPath = replaceAll(mPath, "/", "\\");

		this->update();
	}

	void Directory::update()
	{
		DIR* dir = opendir(mPath.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != ".")
				this->emplace<Dir>(ent->d_name);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->emplace<File>(ent->d_name);

		closedir(dir);
	}

	void Directory::setLocation(const string& path)
	{
		mPath = path;
		mSheet->clear();
		this->update();
	}

	void Directory::moveIn(const string& subdir)
	{
		this->setLocation(mPath + "\\" + subdir);
	}

	void Directory::moveOut()
	{
		size_t pos = mPath.rfind("\\");
		this->setLocation(mPath.substr(0, pos));
	}

	FileBrowser::FileBrowser(const string& path)
		: Sheet(styleCls())
		, mPath(path)
	{
		mDirectory = this->makeappend<Directory>(mPath);
	}

	FileNode::FileNode(const string& name)
		: TreeNode("file_20.png", name, true)
	{}

	DirectoryNode::DirectoryNode(const string& path, const string& name, bool collapsed, bool load)
		: TreeNode("folder_20.png", name, collapsed)
		, mPath(path)
	{
		if(load)
			this->update();
	}

	void DirectoryNode::update()
	{
		DIR* dir = opendir(mPath.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
				this->emplace<DirectoryNode>(mPath + "/" + ent->d_name, ent->d_name, true, !mCollapsed);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->emplace<FileNode>(ent->d_name);

		closedir(dir);
	}
}
