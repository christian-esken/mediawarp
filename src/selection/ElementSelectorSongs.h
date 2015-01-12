/*
 * ElementSelector.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef ELEMENTSELECTOR_SONGS_H_
#define ELEMENTSELECTOR_SONGS_H_

#include <vector>       // std::vector

#include "../selection/ElementSelector.h"
#include "../model/MediaItem.h"
#include "../util/stdnamespaces.h"

class ElementSelectorSongs : public ElementSelector
{
public:
	ElementSelectorSongs(int count);
	virtual ~ElementSelectorSongs();

	std::vector<shared_ptr<MediaItem> > select(std::vector<shared_ptr<MediaItem> > ventries) override;
};

#endif /* ELEMENTSELECTOR_H_ */
