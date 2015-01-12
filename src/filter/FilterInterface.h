/*
 * FilterInterface.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef FILTERINTERFACE_H_
#define FILTERINTERFACE_H_

#include "../model/MediaItem.h"

class FilterInterface
{
public:
	FilterInterface();
	virtual ~FilterInterface();

	virtual bool match(shared_ptr<MediaItem> mediaItem) = 0;
	bool operator()(shared_ptr<MediaItem> mediaItem) { return match(mediaItem); };
};

#endif /* FILTERINTERFACE_H_ */
