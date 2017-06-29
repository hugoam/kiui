//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIRECTORY_H
#define TOY_DIRECTORY_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/Tree.h>

struct dirent;

namespace toy
{
	class _refl_ TOY_UI_EXPORT Dir : public MultiButton
	{
	public:
		Dir(Wedge& parent, Directory& directory, const string& name);

		void open();

		static Type& cls() { static Type ty("Dir", MultiButton::cls()); return ty; }

	protected:
		Directory& m_directory;
		string m_name;
	};

	class _refl_ TOY_UI_EXPORT File : public MultiButton
	{
	public:
		File(Wedge& parent, Directory& directory, const string& name);

		static Type& cls() { static Type ty("File", MultiButton::cls()); return ty; }

	protected:
		Directory& m_directory;
		string m_name;
	};

	class _refl_ TOY_UI_EXPORT Directory : public Wedge
	{
	public:
		Directory(Wedge& parent, const string& path);

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

		static Type& cls() { static Type ty("Directory", Wedge::cls()); return ty; }

	protected:
		string m_path;
	};

	class _refl_ TOY_UI_EXPORT FileBrowser : public Wedge
	{
	public:
		FileBrowser(Wedge& parent, const string& path);

		static Type& cls() { static Type ty("FileBrowser", Wedge::cls()); return ty; }

	protected:
		string m_path;
		Directory m_directory;
	};

	class _refl_ TOY_UI_EXPORT FileNode : public TreeNode
	{
	public:
		FileNode(Wedge& parent, const string& name);

		static Type& cls() { static Type ty("FileNode", TreeNode::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT DirectoryNode : public TreeNode
	{
	public:
		DirectoryNode(Wedge& parent, const string& path, const string& name, bool collapsed);

		void expand();
		void update();

		static Type& cls() { static Type ty("DirectoryNode", TreeNode::cls()); return ty; }

	protected:
		string m_path;
	};


}

#endif
