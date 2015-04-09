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
	class MK_UI_EXPORT _I_ Dir : public WrapButton, public Typed<Dir, Sheet>, public Styled<Dir>
	{
	public:
		Dir(const string& name);

		void trigger();

		using Typed<Dir, Sheet>::cls;

	protected:
		string mName;
	};

	class MK_UI_EXPORT _I_ File : public WrapButton, public Typed<File, Sheet>, public Styled<File>
	{
	public:
		File(const string& name);

		void trigger();

		using Typed<File, Sheet>::cls;

	protected:
		string mName;
	};

	class MK_UI_EXPORT _I_ Directory : public ScrollSheet, public Typed<Directory, Sheet>, public Styled<Directory>
	{
	public:
		Directory(const string& path);

		void update();

		void setLocation(const string& path);
		void moveIn(const string& name);
		void moveOut();

		using Typed<Directory, Sheet>::cls;
		using Styled<Directory>::styleCls;

	protected:
		string mPath;
	};

	class MK_UI_EXPORT _I_ FileBrowser : public Sheet, public Typed<FileBrowser, Sheet>, public Styled<FileBrowser>
	{
	public:
		FileBrowser(const string& path);

		using Typed<FileBrowser, Sheet>::cls;

	protected:
		string mPath;
		Directory* mDirectory;
	};

	class MK_UI_EXPORT _I_ FileNode : public TreeNode, public Typed<FileNode, TreeNode>
	{
	public:
		FileNode(const string& name);

		using Typed<FileNode, TreeNode>::cls;
	};

	class MK_UI_EXPORT _I_ DirectoryNode : public TreeNode, public Typed<DirectoryNode, TreeNode>
	{
	public:
		DirectoryNode(const string& path, const string& name, bool collapsed);

		void expand();
		void update();

		using Typed<DirectoryNode, TreeNode>::cls;

	protected:
		string mPath;
	};


}

#endif
