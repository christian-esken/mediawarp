/*
 * AlbumFilter.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include "AlbumFilter.h"

AlbumFilter::AlbumFilter(QString tagValue) : TagFilter(tagValue)
{
}

AlbumFilter::~AlbumFilter()
{
}


bool AlbumFilter::match(shared_ptr<MediaItem> mediaItem)
{
	return tagExpr.match(mediaItem->getAlbum()).hasMatch();
}
