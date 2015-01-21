/*
 * Title.h
 *
 *  Created on: 19.01.2015
 *      Author: chris
 */

#ifndef SRC_MODEL_TITLE_H_
#define SRC_MODEL_TITLE_H_

#include <QString>

#include "../collection/CollectionInterface.h"
#include "../util/stdnamespaces.h"

class Title
{
public:
	Title(int title_id,	shared_ptr<CollectionInterface> collection,	QString uri);
	virtual ~Title();


	const shared_ptr<CollectionInterface>& getCollection() const
	{
		return collection;
	}

	int getTitleId() const
	{
		return title_id;
	}

	const QString& getUri() const
	{
		return uri;
	}


protected:
	int title_id;
	shared_ptr<CollectionInterface> collection;
	QString uri;

};

inline bool operator== (const Title& lhs, const Title& rhs);
inline bool operator<(const Title& lhs, const Title& rhs);

// The relevant operrator for set::find() is below, as all collections hold shared_ptr<> instances
bool operator<(const shared_ptr<Title>& lhs, const shared_ptr<Title>& rhs);


#endif /* SRC_MODEL_TITLE_H_ */
