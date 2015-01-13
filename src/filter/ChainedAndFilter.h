/*
 * ChainedAndFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef ChainedAndFilter_H_
#define ChainedAndFilter_H_

#include "FilterInterface.h"

#include <vector>       // std::vector

class ChainedAndFilter: public FilterInterface
{
public:
	ChainedAndFilter();
	virtual ~ChainedAndFilter();

	void addFilter(FilterInterface* ifc);

	virtual bool match(shared_ptr<MediaItem> mediaItem);

private:
	std::vector<shared_ptr<FilterInterface> > filters;
};

#endif /* UNHEAREDFILTER_H_ */
