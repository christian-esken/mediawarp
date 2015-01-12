/*
 * ElementSelector.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef ELEMENTSELECTOR_H_
#define ELEMENTSELECTOR_H_

#include <vector>       // std::vector

#include "../model/MediaItem.h"
#include "../util/stdnamespaces.h"

class ElementSelector
{
public:
	ElementSelector(int count);
	virtual ~ElementSelector();

	virtual std::vector<shared_ptr<MediaItem> > select(std::vector<shared_ptr<MediaItem> > ventries) = 0;

	const int getCount() const
	{
		return count;
	}

protected:
	const int count;

};

#endif /* ELEMENTSELECTOR_H_ */
