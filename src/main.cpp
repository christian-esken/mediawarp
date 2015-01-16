#include <algorithm>
#include <exception>
#include <iostream>
#include <time.h>
#include <vector>       // std::vector

#include <QDebug>
#include <QList>

#include "util/stdnamespaces.h"

#include "mediawarpConfig.h"
#include "collection/ClementineCollection.h"
#include "filter/FilterFactory.h"
#include "filter/BaseFilter.h"
#include "filter/ChainedAndFilter.h"
#include "filter/UnhearedFilter.h"
#include "model/MediaItem.h"
#include "selection/ElementSelectorAlbums.h"
#include "selection/ElementSelectorSongs.h"
#include "selection/MediaItemSortFunctions.h"
#include "util/Param.h"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[])
{
	bool printInfos = false;

	time_t now = time(0);
	srand(uint(now));

	std::vector<shared_ptr<MediaItem> > ventries;

	char clementineDB[] = "/home/chris/.config/Clementine/clementine.db";
	try
	{
		ClementineCollection coll(clementineDB);
		ventries = coll.load();

		Param params(argc, argv);

		// SELECT * FROM collection1 WHERE notplayed ORDER BY liking,random LIMIT 5 albums


		// -BEGIN- SORT ----------------------------------------------------------------------
		MediaItemSort* sortFunction = new MediaItemSort(params.getOrder());

		std::vector<shared_ptr<MediaItem> >::iterator begin1(ventries.begin());
		std::vector<shared_ptr<MediaItem> >::iterator end1(ventries.end());
		std::sort(begin1, end1, *sortFunction);

		if (printInfos)
			std::cerr << "Sorted songs         : " << ventries.size() << std::endl;

		// -PROCESS- FILTER ----------------------------------------------------------------------
		FilterInterface* filterChain = FilterFactory::build(params.getFilter());
		std::vector<shared_ptr<MediaItem> > filteredSongs;

		// Hint: We need a manual loop, as std::copy_if requires a stateless function (object)
		//		std::copy_if(begin2, end2, std::back_inserter(filteredSongs), *(filterChain)); // << does not work
		for (shared_ptr<MediaItem> entry : ventries)
		{
			if (filterChain->operator()(entry))
				filteredSongs.push_back(entry);
		}

		if (printInfos)
			std::cerr << "Songs after filtering: " << filteredSongs.size() << std::endl;


		// -END- FINAL SELECTION ----------------------------------------------------------------------
		mediawarp::Constants::Unit unit = params.getUnit();

		ElementSelector* selector;
		if (unit == mediawarp::Constants::Unit::Album)
			selector = new ElementSelectorAlbums(params.getLimit());
		else if (unit == mediawarp::Constants::Unit::Title)
			selector = new ElementSelectorSongs(params.getLimit());

		std::vector<shared_ptr<MediaItem> > selectedSongs = selector->select(filteredSongs);



		// ---  Write M3U list -------------------------------------------------------------------

		if (printInfos)
		{
			std::cerr << "Selected songs       : " << selectedSongs.size() << std::endl;
			std::cerr << "---------------------------------------------------------------------" << std::endl;
		}

		std::cout << "#EXTM3U" << std::endl << std::endl;

		for (auto &mi : selectedSongs)
		{
			QString filename = (*mi).getFilename();
			if (filename.startsWith("file:///"))
			{
				filename = filename.mid(7); // strip off URL prefix for files
			}
			// TODO This might need URL-Decode, depending on how we define MediaItem::getFilename()
			std::cout << filename.toUtf8().data() << std::endl;
		}



		// -TEARDOWN- ------------------------------------------------------------------------------------

		ventries.clear();
		delete sortFunction;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
		exit(1);
	}
	return 0;
}
