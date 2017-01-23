#include <toyui/Edit/DIndexer.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Reflect/Imprint.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Device/RootDevice.h>
#include <toyui/UiWindow.h>

#include <toyobj/Indexer.h>

#include <toyui/Device/Stack.h>

using namespace std::placeholders;

namespace toy
{
	DIndexer::DIndexer(Device& parent, Indexer& indexer, Store<Object>& selection)
		: Device(parent, cls())
		, m_elementType(indexer.elementType())
		, m_name(m_elementType.imprint().name())
		, m_picker(this->emplace<Stack>().store(indexer).selecter(selection))
	{
	}

	DIndexer::~DIndexer()
	{}
}
