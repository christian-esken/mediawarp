/*
 * ArtistFilter.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef SRC_FILTER_ARTISTFILTER_H_
#define SRC_FILTER_ARTISTFILTER_H_

#include "TagFilter.h"

class ArtistFilter: public TagFilter
{
public:
	ArtistFilter(QString tagValue);
	virtual ~ArtistFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);
};

#endif /* SRC_FILTER_ARTISTFILTER_H_ */
