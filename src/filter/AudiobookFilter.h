/*
 * AudiobookFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef AudiobookFILTER_H_
#define AudiobookFILTER_H_

#include "BaseFilter.h"

class AudiobookFilter: public BaseFilter
{
public:
	AudiobookFilter();
	virtual ~AudiobookFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);
};

#endif /* AudiobookFILTER_H_ */
