/*
 * UnhearedFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "UnhearedFilter.h"

UnhearedFilter::UnhearedFilter()
{
	// TODO Auto-generated constructor stub

}

UnhearedFilter::~UnhearedFilter()
{
	// TODO Auto-generated destructor stub
}

bool UnhearedFilter::match(shared_ptr<MediaItem> mediaItem)
{
	return mediaItem->getPlaycount() == 0;
}
