/*
 * ChainedAndFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "ChainedAndFilter.h"

ChainedAndFilter::ChainedAndFilter() : BaseFilter()
{
}

ChainedAndFilter::~ChainedAndFilter()
{
	filters.clear();
}

void ChainedAndFilter::addFilter(FilterInterface* filter)
{
	shared_ptr<FilterInterface> ptrFilter = shared_ptr<FilterInterface>(filter);
	filters.push_back(ptrFilter);

}

/**
 * Returns true if the mediaItem passes all filters. If there are no filters, the mediaItem automatically passes.
 *
 * @param mediaItem
 * @return true if the mediaItem passes all filters
 */
bool ChainedAndFilter::match(shared_ptr<MediaItem> mediaItem)
{
	for (shared_ptr<FilterInterface> filter : filters)
	{
		if (! filter->operator()(mediaItem))
		{
			// AND filter
			return false;
		}
	}

	// All filters hold => accept
	return true;
}
