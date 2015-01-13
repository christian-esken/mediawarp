/*
 * ChainedFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "ChainedFilter.h"

ChainedFilter::ChainedFilter()
{
}

ChainedFilter::~ChainedFilter()
{
	filters.clear();
}

void ChainedFilter::addFilter(FilterInterface* filter)
{
	shared_ptr<FilterInterface> ptrFilter = shared_ptr<FilterInterface>(filter);
	filters.push_back(ptrFilter);

}

bool ChainedFilter::match(shared_ptr<MediaItem> mediaItem)
{
	for (shared_ptr<FilterInterface> filter : filters)
	{
		if (! filter->match(mediaItem))
		{
			// AND filter
			return false;
		}
	}

	// All filters holde => accept
	return true;
}
