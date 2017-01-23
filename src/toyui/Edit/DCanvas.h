//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CANVAS_H
#define TOY_CANVAS_H

/* toy */
#include <toyobj/Store/Array.h>
#include <toyobj/Store/Registry.h>
#include <toyobj/Script/Script.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Device/Stack.h>

#include <vector>

namespace toy
{
	class TOY_UI_EXPORT DProcessInput : public Device
	{
	public:
		DProcessInput(Device& parent, InputParam& inputParam);

		InputParam& param() { return m_param; }

		static DeviceType& cls() { static DeviceType ty("DNodeInput", Device::cls()); return ty; }

	protected:
		InputParam& m_param;
	};

	class TOY_UI_EXPORT DProcessOutput : public Device
	{
	public:
		DProcessOutput(Device& parent, OutputParam& outputParam);

		OutputParam& param() { return m_param; }

		static DeviceType& cls() { static DeviceType ty("DNodeOutput", Device::cls()); return ty; }

	protected:
		OutputParam& m_param;
	};

	class TOY_UI_EXPORT DProcess : public Device, public Process::Observer
	{
	public:
		DProcess(Device& parent, DScriptCanvas& canvas, Process& process, DeviceType* deviceType = nullptr);

		DScriptCanvas& canvas() { return m_canvas; }
		Process& process() { return m_process; }

		virtual void handleProcessExecute(Process& process);

		static DeviceType& cls() { static DeviceType ty("DProcess", Device::cls()); return ty; }

	protected:
		DScriptCanvas& m_canvas;
		Process& m_process;
		Stack& m_inputs;
		Stack& m_outputs;
		Device& m_body;
	};

	class TOY_UI_EXPORT DInsertNode : public Device
	{
	public:
		DInsertNode(Device& parent, DScriptCanvas& canvas);

		void insert(const ProcessCreator& creator);

		DScriptCanvas& canvas() { return m_canvas; }

		static DeviceType& cls() { static DeviceType ty("DInsertNode", Device::cls()); return ty; }

	protected:
		DScriptCanvas& m_canvas;
	};

	class TOY_UI_EXPORT DScriptCanvas : public Stack
	{
	public:
		DScriptCanvas(Device& parent, Script& script);

		Script& script() { return m_script; }

		void insertNode();

		unique_ptr<DProcess> makeNode(Device& parent, Object& process);

		void insertAt(float x, float y, float z = 0.f) { m_insertAt[0] = x; m_insertAt[1] = y; m_insertAt[2] = z; }
		const std::array<float, 3>& insertAt() { return m_insertAt; }

		static DeviceType& cls() { static DeviceType ty("DScriptCanvas", Stack::cls()); return ty; }

	protected:
		Script& m_script;
		//Stack& m_nodes;
		std::array<float, 3> m_insertAt;
	};

	class TOY_UI_EXPORT DScriptEditor : public Device
	{
	public:
		DScriptEditor(Device& parent);

		Stack& canvases() { return m_canvases; }

		Script& newScript();

		static DeviceType& cls() { static DeviceType ty("DScriptEditor", Device::cls()); return ty; }

	protected:
		Registry<Script> m_scripts;
		Stack& m_canvases;
	};

	class ProcessDisplay;

	class TOY_UI_EXPORT DProcessDisplay : public DProcess
	{
	public:
		DProcessDisplay(Device& parent, DScriptCanvas& canvas, ProcessDisplay& process);

		void updateDisplay(ProcessDisplay& process);

		static DeviceType& cls() { static DeviceType ty("DProcessDisplayString", DProcess::cls(), true); return ty; }
	};

	/*

	class TOY_UI_EXPORT NodeStructure : public DProcess
	{
	public:
		NodeStructure(Device& parent, DScriptCanvas& canvas);

		virtual void execute();

		static DeviceType& cls() { static DeviceType ty("NodeStructure", DProcess::cls(), true); return ty; }

	protected:
		DStructure& m_structure;
	};

	class TOY_UI_EXPORT NodeConstruct : public DProcess
	{
	public:
		NodeConstruct(Device& parent, DScriptCanvas& canvas);

		virtual void execute();

		static DeviceType& cls() { static DeviceType ty("NodeConstruct", DProcess::cls(), true); return ty; }

	protected:
		DRootObjectCreate& m_objectCreate;
	};

	*/
}

#endif
