//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WDIRECTORY_H
#define TOY_WDIRECTORY_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/Tree.h>

struct dirent;

namespace toy
{
	class _I_ TOY_UI_EXPORT Dir : public WrapButton
	{
	public:
		Dir(Piece& parent, Directory& directory, const string& name);

		void click();

		static Type& cls() { static Type ty("Dir", WrapButton::cls()); return ty; }

	protected:
		Directory& m_directory;
		string m_name;

		Icon m_icon;
		Label m_label;
	};

	class _I_ TOY_UI_EXPORT File : public WrapButton
	{
	public:
		File(Piece& parent, Directory& directory, const string& name);

		void click();

		static Type& cls() { static Type ty("File", WrapButton::cls()); return ty; }

	protected:
		Directory& m_directory;
		string m_name;

		Icon m_icon;
		Label m_label;
	};

	class _I_ TOY_UI_EXPORT Directory : public Container
	{
	public:
		Directory(Piece& parent, const string& path);

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

		static Type& cls() { static Type ty("Directory", Container::cls()); return ty; }

	protected:
		string m_path;
	};

	class _I_ TOY_UI_EXPORT FileBrowser : public Piece
	{
	public:
		FileBrowser(Piece& parent, const string& path);

		static Type& cls() { static Type ty("FileBrowser", Piece::cls()); return ty; }

	protected:
		string m_path;
		Directory m_directory;
	};

	class _I_ TOY_UI_EXPORT FileNode : public TreeNode
	{
	public:
		FileNode(Piece& parent, const string& name);

		static Type& cls() { static Type ty("FileNode", TreeNode::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT DirectoryNode : public TreeNode
	{
	public:
		DirectoryNode(Piece& parent, const string& path, const string& name, bool collapsed);

		void expand();
		void update();

		static Type& cls() { static Type ty("DirectoryNode", TreeNode::cls()); return ty; }

	protected:
		string m_path;
	};


}

#endif
