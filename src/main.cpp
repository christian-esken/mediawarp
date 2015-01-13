#include <algorithm>
#include <exception>
#include <iostream>
#include <time.h>
#include <vector>       // std::vector

#include <QDebug>
#include <QList>

#include "mediawarpConfig.h"
#include "collection/ClementineCollection.h"
#include "filter/ChainedAndFilter.h"
#include "filter/UnhearedFilter.h"
#include "model/MediaItem.h"
#include "selection/ElementSelectorAlbums.h"
#include "selection/ElementSelectorSongs.h"
#include "selection/MediaItemSortFunctions.h"
#include "util/stdnamespaces.h"

using std::cout;
using std::cerr;
using std::endl;

static char orderLiking[] = "LIKING,RANDOM,ID";
int main(int argc, char *argv[])
{
	time_t now = time(0);
	srand(uint(now));

	std::vector<shared_ptr<MediaItem> > ventries;

	char clementineDB[] = "/home/chris/.config/Clementine/clementine.db";
	try
	{
		ClementineCollection coll(clementineDB);
		ventries = coll.load();

		int limit = 50;
		char* order = orderLiking;

		if (argc >= 2)
		{
			limit = atoi(argv[1]);
		}

		if (argc >= 3)
		{
			order = argv[2];
		}


		// SELECT * FROM collection1 WHERE notplayed ORDER BY liking,random LIMIT 5 albums

		// -BEGIN- SORT ----------------------------------------------------------------------

		QString orderString(order);
		QStringList orderList = orderString.split(',');
		MediaItemSort* sortFunction = new MediaItemSort(orderList);

		std::vector<shared_ptr<MediaItem> >::iterator begin1(ventries.begin());
		std::vector<shared_ptr<MediaItem> >::iterator end1(ventries.end());
		std::sort(begin1, end1, *sortFunction);

		// -PROCESS- FILTER ----------------------------------------------------------------------
		ChainedAndFilter* filterChain = new ChainedAndFilter();
		filterChain->addFilter(new UnhearedFilter());

		std::vector<shared_ptr<MediaItem> > filteredSongs;
		std::copy_if(begin1, end1, std::back_inserter(filteredSongs), *(filterChain));

		// -END- FINAL SELECTION ----------------------------------------------------------------------
		ElementSelectorAlbums selector(limit);
//		ElementSelectorSongs selector(limit);
		std::vector<shared_ptr<MediaItem> > selectedSongs = selector.select(filteredSongs);

		for (auto &mi : selectedSongs)
		{
			std::cout << (*mi) << std::endl;
		}



		// -TEARDOWN- ------------------------------------------------------------------------------------
		// -TEARDOWN- ------------------------------------------------------------------------------------
		// -TEARDOWN- ------------------------------------------------------------------------------------

		ventries.clear();
		//	std::cout << "--- QUIT --- " << order << std::endl;

		delete sortFunction;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
		exit(1);
	}
	return 0;
}
