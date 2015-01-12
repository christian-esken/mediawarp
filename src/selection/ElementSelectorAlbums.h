/*
 * ElementSelector.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef ELEMENTSELECTOR_Albums_H_
#define ELEMENTSELECTOR_Albums_H_

#include <vector>       // std::vector

#include "../selection/ElementSelector.h"
#include "../model/MediaItem.h"
#include "../util/stdnamespaces.h"

class ElementSelectorAlbums : public ElementSelector
{
public:
	ElementSelectorAlbums(int count);
	virtual ~ElementSelectorAlbums();

	std::vector<shared_ptr<MediaItem> > select(std::vector<shared_ptr<MediaItem> > ventries) override;
};

#endif /* ELEMENTSELECTOR_H_ */
