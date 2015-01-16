/*
 * MediaItemSortFunctions.h
 *
 *  Created on: 22.12.2014
 *      Author: chris
 */

#ifndef MEDIAITEMSORTFUNCTIONS_H_
#define MEDIAITEMSORTFUNCTIONS_H_

#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include "QString"
#include "QStringList"

#include "../model/MediaItem.h"
#include "../util/stdnamespaces.h"


class DIRECTED_SORT;

class MediaItemSort
{
public:

	enum ORDER { NAME, LIKING, INDEX, RANDOMIZER };
	enum DIRECTION { ASC, DESC, DEFAULT };

	MediaItemSort(QString order);
	virtual ~MediaItemSort();

	bool operator()(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j);

	bool assertComparatorLogic(int smaller, int smaller2);
	int directionAwareCompare(DIRECTION dir, int smaller);
	bool calcSmallerFromInt(int smaller);


	std::vector<DIRECTED_SORT> _sortCriteria;
};

class MediaItemSortFunctions
{
public:

	static int byIndex(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j);
	static int byName(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j);
	static int byLiking(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j);
	static int byRandomizer(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j);

protected:
	static int compareByGenericInt(int iVal, int jVal);
};

class DIRECTED_SORT
{
public:
	DIRECTED_SORT(MediaItemSort::ORDER order, MediaItemSort::DIRECTION direction) :
	order(order), direction(direction)
	{

	}
	const MediaItemSort::ORDER order;
	const MediaItemSort::DIRECTION direction;

};

#endif /* MEDIAITEMSORTFUNCTIONS_H_ */
