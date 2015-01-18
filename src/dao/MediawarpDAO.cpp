/*
 * MediawarpDAO.cpp
 *
 *  Created on: 17.01.2015
 *      Author: chris
 */

#include "MediawarpDAO.h"

#include <iostream>


MediawarpDAO::MediawarpDAO() : conn(0)
{
}

MediawarpDAO::~MediawarpDAO()
{
	delete conn;
}

void MediawarpDAO::open()
{
	bool printInfos = false;

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
	QString mediawarpDB = appDataDir + "mediawarp.sqlite";

	conn = new SQLiteConnection();
	if (!conn->open(mediawarpDB, "mediawarp", true))
	{
		throw std::runtime_error(std::string("Cannot open mediawarp database: db=" ) + mediawarpDB.toUtf8().data());
	}


	prepareTables();

}

/**
 * Prepares the DB tables, if they do not exist yet. Tables are either created or migrated to the current version by
 * this method.
 */
void MediawarpDAO::prepareTables()
{
	/**
	 * mwdb table setup
	 */


	/** Create : CREATE TABLE IF NOT EXISTS collection (collection_id INTEGER, collection_type TEXT, readable_name TEXT, uri TEXT, last_change_seen INTEGER);
	 *
	 * Example: 1, "clementine", "/home/chris/.config/Clementine/clementine.db", 1421453370
	 *
	 * collection_id     : UNIQUE ID in this table (autoincrement)
	 * uri               : The unique URI to connect to the collection. Can be either a local file name, or points to
	 *                     a remote service. Example "clementine:///DEFAULTDB". Everything after the scheme (here
	 *                     "clementine:" has a collection dependent interpretation, but
	 *                     collection impelmentors SHOULD follow the URI RFC spec.
	 * readable_name     : User changable name, e.g. "Clementine collection on whitefall@site.local"
	 * last_change_seen  : The latest change (add or remove title) in the collection mediawarp is aware.
	 */
	QString sql = "CREATE TABLE IF NOT EXISTS collection (collection_id INTEGER, uri TEXT, readable_name TEXT, last_change_seen INTEGER)";
	conn->runQuery(sql);

	/**
	 * Create : CREATE TABLE IF NOT EXISTS title (title_id INTEGER, collection_id INTEGER, id TEXT);
	 *
	 * Example: 1, 1, "47"
	 *
	 * title_id       : UNIQUE ID in this table (autoincrement)
	 * collection_id  : Collection ID, where this title belongs to
	 * title_uri      : The ID that uniquely identifies the title in the collection (collection specfic, e.g. a numeric ID or URI)
	 *
	 */
	sql = "CREATE TABLE IF NOT EXISTS title (title_id INTEGER PRIMARY KEY, collection_id INTEGER, title_uri TEXT)";
	conn->runQuery(sql);

	/**
	 * uri The unique URI to connect to the player. This is typically a device name like file:///dev/sdc1, a hardware
	 *           addres like usb://1d6b:0002@B3:D1     (Bus 3, Device 1)
	 * serialno  The serial number of the player, if known. Dependent on the device type, this can be a number
	 *           form the OS (e.g. lsusb -v | grep iSerial), the actual serial number, or empty (unknown)
	 *
	 * type      The type of the player (e.g. iPod, MTP, Generic USB Flash memory)
	 * readable_name User changable name, e.g. "Green iPod 5th Gen (GreenScreen)"
	 */
	sql = "CREATE TABLE IF NOT EXISTS player (uri TEXT, serialno TEXT, type INTEGER, readable_name TEXT)";
	conn->runQuery(sql);

	// title2player

	/**
	 * A table with metadata, e.g. DB version
	 */
	sql = "CREATE TABLE IF NOT EXISTS mediawarp (metakey TEXT PRIMARY KEY, value TEXT)";
	conn->runQuery(sql);

	sql = "INSERT OR IGNORE INTO  mediawarp VALUES (\"dbversion\", \"1\")";
	conn->runQuery(sql);

}


void MediawarpDAO::markHandled(int playerId, int collectionId, std::vector<shared_ptr<MediaItem> > selectedSongs)
{
	QSqlQuery* query = conn->getPreparedQuery("INSERT OR IGNORE INTO title (title_id, collection_id, title_uri) VALUES (?,?,?)");
//	QSqlQuery* query = conn->getPreparedQuery("INSERT OR IGNORE INTO title (collection_id, title_uri) VALUES (?, ?)");
	for (auto &mi : selectedSongs)
	{

//		query->addBindValue(collectionId);
//		query->addBindValue(mi->getFilename());
		query->bindValue(0, QVariant(QVariant::Int)); // null => SQLite will do autoincrement
		query->bindValue(1, collectionId);
		query->bindValue(2, mi->getFilename());
//		std::cerr << "Bound " << query->boundValues().size() << std::endl;
//		QString filename = (*mi).getFilename();
//		QString sql = "INSERT OR IGNORE INTO title (collection_id, title_uri) VALUES (";
//		sql += QString::number(collectionId) + ", \"" +  filename +"\")";
		conn->execPreparedQuery(query);
	}

	conn->commit();
}

