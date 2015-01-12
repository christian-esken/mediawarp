/*
 * UnhearedFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef UNHEAREDFILTER_H_
#define UNHEAREDFILTER_H_

#include "FilterInterface.h"

class UnhearedFilter: public FilterInterface
{
public:
	UnhearedFilter();
	virtual ~UnhearedFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);
};

#endif /* UNHEAREDFILTER_H_ */
