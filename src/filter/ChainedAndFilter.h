/*
 * UnhearedFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef ChainedFILTER_H_
#define ChainedFILTER_H_

#include "FilterInterface.h"

#include <vector>       // std::vector

class ChainedFilter: public FilterInterface
{
public:
	ChainedFilter();
	virtual ~ChainedFilter();

	void addFilter(FilterInterface* ifc);

	virtual bool match(shared_ptr<MediaItem> mediaItem);

private:
	std::vector<shared_ptr<FilterInterface> > filters;
};

#endif /* UNHEAREDFILTER_H_ */
