/*
 * ElementSelectorDuration.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include "src/selection/ElementSelectorDuration.h"

#include <iostream>
#include <string>

#include <QSet>
#include <QString>

ElementSelectorDuration::ElementSelectorDuration(int count, mediawarp::Constants::Unit unit) :
ElementSelector(count), unit(unit)
{
	if (unit != mediawarp::Constants::Unit::Minutes)
	{
		// TODO Eclipse shows "Function 'to_string' could not be resolved". Maybe not correctly configured to C++11,
		//      because std::to_string should be defined inside #include <string>
		throw std::runtime_error(std::string("Only time unit Minutes supported. unit=" + std::to_string(unit)));
	}
}

ElementSelectorDuration::~ElementSelectorDuration()
{
}

std::vector<shared_ptr<MediaItem> > ElementSelectorDuration::select(std::vector<shared_ptr<MediaItem> > ventries)
{
	// We will keep the songs in an interval of "[count .. count+1[" minutes.
	long targetMillis = ( count    * 60) * 1000;
	long maxMillis    = ((count+1) * 60) * 1000;

	std::vector<shared_ptr<MediaItem> > result;
	long millis = 0;
	for (auto &entry : ventries)
	{
		long millisSong = entry->getLengthMillis();
		if (millisSong <= 0)
		{
			// This title is either empty, then it makes no sense to add.
			// Or the collection has no clue how long this title is => it might be arbitrarily long => better do not
			// add it, as it may be way too long (could be even and audiobook with 10 hours).
			continue;
		}


		long wouldBeMillis = millis + millisSong;
		if (wouldBeMillis >= maxMillis)
		{
			// This song would be over a minute longer. But there is probabably another that will fit => continue
			continue;
		}

		result.push_back(entry);
		millis += millisSong;
		std::cerr << "Adding a song with " << millisSong << "ms. New overall length is " << millis << "ms"
			<< "   \ttarget-interval=[" << targetMillis << " .. " << maxMillis << "[ ms"
			<< std::endl;

		if (millis > targetMillis)
		{
			break;
		}
	}

	return result;
}
