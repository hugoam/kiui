//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Directory.h>

#include <toyui/Button/Button.h>

#include <dirent.h>

namespace toy
{
	Dir::Dir(Wedge& parent, Directory& directory, const string& name)
		: MultiButton(parent, nullptr, { "folder_20" , name }, cls())
		, m_directory(directory)
		, m_name(name)
	{}

	void Dir::click()
	{
		if(m_name == ".")
			return;
		if(m_name == "..")
			m_directory.moveOut();
		else
			m_directory.moveIn(m_name);
			
	}

	File::File(Wedge& parent, Directory& directory, const string& name)
		: MultiButton(parent, nullptr, { "file_20", name }, cls())
		, m_directory(directory)
		, m_name(name)
	{}

	void File::click()
	{}

	Directory::Directory(Wedge& parent, const string& path)
		: Container(parent, cls())
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

	FileBrowser::FileBrowser(Wedge& parent, const string& path)
		: Wedge(parent, cls())
		, m_path(path)
		, m_directory(*this, m_path)
	{}

	FileNode::FileNode(Wedge& parent, const string& name)
		: TreeNode(parent, "file_20", name, true, cls())
	{}

	DirectoryNode::DirectoryNode(Wedge& parent, const string& path, const string& name, bool collapsed)
		: TreeNode(parent, "folder_20", name, collapsed, cls())
		, m_path(path)
	{}

	void DirectoryNode::expand()
	{
		Expandbox::expand();

		for(auto& pt : m_container.contents())
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
