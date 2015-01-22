/*
 * ArtistFilter.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include "ArtistFilter.h"

ArtistFilter::ArtistFilter(QString tagValue) : TagFilter(tagValue)
{
}

ArtistFilter::~ArtistFilter()
{
}


bool ArtistFilter::match(shared_ptr<MediaItem> mediaItem)
{
	return tagExpr.match(mediaItem->getArtist()).hasMatch();
}
