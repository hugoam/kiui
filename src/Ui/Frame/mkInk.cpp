//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>

namespace mk
{
	void InkTarget::moveToTop(InkLayer& layer)
	{
		size_t zmax = mZMax;
		this->removeLayer(layer);
		mLayers[mZMax].push_back(&layer);
		layer.setIndex(mZMax);
		mZMax = zmax;
	}

	unique_ptr<InkLayer> InkTarget::addLayer(Frame& frame, size_t z)
	{
		if(z == 0) z = mZMax++;
		unique_ptr<InkLayer> layer = createLayer(frame, z);
		mLayers[z].push_back(layer.get());
		return std::move(layer);
	}

	void InkTarget::removeLayer(InkLayer& layer)
	{
		mLayers[layer.index()].erase(std::remove(mLayers[layer.index()].begin(), mLayers[layer.index()].end(), &layer), mLayers[layer.index()].end());
		if(mLayers[layer.index()].size() == 0 && mZMax > 0)
		{
			std::swap(mLayers[layer.index()], mLayers[mZMax - 1]);
			for(InkLayer* moved : mLayers[layer.index()])
				moved->setIndex(layer.index());
			--mZMax;
		}
	}
}
