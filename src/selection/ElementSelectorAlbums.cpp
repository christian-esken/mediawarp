/*
 * ElementSelector.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "src/selection/ElementSelectorAlbums.h"


#include <QSet>
#include <QString>

ElementSelectorAlbums::ElementSelectorAlbums(int count, std::vector<shared_ptr<MediaItem> > unfilteredSongs) :
ElementSelector(count), unfilteredSongs(unfilteredSongs)
{
}

ElementSelectorAlbums::~ElementSelectorAlbums()
{
}

std::vector<shared_ptr<MediaItem> > ElementSelectorAlbums::select(std::vector<shared_ptr<MediaItem> > ventries)
{
	QSet<QString> albums;

	// --- STEP 1 --- SELECT ALBUMS ---------------------------------------
	std::vector<shared_ptr<MediaItem> > result;
//	int i = 0;
	for (auto &entry : ventries)
	{
		bool accept = false;
		QString albumName = entry->getAlbum();
		if (albumName.isEmpty())
		{
			// Songs w/o album name do not qualify for the album selector
			continue;
		}

		if (! albums.contains(albumName))
		{
			albums.insert(albumName);
			if (albums.count() == count)
				break;
		}
	}

	// --- STEP 2 --- FROM THE SELECTED ALBUMS, ADD ALL SONGS ------------------------------------
	for (auto &entry : unfilteredSongs)
	{
		QString albumName = entry->getAlbum();
		if (albums.contains(albumName))
		{
			result.push_back(entry);
		}
	}


	return result;
}
