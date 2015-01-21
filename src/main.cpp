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
#include "dao/MediawarpDAO.h"
#include "device/IPod.h"
#include "filter/FilterFactory.h"
#include "filter/BaseFilter.h"
#include "filter/ChainedAndFilter.h"
#include "filter/UnhearedFilter.h"
#include "model/MediaItem.h"
#include "selection/ElementSelectorAlbums.h"
#include "selection/ElementSelectorSongs.h"
#include "selection/MediaItemSortFunctions.h"
#include "storage/SQLiteConnection.h"
#include "util/Param.h"

using std::cout;
using std::cerr;
using std::endl;

void openMediaPlayers(bool printInfos);

int main(int argc, char *argv[])
{
	bool printInfos = true;

	time_t now = time(0);
	srand(uint(now));

	std::vector<shared_ptr<MediaItem> > ventries;


	openMediaPlayers(printInfos);

	MediawarpDAO* mwDAO = new MediawarpDAO();

	QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/";
	QString clementineDB = homeDir + ".config/Clementine/clementine.db";

	int collectionId = 1; // TODO This must later be read from the "collections" DB table
	int playerId = 1; // TODO This must later be read from the "player" DB table

	try
	{
		mwDAO->open();

		shared_ptr<ClementineCollection> coll(new ClementineCollection(collectionId, clementineDB));
//		ClementineCollection* coll = new ClementineCollection(1, clementineDB);
		ventries = coll->load();

		mwDAO->addCollection(coll);

		Param params(argc, argv);

		// SELECT * FROM songs WHERE notplayed ORDER BY liking,random LIMIT 5 albums


		// -BEGIN- SORT ----------------------------------------------------------------------
		MediaItemSort* sortFunction = new MediaItemSort(params.getOrder());
		std::sort(ventries.begin(), ventries.end(), *sortFunction);

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

		mwDAO->markHandled(playerId, coll, selectedSongs);

		// -TEARDOWN- ------------------------------------------------------------------------------------

		ventries.clear();
//		delete coll;
		delete mwDAO;
		delete sortFunction;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
		exit(1);
	}
	return 0;
}


/**
 * Experimental opening of a media player. This method must be moved to some dedicated class.
 *
 * @param printInfos
 */
void openMediaPlayers(bool printInfos)
{
	IPod ipodFactory("");
	std::vector<QString> devs = ipodFactory.listDevices();
	if (devs.size() >= 1)
	{
		QString firstDev = devs.front();
		if (printInfos)
			std::cerr << "Opening player: " << qPrintable(firstDev) << std::endl;

		IPod ipod(firstDev);
		try
		{
			std::vector<shared_ptr<MediaItem> > songsOnIpod = ipod.load();

			if (printInfos)
				std::cerr << "Songs on player : " << songsOnIpod.size() << std::endl;
			for (auto &mi : songsOnIpod)
			{
				if (printInfos)
				{
					std::cerr << mi->getRating() << ", " << qPrintable(mi->getFilename()) << std::endl;
				}
			}
		} catch (const std::exception& ex)
		{
			cerr << "Reading iPod DB failed. player=" << qPrintable(firstDev) << ex.what() << endl;
			exit(1);
		}

		if (printInfos)
			std::cerr << "=============================================================================" << std::endl;

	}
}

