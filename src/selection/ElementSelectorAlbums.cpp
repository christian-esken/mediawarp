/*
 * ElementSelector.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "src/selection/ElementSelectorAlbums.h"


#include <QSet>
#include <QString>

ElementSelectorAlbums::ElementSelectorAlbums(int count) :
ElementSelector(count)
{
}

ElementSelectorAlbums::~ElementSelectorAlbums()
{
}

std::vector<shared_ptr<MediaItem> > ElementSelectorAlbums::select(std::vector<shared_ptr<MediaItem> > ventries)
{
	QSet<QString> albums;

	std::vector<shared_ptr<MediaItem> > result;
	int i = 0;
	for (auto &entry : ventries)
	{
		bool accept = false;
		QString albumName = entry->getAlbum();
		if (albums.contains(albumName))
		{
			// Album already accepted => accept
			accept = true;
		}
		else
		{
			if (albums.count() != count)
			{
				// More albums may be added => accept
				albums.insert(albumName);
				accept = true;
			}
		}

		if (accept)
		{
			result.push_back(entry);
		}
	}

	return result;
}
