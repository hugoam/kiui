//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/DCanvas.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>

#include <toyui/Edit/DStructure.h>
#include <toyui/Edit/DObjectCreate.h>
#include <toyui/Edit/DValueEdit.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Script/Script.h>

using namespace std::placeholders;

namespace toy
{
	DProcessInput::DProcessInput(Device& parent, InputParam& param)
		: Device(parent, cls())
		, m_param(param)
	{}

	DProcessOutput::DProcessOutput(Device& parent, OutputParam& param)
		: Device(parent, cls())
		, m_param(param)
	{}

	DProcess::DProcess(Device& parent, DScriptCanvas& canvas, Process& process, DeviceType* deviceType)
		: Device(parent, deviceType ? *deviceType : cls())
		, m_canvas(canvas)
		, m_process(process)
		, m_inputs(this->emplace<Stack>().maker(&make_device<InputParam, DProcessInput>).tstore(process.inputs()))
		, m_outputs(this->emplace<Stack>().maker(&make_device<OutputParam, DProcessOutput>).tstore(process.outputs()))
		, m_body(this->emplace<Device>(Device::cls()))
	{
		for(OutputParam* output : m_process.outputs().store())
			if(output->edit())
				m_body.emplace<DValue>(output->value(), [output](Lref& lref) { output->invalidate(); });

		process.observe(*this);
	}

	void DProcess::handleProcessExecute(Process& process)
	{
		for(auto& device : m_inputs.contents())
			device->as<DProcessInput>().refresh();

		for(auto& device : m_outputs.contents())
			device->as<DProcessOutput>().refresh();
	}

	DInsertNode::DInsertNode(Device& parent, DScriptCanvas& canvas)
		: Device(parent, cls())
		, m_canvas(canvas)
	{
		for(const ProcessCreator& creator : m_canvas.script().processCreators())
			this->emplace<Response>(creator.name, std::bind(&DInsertNode::insert, this, std::ref(creator)));
		/*
		this->emplace<Response>("Structure", [&canvas]() { canvas.emplace<NodeStructure>(canvas); });
		//this->emplace<Response>("Construct", [&canvas]() { canvas.emplace<NodeConstruct>(canvas); });*/
	}

	void DInsertNode::insert(const ProcessCreator& creator)
	{
		unique_ptr<Process> process = creator.creator(m_canvas.script());
		m_canvas.script().processes().add(std::move(process));
	}

	DScriptCanvas::DScriptCanvas(Device& parent, Script& script)
		: Stack(parent, cls())
		, m_script(script)
		//, m_nodes(this->emplace<Stack>().maker(std::bind(&DScriptCanvas::makeNode, this, _1, _2)).tstore(script.processes()))
	{
		this->maker(std::bind(&DScriptCanvas::makeNode, this, _1, _2));
		this->tstore(script.processes());
	}
		
	void DScriptCanvas::insertNode()
	{
		this->emplace<DInsertNode>(*this);
	}

	unique_ptr<DProcess> DScriptCanvas::makeNode(Device& parent, Object& process)
	{
		if(&process.as<Process>().type() == &ProcessDisplay::cls())
			return make_unique<DProcessDisplay>(parent, parent.as<DScriptCanvas>(), process.as<ProcessDisplay>());

		return make_unique<DProcess>(parent, parent.as<DScriptCanvas>(), process.as<Process>());
	}

	DScriptEditor::DScriptEditor(Device& parent)
		: Device(parent, cls())
		, m_scripts()
		, m_canvases(this->emplace<Stack>().maker(&make_device<Script, DScriptCanvas>).tstore<Script>(m_scripts))
	{
		this->newScript();
		this->newScript();
	}

	Script& DScriptEditor::newScript()
	{
		m_scripts.add(make_unique<Script>("New Script"));
		return *m_scripts.store().back();
	}

	DProcessDisplay::DProcessDisplay(Device& parent, DScriptCanvas& canvas, ProcessDisplay& process)
		: DProcess(parent, canvas, process, &cls())
	{
		process.updateDisplayHandler(std::bind(&DProcessDisplay::updateDisplay, this, _1));
	}

	void DProcessDisplay::updateDisplay(ProcessDisplay& process)
	{
		m_body.clear();
		m_body.emplace<DValue>(process.inputValue().value());
	}

	/*
	NodeStructure::NodeStructure(Device& parent, DScriptCanvas& canvas)
		: DProcess(canvas, "Structure", cls())
		, m_structure(this->emplace<DStructure>())
	{
		&this->emplace<DNodeInput>(*this, "Object");
	}

	void NodeStructure::execute()
	{

	}


	NodeConstruct::NodeConstruct(Device& parent, DScriptCanvas& canvas)
		: DProcess(canvas, "Construct", cls())
		, m_objectCreate(this->emplace<DRootObjectCreate>())
	{
		&this->emplace<DNodeOutput>(*this, "Object");
	}

	void NodeConstruct::execute()
	{

	}

	*/
}
