//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Directory.h>

#include <toyui/Widget/Button.h>

#include <dirent.h>

namespace toy
{
	Dir::Dir(Directory& directory, const string& name)
		: WrapButton(nullptr, Trigger(), cls())
		, m_directory(directory)
		, m_name(name)
	{
		this->makeappend<Icon>("folder_20");
		this->makeappend<Label>(m_name);
	}

	void Dir::trigger()
	{
		if(m_name == ".")
			return;
		if(m_name == "..")
			m_directory.moveOut();
		else
			m_directory.moveIn(m_name);
			
	}

	File::File(Directory& directory, const string& name)
		: WrapButton(nullptr, Trigger(), cls())
		, m_directory(directory)
		, m_name(name)
	{
		this->makeappend<Icon>("file_20");
		this->makeappend<Label>(m_name);
	}

	void File::trigger()
	{}

	Directory::Directory(const string& path)
		: Sheet(cls())
		, m_path(path)
	{
		this->update();
	}

	void Directory::update()
	{
		DIR* dir = opendir(m_path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != ".")
				this->emplace<Dir>(*this, ent->d_name);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->emplace<File>(*this, ent->d_name);

		closedir(dir);
	}

	void Directory::setLocation(const string& path)
	{
		m_path = path;
		this->clear();
		this->update();
	}

	void Directory::moveIn(const string& subdir)
	{
		this->setLocation(m_path + "/" + subdir);
	}

	void Directory::moveOut()
	{
		size_t pos = m_path.rfind("/");
		this->setLocation(m_path.substr(0, pos));
	}

	FileBrowser::FileBrowser(const string& path)
		: Sheet(cls())
		, m_path(path)
		, m_directory(this->makeappend<Directory>(m_path))
	{}

	FileNode::FileNode(const string& name)
		: TreeNode("file_20", name, true, cls())
	{}

	DirectoryNode::DirectoryNode(const string& path, const string& name, bool collapsed)
		: TreeNode("folder_20", name, collapsed, cls())
		, m_path(path)
	{}

	void DirectoryNode::expand()
	{
		Expandbox::expand();

		for(auto& pt : m_container->contents())
			if(&pt->type() == &DirectoryNode::cls())
				pt->as<DirectoryNode>().update();
	}

	void DirectoryNode::update()
	{
		DIR* dir = opendir(m_path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
			{
				DirectoryNode& node = this->emplace<DirectoryNode>(m_path + "/" + ent->d_name, ent->d_name, true);
				if(!m_collapsed)
					node.update();
			}

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				this->emplace<FileNode>(ent->d_name);

		closedir(dir);
	}
}
