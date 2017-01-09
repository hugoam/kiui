//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Device/mkRootDevice.h>

#include <Object/Iterable/mkReverse.h>
#include <Object/Reflect/mkImprint.h>
#include <Object/Reflect/mkMember.h>
#include <Object/Script/mkScript.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Ui/Device/mkDevice.h>
#include <Ui/Device/mkHook.h>
#include <Ui/Device/mkStack.h>

#include <Ui/Edit/mkDValueEdit.h>
#include <Ui/Edit/mkDObjectEdit.h>
#include <Ui/Edit/mkDObjectCreate.h>
#include <Ui/Edit/mkDStructure.h>
#include <Ui/Edit/mkDMethod.h>
#include <Ui/Edit/mkDCanvas.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Widget/mkInput.h>
#include <Ui/Widget/mkWidgets.h>
#include <Ui/Widget/mkInput.h>
#include <Ui/Widget/mkContextMenu.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>
#include <Ui/Scheme/mkTable.h>
#include <Ui/Scheme/mkDockspace.h>
#include <Ui/Scheme/mkExpandbox.h>
#include <Ui/Scheme/mkRadioButton.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Scheme/mkNode.h>
#include <Ui/Scheme/mkTree.h>


namespace mk
{
	RootDevice::RootDevice(UiWindow& uiWindow, Sheet& rootSheet)
		: Device(cls(), rootSheet)
		, m_window(uiWindow)
		, m_rootSheet(rootSheet)
		, m_user(&uiWindow.user())
		, m_lastTick(0)
	{
		declareDValueEdit();
		declareDValueDisplay();
		declareDefaultMappings();

		m_sheet = &m_rootSheet;
	}

	RootDevice::~RootDevice()
	{}

	void RootDevice::nextFrame(size_t tick, size_t delta)
	{
		Device::nextFrame(tick, delta);
		m_lastTick = tick;
	}

	void RootDevice::insertionSheet(Sheet& sheet)
	{
		m_sheet = &sheet;
	}

	void RootDevice::declareDefaultMappings()
	{
		Response::cls().map()
			.mapper([](Device& device) { return make_unique<Button>(device.as<Response>().name(), [&device](Button&) { device.as<Response>().trigger(); }); });

		Hook::cls().map()
			.mapper([](Device& device) { return make_unique<Button>(device.as<Hook>().echobject().name(), [&device](Button&) { device.as<Hook>().on(); }); });

		Stack::cls().map()
			.mapper([](Device& device) { return make_unique<Sheet>(); });

		DValue::cls().map()
			.mapper([](Device& device) { Lref context;  return DispatchInput::dispatch(context, device.as<DValue>().value()); })
			.structure([](Device& device, Sheet& sheet) -> Sheet& { sheet.as<WValue>().onUpdate([&device](Lref& lref) {device.as<DValue>().handleValueChanged(); }); return sheet; });

		DEmpty::cls().map()
			.mapper([](Device& device) { return make_unique<Label>("Empty"); });

		DNone::cls().map()
			.mapper([](Device& device) { return make_unique<Label>("None"); });

		DSequence::cls().map()
			.mapper([](Device& device) { return make_unique<Expandbox>("Sequence"); });

		DLink::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); });

		DEnum::cls().map()
			.mapper([](Device& device) { return make_unique<RadioSwitch>([&device](Widget&) { device.as<DEnum>(); }, 0, device.as<DEnum>().value()->imprint().enumIds()); });

		DObjectEdit::cls().map()
			.mapper([](Device& device) { return make_unique<Sheet>(); });

		DPartEdit::cls().map()
			.mapper([](Device& device) { return make_unique<Expandbox>(device.as<DPartEdit>().objectEdit().type().imprint().name()); });

		DModularEdit::cls().map()
			.mapper([](Device& device) { return make_unique<Table>(StringVector{ "type", "value" }, std::vector<float>{ 0.4f, 0.6f }); });

		DMemberEdit::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); })
			.structure([](Device& device, Sheet& sheet) -> Sheet& { sheet.emplace<Title>(device.as<DMemberEdit>().member().member().name()); return sheet; });
		
		DCreateArg::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); })
			.structure([](Device& device, Sheet& sheet) -> Sheet& { sheet.emplace<Title>(device.as<DCreateArg>().member().name()); return sheet; });


		DStructureNode::cls().map()
			.mapper([](Device& device) { return make_unique<TreeNode>("", device.as<DStructureNode>().echobject().name()); });

		DStructure::cls().map()
			.mapper([](Device& device) { return make_unique<Tree>(); });

		DMethod::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); });

		DMethodCall::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); });

		DParam::cls().map()
			.mapper([](Device& device) { return make_unique<Band>(); });

		DScriptCanvas::cls().map()
			.mapper([](Device& device) { return make_unique<Canvas>(device.as<DScriptCanvas>().script().name(), [&device](Widget& widget) { device.as<DScriptCanvas>().insertNode(); }); });

		DInsertNode::cls().map()
			//.mapper([](Device& device) { return make_unique<Dropdown>([](Widget& widget) { widget.as<Button>().trigger(); }); })
			.mapper([](Device& device) { device.as<DInsertNode>().canvas().insertAt(device.uiWindow().mouse().lastX(), device.uiWindow().mouse().lastY()); return make_unique<Popup>(); })
			.structure([](Device& device, Sheet& sheet) -> Sheet& {
				Dropdown& dropdown = sheet.emplace<Dropdown>([](Widget& widget) { widget.as<Button>().trigger(); }, StringVector{}, true);
				return dropdown;
			})
			.postinsert([](Device& device, Sheet& sheet) {
				sheet.as<Dropdown>().dropdown();
			});

		DProcess::cls().map()
			.mapper([](Device& device) { return make_unique<Node>(device.as<DProcess>().process().title()); })
			.postinsert([](Device& device, Sheet& sheet) {
				float x = device.as<DProcess>().canvas().insertAt()[0];
				float y = device.as<DProcess>().canvas().insertAt()[1];
				sheet.frame().setPosition(x - sheet.parent()->frame().left(), y - sheet.parent()->frame().top());
			});

		DProcessOutput::cls().map()
			.mapper([](Device& device) { return make_unique<NodeOutPlug>(device.as<DProcessOutput>().param().name(), [](NodePlug& plugIn, NodePlug& plugOut) { plugIn.device()->as<DProcessOutput>().param().connectTo(plugOut.device()->as<DProcessInput>().param()); }); })
			.inserter([](Device& device) { return &device.parent()->parent()->sheet().as<Node>().outputs(); })
			.refresh([](Device& device, Widget& widget) { return widget.as<NodeOutPlug>().setTooltip(device.as<DProcessOutput>().param().paramInfo()); });

		DProcessInput::cls().map()
			.mapper([](Device& device) { return make_unique<NodeInPlug>(device.as<DProcessInput>().param().name()); })
			.inserter([](Device& device) { return &device.parent()->parent()->sheet().as<Node>().inputs(); })
			.refresh([](Device& device, Widget& widget) { return widget.as<NodeInPlug>().setTooltip(device.as<DProcessInput>().param().paramInfo()); });

		DRootObjectCreate::cls().map()
			.structure([](Device& device, Sheet& sheet) -> Sheet& {

				static DeviceMapping dropdownMapping;
				dropdownMapping.mapper([](Device& device) { return make_unique<Dropdown>([&device](Widget& widget) { device.as<Stack>().on(widget.device()->as<Hook>().object()); }); });

				device.as<DRootObjectCreate>().types().mapping(dropdownMapping);
				return sheet;
			});
	}
}
