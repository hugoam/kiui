//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Directory.h>

#include <toyui/Button/Button.h>

#include <dirent.h>

namespace toy
{
	Dir::Dir(const Params& params, Directory& directory, const string& name)
		: MultiButton({ params, &cls<Dir>() }, { "(folder_20)" , name }, [&](Widget&) { this->open(); })
		, m_directory(directory)
		, m_name(name)
	{}

	void Dir::open()
	{
		if(m_name == ".")
			return;
		if(m_name == "..")
			m_directory.moveOut();
		else
			m_directory.moveIn(m_name);
			
	}

	File::File(const Params& params, Directory& directory, const string& name)
		: MultiButton({ params, &cls<File>() }, { "(file_20)", name }, nullptr)
		, m_directory(directory)
		, m_name(name)
	{}

	Directory::Directory(const Params& params, const string& path)
		: Wedge({ params, &cls<Directory>() })
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
		this->store().clear();
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

	FileBrowser::FileBrowser(const Params& params, const string& path)
		: Wedge({ params, &cls<FileBrowser>() })
		, m_path(path)
		, m_directory({ this }, m_path)
	{}

	FileNode::FileNode(const Params& params, const string& name)
		: TreeNode({ params, &cls<FileNode>() }, { "(file_20)", name }, true, nullptr, nullptr)
	{
		m_toggle.enableState(DISABLED);
	}

	DirectoryNode::DirectoryNode(const Params& params, const string& path, const string& name, bool collapsed)
		: TreeNode({ params, &cls<DirectoryNode>() }, { "(folder_20)", name }, collapsed, nullptr, nullptr)
		, m_path(path)
	{}

	void DirectoryNode::expand()
	{
		Expandbox::expand();

		for(Widget* widget : m_body.m_contents)
			if(is<DirectoryNode>(*widget))
				as<DirectoryNode>(*widget).update();
	}

	void DirectoryNode::update()
	{
		DIR* dir = opendir(m_path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..")
			{
				DirectoryNode& node = m_body.emplace<DirectoryNode>(m_path + "/" + ent->d_name, ent->d_name, true);
				if(!m_collapsed)
					node.update();
			}

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				m_body.emplace<FileNode>(ent->d_name);

		closedir(dir);
	}
}
