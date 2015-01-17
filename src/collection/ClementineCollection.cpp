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



ClementineCollection::ClementineCollection(QString clementineDB) : db(clementineDB)
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

std::vector<shared_ptr<MediaItem> > ClementineCollection::load()
{
	std::vector<shared_ptr<MediaItem> > ventries;

	QString allTunesSQL;
	allTunesSQL.reserve(300);
	allTunesSQL.append(
		"select filename, lastplayed, beginning, length, genre, rating, playcount, skipcount, score, mtime, ctime");
	allTunesSQL.append(" FROM songs");

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

