/*
 * UnhearedFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "UnhearedFilter.h"

UnhearedFilter::UnhearedFilter() : BaseFilter()
{
}

UnhearedFilter::~UnhearedFilter()
{
}

bool UnhearedFilter::match(shared_ptr<MediaItem> mediaItem)
{
	return mediaItem->getPlaycount() == 0;
}
