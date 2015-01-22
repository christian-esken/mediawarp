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
	ElementSelectorAlbums(int count, std::vector<shared_ptr<MediaItem> > unfilteredSongs);
	virtual ~ElementSelectorAlbums();

	std::vector<shared_ptr<MediaItem> > select(std::vector<shared_ptr<MediaItem> > ventries) override;

private:
	std::vector<shared_ptr<MediaItem> > unfilteredSongs;
};

#endif /* ELEMENTSELECTOR_H_ */
