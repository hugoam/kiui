//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

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

	unique_ptr<InkLayer> InkTarget::addLayer(Layer& layer, size_t z)
	{
		if(z == 0) z = mZMax++;
		unique_ptr<InkLayer> inklayer = createLayer(layer, z);
		mLayers[z].push_back(inklayer.get());
		return std::move(inklayer);
	}

	void InkTarget::removeLayer(InkLayer& layer)
	{
		mLayers[layer.index()].erase(std::remove(mLayers[layer.index()].begin(), mLayers[layer.index()].end(), &layer), mLayers[layer.index()].end());
		if(mLayers[layer.index()].size() == 0 && mZMax > 0)
		{
			mLayers.insert(mLayers.begin() + mZMax - 1, mLayers[layer.index()]);
			mLayers.erase(mLayers.begin() + layer.index());
			for(InkLayer* moved : mLayers[layer.index()])
				moved->setIndex(layer.index());
			--mZMax;
		}
	}
}
