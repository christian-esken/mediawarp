/*
 * MediawarpDAO.h
 *
 *  Created on: 17.01.2015
 *      Author: chris
 */

#ifndef SRC_DAO_MEDIAWARPDAO_H_
#define SRC_DAO_MEDIAWARPDAO_H_

#include <set>

#include <QString>

#include "../collection/CollectionInterface.h"
#include "../model/MediaItem.h"
#include "../model/Title.h"
#include "../storage/SQLiteConnection.h"
#include "../util/stdnamespaces.h"

class MediawarpDAO
{
public:
	MediawarpDAO();
	virtual ~MediawarpDAO();

	void open();
	void markHandled(int playerId, shared_ptr<CollectionInterface> collection, std::vector<shared_ptr<MediaItem> > selectedSongs);

	shared_ptr<CollectionInterface> getCollection(int collectionId);
	void addCollection(shared_ptr<CollectionInterface> coll);

protected:
	void prepareTables();

	SQLiteConnection* conn;

	bool titlesLoaded = false;
	std::set<shared_ptr<Title> > titles;
	std::vector<shared_ptr<CollectionInterface> > collections;
};

#endif /* SRC_DAO_MEDIAWARPDAO_H_ */
