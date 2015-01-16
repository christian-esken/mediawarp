/*
 * BaseFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "BaseFilter.h"

BaseFilter::BaseFilter() : FilterInterface()
{
}

BaseFilter::~BaseFilter()
{
}

bool BaseFilter::match(shared_ptr<MediaItem> mediaItem)
{
	return false;
}
