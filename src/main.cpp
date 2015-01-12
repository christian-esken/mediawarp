#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>       // std::vector

#include <QDebug>
#include <QList>

#include "mediawarpConfig.h"
#include "filter/UnhearedFilter.h"
#include "model/MediaItem.h"
#include "selection/ElementSelectorAlbums.h"
#include "selection/ElementSelectorSongs.h"
#include "selection/MediaItemSortFunctions.h"
#include "storage/SQLiteConnection.h"
#include "util/stdnamespaces.h"

using std::cout;
using std::cerr;
using std::endl;

static char orderLiking[] = "LIKING";
int main(int argc, char *argv[])
{
	time_t now = time(0);
	srand (uint(now));

	char clementineDB[] = "/home/chris/.config/Clementine/clementine.db";
	SQLiteConnection* conn = new SQLiteConnection();
	if (!conn->open(clementineDB, false))
	{
		cerr << "Cannot open Clementine database: db=" << clementineDB << endl;
		exit(1);
	}

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


	std::vector<shared_ptr<FilterInterface> > filters;

	UnhearedFilter* uf = new UnhearedFilter();
	shared_ptr<FilterInterface> filter = shared_ptr<FilterInterface>(uf);
	filters.push_back(filter);

//	cout << "Opened Clementine database: db=" << clementineDB << endl;

	QString allTunesSQL;
	allTunesSQL.reserve(300);
	allTunesSQL.append(
		"select filename, lastplayed, beginning, length, genre, rating, playcount, skipcount, score, mtime, ctime");
	allTunesSQL.append(" FROM songs");
//	allTunesSQL.append(" ORDER BY playcount DESC");
//  allTunesSQL = allTunesSQL.append(" LIMIT %1").arg(limit);

	std::vector<shared_ptr<MediaItem> > ventries;

	QSqlQuery* query = conn->runQuery(allTunesSQL);
	while (query->next())
	{
		shared_ptr<MediaItem> mi1(new MediaItem());
		QSqlRecord row = query->record();
		mi1->setFilename(row.value(0).toString());
		mi1->setLastplayedMillis(row.value(1).toLongLong());
		mi1->setCurrentPlayposition(row.value(2).toLongLong());
		mi1->setLengthMillis(row.value(3).toInt());
		mi1->setGenre(row.value(4).toString());
		mi1->setRating(row.value(5).toInt());
		mi1->setPlaycount(row.value(6).toInt());
		mi1->setSkipcount(row.value(7).toInt());
		mi1->setScore(row.value(8).toInt());
		long mtime = row.value(9).toLongLong();
		mi1->setMtimeMillis(mtime);
		mi1->setCtimeMillis(row.value(10).toLongLong());
		mi1->setAtimeMillis(mtime);

		ventries.push_back(mi1);
	}

//	std::cout << "------------------------------" << std::endl;

//	std::cout << "--- PRINT before SORT ---------------------------" << std::endl;
//	foreach(shared_ptr<MediaItem> mi, ventries)
//	{
//		std::cout << (*mi) << std::endl;
//	}


//	std::cout << "--- SORT ---------------------------" << std::endl;

	// -BEGIN- SORT ----------------------------------------------------------------------

	QString orderString(order);
	QStringList orderList = orderString.split(',');
	MediaItemSort* sortFunction = new MediaItemSort(orderList);

	std::vector<shared_ptr<MediaItem> >::iterator begin1(ventries.begin());
	std::vector<shared_ptr<MediaItem> >::iterator end1(ventries.end());
	std::sort(begin1, end1, *sortFunction);


	// -PROCESS- FILTER ----------------------------------------------------------------------
//	std::copy_if()
	std::vector<shared_ptr<MediaItem> > filteredSongs;
	std::copy_if(begin1, end1, std::back_inserter(filteredSongs), *(uf));

	// -END- FINAL SELECTION ----------------------------------------------------------------------
	ElementSelectorAlbums selector(limit);
	std::vector<shared_ptr<MediaItem> > selectedSongs = selector.select(filteredSongs);

	for (auto &mi : selectedSongs)
	{
		std::cout << (*mi) << std::endl;
//		if (++i > limit)
//		break;
	}
	delete query;

	ventries.clear();
//	std::cout << "--- QUIT --- " << order << std::endl;

	conn->close();
	delete conn;
	delete sortFunction;
	return 0;
}

//  sqlite> .schema songs
// CREATE TABLE songs (
//   /* Metadata from taglib */
//   title TEXT,
//   album TEXT,
//   artist TEXT,
//   albumartist TEXT,
//   composer TEXT,
//   track INTEGER,
//   disc INTEGER,
//   bpm REAL,
//   year INTEGER,
//   genre TEXT,
//   comment TEXT,
//   compilation INTEGER,
// 
//   length INTEGER,
//   bitrate INTEGER,
//   samplerate INTEGER,
// 
//   /* Information about the file on disk */
//   directory INTEGER NOT NULL,
//   filename TEXT NOT NULL,
//   mtime INTEGER NOT NULL,
//   ctime INTEGER NOT NULL,
//   filesize INTEGER NOT NULL
// , sampler INTEGER NOT NULL DEFAULT 0, art_automatic TEXT, art_manual TEXT, filetype INTEGER NOT NULL DEFAULT 0, playcount INTEGER NOT NULL DEFAULT 0, lastplayed INTEGER, rating INTEGER, forced_compilation_on INTEGER NOT NULL DEFAULT 0, forced_compilation_off INTEGER NOT NULL DEFAULT 0, effective_compilation NOT NULL DEFAULT 0, skipcount INTEGER NOT NULL DEFAULT 0, score INTEGER NOT NULL DEFAULT 0, beginning INTEGER NOT NULL DEFAULT 0, cue_path TEXT, unavailable INTEGER DEFAULT 0, effective_albumartist TEXT, etag TEXT);
// CREATE INDEX idx_comp_artist ON songs (effective_compilation, artist);
// CREATE INDEX idx_album ON songs (album);
// CREATE INDEX idx_title ON songs (title);
// CREATE INDEX idx_filename ON songs (filename);
