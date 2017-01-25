#ifndef TOY_DUIEDIT_H
#define TOY_DUIEDIT_H

/* EditorApp */
#include <toyobj/Iterable/StoreObserver.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Controller/Controller.h>

/* std */
#include <functional>

namespace toy
{
	/*class TOY_EDIT_EXPORT FImageSkinEdit : public Form
	{
	public:
		FImageSkinEdit();

		void loadImage();
		void saveSkin();

		static StyleType& cls() { static StyleType ty("FImageSkinEdit"); return ty; }

	protected:
		Form* mVisual;
		InputFloat* mInLeft;
		InputFloat* mInRight;
		InputFloat* mInTop;
		InputFloat* mInBottom;
		Button* mOpen;
		Button* mSave;
	};*/

	class TOY_UI_EXPORT DUiEdit : public Device
	{
	public:
		DUiEdit(Device& parent);

		void selectWidget(Widget& widget);
		//void selectDevice(Device& device);

		static DeviceType& cls() { static DeviceType ty("DUiEdit", Device::cls()); return ty; }

	protected:
		DEdit& m_widgetEdit;
		DEdit& m_styleEdit;
		DEdit& m_skinEdit;

		DStructure& m_structure;

		Widget* m_widget;
	};

	class TOY_UI_EXPORT DUiEditor : public Device//, public Controller
	{
	public:
		DUiEditor(Device& parent);
		~DUiEditor();

		bool leftClick(float xPos, float yPos);
		bool rightClick(float xPos, float yPos);

		void selectWidget(Widget& widget);
		void selectDevice(Device& device);

		void editorMode();
		void interactMode();

		static DeviceType& cls() { static DeviceType ty("DUiEditor", Device::cls()); return ty; }

	protected:
		Device& m_toolbar;
		DStructure& m_widgetStructure;
		DStructure& m_deviceStructure;

		DUiEdit& m_uiEdit;

		Sheet* m_edited;
		Device* m_selectedDevice;
		Widget* m_selectedWidget;

		//UiDummy* mSelectionDummy;

		bool m_editorMode;
	};
}
#endif // TOY_DUIEDIT_H
