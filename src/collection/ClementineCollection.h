/*
 * ClementineCollection.h
 *
 *  Created on: 13.01.2015
 *      Author: chris
 */

#ifndef SRC_COLLECTION_CLEMENTINECOLLECTION_H_
#define SRC_COLLECTION_CLEMENTINECOLLECTION_H_

#include <QString>

#include "CollectionInterface.h"

#include "../storage/SQLiteConnection.h"
#include "../util/stdnamespaces.h"


class ClementineCollection: public CollectionInterface
{
public:
	ClementineCollection(QString db);
	virtual ~ClementineCollection();

	virtual std::vector<shared_ptr<MediaItem> > load();

private:
	QString db;
	SQLiteConnection* conn;
};

#endif /* SRC_COLLECTION_CLEMENTINECOLLECTION_H_ */
