/*
 * ClementineCollection.cpp
 *
 *  Created on: 13.01.2015
 *      Author: chris
 */

#include <src/collection/ClementineCollection.h>

#include <exception>
#include <iostream>
//#include <runtime_error>
#include <stdexcept>
#include <system_error>
#include <vector>       // std::vector

#include "../storage/SQLiteConnection.h"



ClementineCollection::ClementineCollection(int collectionId, QString clementineDB) : CollectionInterface(collectionId), db(clementineDB)
{
	conn = new SQLiteConnection();
	if (!conn->open(clementineDB, "clementine", false))
	{
		throw std::runtime_error(std::string("Cannot open Clementine database: db=" ) + clementineDB.toUtf8().data());
	}


	// cout << "Opened Clementine database: db=" << clementineDB << endl;
}

ClementineCollection::~ClementineCollection()
{
	conn->close();
	delete conn;
}

long convertNanoToMillis(QVariant qvar)
{
	qlonglong evenlonger = qvar.toLongLong();
	long verylong = evenlonger / 1000000;
//	if (verylong > 0)
//		std::cerr << "verylong nanos=" << evenlonger << ", millis=" << verylong << std::endl;
	return verylong;
}

std::vector<shared_ptr<MediaItem> > ClementineCollection::load()
{
	std::vector<shared_ptr<MediaItem> > ventries;

	QString allTunesSQL;
	allTunesSQL.reserve(300);
	allTunesSQL.append(
		"select filename, title, album, artist, lastplayed, beginning, length, genre, rating, playcount, skipcount, score, mtime, ctime");
	allTunesSQL.append(" FROM songs");

	QSqlQuery* query = conn->runQuery(allTunesSQL);
	while (query->next())
	{
		int f = 0;
		shared_ptr<MediaItem> mi1(new MediaItem());
		QSqlRecord row = query->record();
		mi1->setUri(row.value(f++).toString());
		mi1->setTitle(row.value(f++).toString());
		mi1->setAlbum(row.value(f++).toString());
		mi1->setArtist(row.value(f++).toString());

		mi1->setLastplayedMillis(convertNanoToMillis(row.value(f++)));
		mi1->setCurrentPlayposition(convertNanoToMillis(row.value(f++)));
		mi1->setLengthMillis(convertNanoToMillis(row.value(f++)));

		mi1->setGenre(row.value(f++).toString());

		float ratingFloat = row.value(f++).toFloat();
		float ratingFloat2 = ratingFloat * 50.0;
		int rating = (int)ratingFloat2;
		mi1->setStarrating(rating);

//		if (ratingFloat > 0)
//			std::cerr << "Rating orig=" << ratingFloat << ", *50=" << ratingFloat2 << ", toInt=" << mi1->getStarrating()
//				<< ", stars=" << qPrintable(mi1->getStarratingString()) << std::endl;

		mi1->setPlaycount(row.value(f++).toInt());
		mi1->setSkipcount(row.value(f++).toInt());
		mi1->setScore(row.value(f++).toInt());

		long mtime = row.value(f++).toLongLong();
		mi1->setMtimeMillis(mtime);
		mi1->setCtimeMillis(row.value(f++).toLongLong());
		mi1->setAtimeMillis(mtime);

		//std::cout << *mi1 << std::endl;
		ventries.push_back(mi1);
	}
	delete query;

	return ventries;
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

