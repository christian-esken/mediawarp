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
	virtual ~FilterInterface();

	virtual bool match(shared_ptr<MediaItem> mediaItem) = 0;

	virtual bool operator()(shared_ptr<MediaItem> mediaItem)
	{
		bool ret = match(mediaItem);
		return reverse ? !ret : ret;
	};

	void setReverse(bool reverse)
	{
		this->reverse = reverse;
	};
protected:
	FilterInterface();

private:
	bool reverse;
};

#endif /* FILTERINTERFACE_H_ */
