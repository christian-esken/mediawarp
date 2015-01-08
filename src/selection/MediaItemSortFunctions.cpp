/*
 * MediaItemSortFunctions.cpp
 *
 *  Created on: 22.12.2014
 *      Author: chris
 */

#include "src/selection/MediaItemSortFunctions.h"

#include <algorithm>
#include <assert.h>
#include <iostream>

bool MediaItemSortFunctionsDEBUG = false;

int MediaItemSortFunctions::byRandomizer(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
{
	return (i->getRandomizer() - j->getRandomizer());
}

int MediaItemSortFunctions::byIndex(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
{
	int iVal = i->getIndex();
	int jVal = j->getIndex();
	return compareByGenericInt(iVal, jVal);
}

int MediaItemSortFunctions::compareByGenericInt(int iVal, int jVal)
{
	if (iVal < jVal)
		return -1;
	else if (iVal > jVal)
		return 1;
	else
		return 0;
}

//bool MediaItemSortFunctions::byIndexSmaller(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
//{
//	return i->getIndex() < j->getIndex();
//}

int MediaItemSortFunctions::byName(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
{
	return i->getFilename().compare(j->getFilename());
}

int MediaItemSortFunctions::byLiking(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
{
	int iVal = i->getScore();
	int jVal = j->getScore();
	return compareByGenericInt(iVal, jVal);
}


// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------


MediaItemSort::MediaItemSort(QStringList sortCriteria)
{
	bool foundIndexFallback = false;
	foreach(const QString& orderString, sortCriteria)
	{
		if (orderString.isEmpty())
			continue; // skip empty

		const QChar firstChar = orderString[0];
		bool hasQualifier = firstChar == '-' || firstChar == '+';
		QString order = hasQualifier ? orderString.mid(1) : orderString;

		DIRECTION dir;
		if (firstChar == '-')
		{
			dir = DIRECTION::DESC;
		}
		else if (firstChar == '+')
		{
			dir = DIRECTION::ASC;
		}
		else
		{
			dir = DIRECTION::DEFAULT;
		}

		bool smaller = false;
		if (order == "NAME")
		{
			if (dir == DIRECTION::DEFAULT)
				dir = DIRECTION::ASC;
			_sortCriteria.push_back(DIRECTED_SORT(NAME, dir));
		}
		else if (order == "LIKING")
		{
			if (dir == DIRECTION::DEFAULT)
				dir = DIRECTION::DESC;
			_sortCriteria.push_back(DIRECTED_SORT(LIKING, dir));
		}
		else if (order == "INDEX")
		{
			if (dir == DIRECTION::DEFAULT)
				dir = DIRECTION::ASC;
			_sortCriteria.push_back(DIRECTED_SORT(INDEX, dir));
			foundIndexFallback = true;
			break; // INDEX is unique => any further sort criteria has no effect => exit loop
		}
		else if (order == "RANDOM")
		{
			if (dir == DIRECTION::DEFAULT)
				dir = DIRECTION::ASC;
			_sortCriteria.push_back(DIRECTED_SORT(RANDOMIZER, dir));
			foundIndexFallback = true;
			break; // INDEX is unique => any further sort criteria has no effect => exit loop
		}

	}


	if (!foundIndexFallback)
	{
		_sortCriteria.push_back(DIRECTED_SORT(RANDOMIZER, DIRECTION::ASC));
		_sortCriteria.push_back(DIRECTED_SORT(INDEX, DIRECTION::ASC));
	}
}

MediaItemSort::~MediaItemSort()
{
//	std::for_each( _sortCriteria.begin(), _sortCriteria.end(), delete_pointer_element );
	_sortCriteria.clear();
}

bool MediaItemSort::operator()(shared_ptr<MediaItem> i, shared_ptr<MediaItem> j)
{
	int smaller = 0;
	int smaller2 = 0;
	if (i.get() == 0)
	{
		std::cout << "OUCH i is null";
		exit(1);
		return false;
	}
	if (j.get() == 0)
	{
		std::cout << "OUCH j is null";
		exit(1);
		return false;
	}


	if (MediaItemSortFunctionsDEBUG)
		std::cout << "------ START Compare " << i << " with " << j << "------------------------" << std::endl;

	for(int sc = 0; sc < _sortCriteria.size(); sc++)
	{
		DIRECTED_SORT& directedSort = _sortCriteria[sc];
		smaller = 0;
		smaller2 = 0;
		ORDER order = directedSort.order;
		DIRECTION dir = directedSort.direction;

		/*
		 * Implementation hint: The variable smaller2 is only for asserting the correct functionality.
		 *    It has no functional use for the business case.
		 *
		 */
		switch (order)
		{
			case NAME:
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Running operator() NAME" << std::endl;
				smaller = MediaItemSortFunctions::byName(i,j);
				smaller2 = MediaItemSortFunctions::byName(j,i);
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Leaving operator() NAME with " << smaller << std::endl;
				break;
			case LIKING:
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Running operator() LIKING" << std::endl;
				smaller = MediaItemSortFunctions::byLiking(i,j);
				smaller2 = MediaItemSortFunctions::byLiking(j,i);
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Leaving operator() LIKING with " << smaller << std::endl;
				break;
			case RANDOMIZER:
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Running operator() RANDOM" << std::endl;
				smaller = MediaItemSortFunctions::byRandomizer(i,j);
				smaller2 = MediaItemSortFunctions::byRandomizer(j,i);
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Leaving operator() RANDOM with " << smaller << std::endl;
				break;
			case INDEX:
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Running operator() INDEX" << std::endl;
				smaller = MediaItemSortFunctions::byIndex(i,j);
				smaller2 = MediaItemSortFunctions::byIndex(j,i);
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Leaving operator() INDEX with " << smaller << std::endl;
				break;
			default:
				if (MediaItemSortFunctionsDEBUG)
					std::cout << "Running operator() UNKNOWN!!!!!!!!!!!!!" << std::endl;
				smaller = 0;
				smaller2 = 0;
				break;
		}

		bool ok = assertComparatorLogic(smaller, smaller2);
		if (!ok)
		{
			std::cerr << "FAIL!!! assertComparatorLogic() " << smaller << " vs " << smaller2;
			assert(false);
			exit(1);
		}

		int compareVal = directionAwareCompare(dir, smaller);
		if (compareVal != 0)
		{
			return calcSmallerFromInt(compareVal);
		}

	}

//	return false;

//	std::cout << "Running operator() DEFAULT RETURN false" << std::endl;
//	return false;
	// Fallback
	std::cout << "Running operator() DEFAULT RETURN ..." << std::endl;
	int val = MediaItemSortFunctions::byIndex(i,j);
	std::cout << "Running operator() DEFAULT RETURN ..." << val << std::endl;
	if (val == 0)
	{
		std::cout << " values i=" << i << ", j=" << j << std::endl;
	}
	std::cout << "------ END DEFAULT Compare " << i << " with " << j << "------------------------" << std::endl;
	return calcSmallerFromInt(val);

//	return byIndex(i,j) != 0;
}



bool MediaItemSort::calcSmallerFromInt(int smaller)
{
	return smaller < 0;
}


/**
 * Returns whether the given value is considered negative, zero or positive. The actual result is dependent on the
 * given #direction. For ASC the result is -1, 0 or 1 respectively. For DESC the result is 1, 0 or -1 respectively.
 *
 * @param dir
 * @param smaller
 * @return
 */
int MediaItemSort::directionAwareCompare(DIRECTION dir, int smaller)
{
	bool lessThan = smaller < 0;

	if (dir == DIRECTION::ASC)
	{
		if (lessThan)
			return -1;
		bool biggerThan = smaller > 0;
		if (biggerThan)
			return 1;
	}
	else if (dir == DIRECTION::DESC)
	{
		if (lessThan)
			return 1;
		bool biggerThan = smaller > 0;
		if (biggerThan)
			return -1;
	}

	return 0;
}

bool MediaItemSort::assertComparatorLogic(int smaller, int smaller2)
{
	if (smaller == 0)
	{
		return smaller2 == 0;
	}

	if (smaller < 0)
	{
		return smaller2 > 0;
	}

	if (smaller > 0)
	{
		return smaller2 < 0;
	}

	// this code path is never executed
	return false;
}
