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
		: WrapButton(nullptr)
		, mName(name)
	{
		mStyle = &cls();
		this->makeappend<Icon>("folder_20");
		this->makeappend<Label>(mName);
	}

	void Dir::trigger()
	{
		if(mName == ".")
			return;
		if(mName == "..")
			mParent->as<Directory>().moveOut();
		else
			mParent->as<Directory>().moveIn(mName);
			
	}

	File::File(const string& name)
		: WrapButton(nullptr)
		, mName(name)
	{
		mStyle = &cls();
		this->makeappend<Icon>("file_20");
		this->makeappend<Label>(mName);
	}

	void File::trigger()
	{}

	Directory::Directory(const string& path)
		: ScrollSheet()
		, mPath(path)
	{
		mStyle = &cls();
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
		this->clear();
		this->update();
	}

	void Directory::moveIn(const string& subdir)
	{
		this->setLocation(mPath + "/" + subdir);
	}

	void Directory::moveOut()
	{
		size_t pos = mPath.rfind("/");
		this->setLocation(mPath.substr(0, pos));
	}

	FileBrowser::FileBrowser(const string& path)
		: Sheet()
		, mPath(path)
		, mDirectory(this->makeappend<Directory>(mPath))
	{
		mStyle = &cls();
	}

	FileNode::FileNode(const string& name)
		: TreeNode("file_20", name, true)
	{
		mStyle = &cls();
	}

	DirectoryNode::DirectoryNode(const string& path, const string& name, bool collapsed)
		: TreeNode("folder_20", name, collapsed)
		, mPath(path)
	{
		mStyle = &cls();
		mType = &cls();
	}

	void DirectoryNode::expand()
	{
		Expandbox::expand();

		for(auto& pt : mContainer->contents())
			if(&pt->type() == &DirectoryNode::cls())
				pt->as<DirectoryNode>().update();
	}

	void DirectoryNode::update()
	{
		DIR* dir = opendir(mPath.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
			{
				DirectoryNode& node = this->emplace<DirectoryNode>(mPath + "/" + ent->d_name, ent->d_name, true);
				if(!mCollapsed)
					node.update();
			}

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->emplace<FileNode>(ent->d_name);

		closedir(dir);
	}
}
