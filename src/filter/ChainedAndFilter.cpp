/*
 * ChainedAndFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "ChainedAndFilter.h"

ChainedAndFilter::ChainedAndFilter()
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

bool ChainedAndFilter::match(shared_ptr<MediaItem> mediaItem)
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
