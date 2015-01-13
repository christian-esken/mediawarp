/*
 * CollectionInterface.h
 *
 *  Created on: 13.01.2015
 *      Author: chris
 */

#ifndef SRC_COLLECTIONINTERFACE_H_
#define SRC_COLLECTIONINTERFACE_H_

#include "../model/MediaItem.h"
#include "../util/stdnamespaces.h"

class CollectionInterface
{
public:
	CollectionInterface();
	virtual ~CollectionInterface();

	virtual std::vector<shared_ptr<MediaItem> > load() = 0;
};

#endif /* SRC_COLLECTIONINTERFACE_H_ */
