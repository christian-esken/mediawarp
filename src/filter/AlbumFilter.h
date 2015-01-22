/*
 * AlbumFilter.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef SRC_FILTER_AlbumFILTER_H_
#define SRC_FILTER_AlbumFILTER_H_

#include "TagFilter.h"

class AlbumFilter: public TagFilter
{
public:
	AlbumFilter(QString tagValue);
	virtual ~AlbumFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);
};

#endif /* SRC_FILTER_AlbumFILTER_H_ */
