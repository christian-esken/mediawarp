/*
 * MediawarpDAO.h
 *
 *  Created on: 17.01.2015
 *      Author: chris
 */

#ifndef SRC_DAO_MEDIAWARPDAO_H_
#define SRC_DAO_MEDIAWARPDAO_H_

#include <QString>

#include "../model/MediaItem.h"
#include "../storage/SQLiteConnection.h"
#include "../util/stdnamespaces.h"

class MediawarpDAO
{
public:
	MediawarpDAO();
	virtual ~MediawarpDAO();

	void open();
	void markHandled(int playerId, int collectionId, std::vector<shared_ptr<MediaItem> > selectedSongs);

protected:
	void prepareTables();

	SQLiteConnection* conn;
};

#endif /* SRC_DAO_MEDIAWARPDAO_H_ */
