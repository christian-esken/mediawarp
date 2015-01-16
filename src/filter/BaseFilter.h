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
	virtual ~BaseFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);

protected:
	BaseFilter();
};

#endif /* BaseFILTER_H_ */
