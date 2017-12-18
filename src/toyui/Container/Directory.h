//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIRECTORY_H
#define TOY_DIRECTORY_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/Tree.h>

struct dirent;

namespace toy
{
	class _refl_ TOY_UI_EXPORT Dir : public MultiButton
	{
	public:
		Dir(const Params& params, Directory& directory, const string& name);

		void open();

	protected:
		Directory& m_directory;
		string m_name;
	};

	class _refl_ TOY_UI_EXPORT File : public MultiButton
	{
	public:
		File(const Params& params, Directory& directory, const string& name);

	protected:
		Directory& m_directory;
		string m_name;
	};

	class _refl_ TOY_UI_EXPORT Directory : public Wedge
	{
	public:
		Directory(const Params& params, const string& path);

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

	protected:
		string m_path;
	};

	class _refl_ TOY_UI_EXPORT FileBrowser : public Wedge
	{
	public:
		FileBrowser(const Params& params, const string& path);

	protected:
		string m_path;
		Directory m_directory;
	};

	class _refl_ TOY_UI_EXPORT FileNode : public TreeNode
	{
	public:
		FileNode(const Params& params, const string& name);
	};

	class _refl_ TOY_UI_EXPORT DirectoryNode : public TreeNode
	{
	public:
		DirectoryNode(const Params& params, const string& path, const string& name, bool collapsed);

		void expand();
		void update();

	protected:
		string m_path;
	};


}

#endif
