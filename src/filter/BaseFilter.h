/*
 * BaseFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef BASEFILTER_H_
#define BASEFILTER_H_

#include "FilterInterface.h"

class BaseFilter: public FilterInterface
{
public:
	BaseFilter();
	virtual ~BaseFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);
};

#endif /* BaseFILTER_H_ */
