#include <Ui/Edit/mkDIndexer.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Reflect/mkImprint.h>

#include <Ui/Widget/mkRootSheet.h>
#include <Ui/Device/mkRootDevice.h>
#include <Ui/mkUiWindow.h>

#include <Object/mkIndexer.h>

#include <Ui/Device/mkStack.h>

using namespace std::placeholders;

namespace mk
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
