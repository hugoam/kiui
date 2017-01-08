#include <Ui/mkUiConfig.h>
#include <Ui/Edit/mkDUiEdit.h>

#include <Ui/Edit/mkDObjectEdit.h>
#include <Ui/Edit/mkDStructure.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Scheme/mkExpandbox.h>
#include <Ui/Scheme/mkTree.h>

#include <Ui/Widget/mkDirectory.h>

#include <Ui/Widget/mkButton.h>
#include <Ui/Widget/mkInput.h>

#include <Ui/Device/mkRootDevice.h>

using namespace std::placeholders;

namespace mk
{
	DUiEdit::DUiEdit(Device& parent)
		: Device(parent, cls())
		, m_widgetEdit(this->emplace<DEdit>())
		, m_styleEdit(this->emplace<DEdit>())
		, m_skinEdit(this->emplace<DEdit>())
		, m_structure(this->emplace<DStructure>())
		, m_widget(nullptr)
	{}

	void DUiEdit::selectWidget(Widget& widget)
	{
		m_widgetEdit.edit(widget, Widget::cls());
		m_styleEdit.edit(widget.style().layout(), LayoutStyle::cls());
		m_skinEdit.edit(widget.style().skin(), InkStyle::cls());
		m_structure.setRoot(widget, Widget::cls());
		m_widget = &widget;
	}

	DUiEditor::DUiEditor(Device& parent)
		: Device(parent, cls())
		, m_toolbar(this->emplace<Device>(Device::cls()))
		, m_widgetStructure(this->emplace<DStructure>())
		, m_deviceStructure(this->emplace<DStructure>())
		, m_uiEdit(this->emplace<DUiEdit>())
		, m_selectedDevice(nullptr)
		, m_selectedWidget(nullptr)
		, m_editorMode(true)
	{
		//m_widgetStructure.picker(std::bind(&DUiEditor::selectWidget, this, _1));
		//m_widgetStructure.picker(std::bind(&DUiEditor::selectDevice, this, _1));

		//m_widget->rootSheet().stackControl(this);

		//m_selectionDummy = &m_sheet.emplace<UiDummy>();

		//m_editor->toolbox().tools().add(make_unique<EditorModeTool>(*mEditor.get(), this));
		//m_editor->toolbox().tools().add(make_unique<InteractModeTool>(*mEditor.get(), this));
	}

	DUiEditor::~DUiEditor()
	{}

	bool DUiEditor::leftClick(float xPos, float yPos)
	{
		Widget& widget = *this->uiWindow().rootSheet().pinpoint(xPos, yPos);

		if(!m_editorMode || !m_edited->contains(widget))
			return false;

		//if(widget->form())
		//	this->selectForm(widget->form());
		//else
		this->selectWidget(widget);

		return true;
	}

	bool DUiEditor::rightClick(float xPos, float yPos)
	{
		Widget& widget = *this->uiWindow().rootSheet().pinpoint(xPos, yPos);

		if(!m_editorMode || !m_edited->contains(widget))
			return false;

		//FUiContext& context = this->emplace<FUiContext>(widget);
		return true;
	}

	void DUiEditor::selectDevice(Device& device)
	{
		if(m_selectedDevice == &device)
			return;

		m_selectedDevice = &device;
		//mFormView->container()->as<Tree>().select(form);

		this->selectWidget(device.sheet());
	}

	void DUiEditor::selectWidget(Widget& widget)
	{
		m_uiEdit.selectWidget(widget);
	}

	void DUiEditor::editorMode()
	{
		m_editorMode = true;
	}

	void DUiEditor::interactMode()
	{
		m_editorMode = false;
	}

	/*FImageSkinEdit::FImageSkinEdit()
		: Form(make_unique<Page>("ImageSkin Editor", "0.1.0"))
	{
		mVisual;
		mInLeft = &mSheet.emplace<InputFloat>("Left Width", 0.f);
		mInRight = &mSheet.emplace<InputFloat>("Right Width", 0.f);
		mInTop = &mSheet.emplace<InputFloat>("Top Width", 0.f);
		mInBottom = &mSheet.emplace<InputFloat>("Bottom Width", 0.f);
		mOpen = &mSheet.emplace<Button>("Open Image", std::bind(&FImageSkinEdit::loadImage, this));
		mSave = &mSheet.emplace<Button>("Save Skin", std::bind(&FImageSkinEdit::saveSkin, this));
	}

	void FImageSkinEdit::loadImage()
	{
		Window* window = &mSheet.rootSheet().emplace<Window>("Load Image");
		window->emplace<Directory>("../Data/interface");
	}

	void FImageSkinEdit::saveSkin()
	{
	
	}*/
}
