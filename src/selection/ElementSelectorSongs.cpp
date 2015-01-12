/*
 * ElementSelector.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "src/selection/ElementSelectorSongs.h"


#include <QSet>
#include <QString>

ElementSelectorSongs::ElementSelectorSongs(int count) :
ElementSelector(count)
{
}

ElementSelectorSongs::~ElementSelectorSongs()
{
}

std::vector<shared_ptr<MediaItem> > ElementSelectorSongs::select(std::vector<shared_ptr<MediaItem> > ventries)
{
	QSet<QString> albums;

	std::vector<shared_ptr<MediaItem> > result;
	int i = 0;
	for (auto &entry : ventries)
	{
		result.push_back(entry);
//		std::cout << *entry << std::endl;
		if (++i == count)
			break;

	}

	return result;
}
