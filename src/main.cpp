#include <algorithm>
#include <exception>
#include <iostream>
#include <time.h>
#include <vector>       // std::vector

#include <QDebug>
#include <QDir>
#include <QList>
#include <QStandardPaths>

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


	QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/";

	// QStandardPaths::AppLocalDataLocation   // AppLocalDataLocation is only available in Qt5.4 and up
	QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
	appDataDir += "/mediawarp/";
	if (printInfos)
	{
		std::cerr << "appDataDir=" << appDataDir.toUtf8().data() << std::endl;
	}

	QDir dir(appDataDir);
	if (!dir.exists())
	{
	    dir.mkpath(".");
	}

	QString clementineDB = homeDir + ".config/Clementine/clementine.db";
	QString mediawarpDB = appDataDir + "mediawarp.sqlite";

	SQLiteConnection mwdbConn;

	try
	{
		if (!mwdbConn.open(mediawarpDB, "mediawarp", true))
		{
			throw std::runtime_error(std::string("Cannot open mediawarp database: db=" ) + mediawarpDB.toUtf8().data());
		}
		/**
		 * mwdb setup:
		 *
		 * Create : CREATE TABLE IF NOT EXISTS collection (collection_id INTEGER, collection_type TEXT, readable_name TEXT, uri TEXT, last_change_seen INTEGER);
		 *
		 * Example: 1, "clementine", "/home/chris/.config/Clementine/clementine.db", 1421453370
		 *
		 * collection_id     : UNIQUE ID in this table (autoincrement)
		 * collection_type   : One of the supported collection types, e.g. "clementine"
		 * readable_name     : User changable name, e.g. "Clementine collection on whitefall@site.local"
		 * last_change_seen  : The latest change (add or remove title) in the collection mediawarp is aware.
		 *
		 *
		 * Create : CREATE TABLE IF NOT EXISTS title (title_id INTEGER, collection_id INTEGER, id TEXT);
		 *
		 * Example: 1, 1, "47"
		 *
		 * title_id       : UNIQUE ID in this table (autoincrement)
		 * collection_id  : Collection ID from the collection table
		 * id             : The ID that uniquely identifies the title in the collection (collection specfic, e.g. a numeric ID or URI)
		 *
		 */

		ClementineCollection coll(clementineDB);
		ventries = coll.load();

		Param params(argc, argv);

		// SELECT * FROM songs WHERE notplayed ORDER BY liking,random LIMIT 5 albums


		// -BEGIN- SORT ----------------------------------------------------------------------
		MediaItemSort* sortFunction = new MediaItemSort(params.getOrder());

		std::vector<shared_ptr<MediaItem> >::iterator begin1(ventries.begin());
		std::vector<shared_ptr<MediaItem> >::iterator end1(ventries.end());
		std::sort(begin1, end1, *sortFunction);

		if (printInfos)
			std::cerr << "Sorted songs         : " << ventries.size() << std::endl;

		// -PROCESS- FILTER ----------------------------------------------------------------------
		FilterInterface* filterChain = FilterFactory::build(params);
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

		mwdbConn.close();
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
