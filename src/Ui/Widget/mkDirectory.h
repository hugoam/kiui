//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDIRECTORY_H
#define MK_WDIRECTORY_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkTree.h>

struct dirent;

namespace mk
{
	class MK_UI_EXPORT _I_ Dir : public WrapButton
	{
	public:
		Dir(const string& name);

		void trigger();

		static StyleType& cls() { static StyleType ty("Dir", WrapButton::cls()); return ty; }

	protected:
		string m_name;
	};

	class MK_UI_EXPORT _I_ File : public WrapButton
	{
	public:
		File(const string& name);

		void trigger();

		static StyleType& cls() { static StyleType ty("File", WrapButton::cls()); return ty; }

	protected:
		string m_name;
	};

	class MK_UI_EXPORT _I_ Directory : public ScrollSheet
	{
	public:
		Directory(const string& path);

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

		static StyleType& cls() { static StyleType ty("Directory", ScrollSheet::cls()); return ty; }

	protected:
		string m_path;
	};

	class MK_UI_EXPORT _I_ FileBrowser : public Sheet
	{
	public:
		FileBrowser(const string& path);

		static StyleType& cls() { static StyleType ty("FileBrowser", Sheet::cls()); return ty; }

	protected:
		string m_path;
		Directory& m_directory;
	};

	class MK_UI_EXPORT _I_ FileNode : public TreeNode
	{
	public:
		FileNode(const string& name);

		static StyleType& cls() { static StyleType ty("FileNode", TreeNode::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ DirectoryNode : public TreeNode
	{
	public:
		DirectoryNode(const string& path, const string& name, bool collapsed);

		void expand();
		void update();

		static StyleType& cls() { static StyleType ty("DirectoryNode", TreeNode::cls()); return ty; }

	protected:
		string m_path;
	};


}

#endif
