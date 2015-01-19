/*
 * Title.cpp
 *
 *  Created on: 19.01.2015
 *      Author: chris
 */

#include <model/Title.h>

Title::Title(int title_id,	shared_ptr<CollectionInterface> collection, QString uri) :
title_id(title_id), collection(collection), uri(uri)
{
}

Title::~Title()
{
}

inline bool operator== (const Title& lhs, const Title& rhs)
{
	if (lhs.getCollection()->getCollectionId() != rhs.getCollection()->getCollectionId() )
		return false;

	if (lhs.getUri() != rhs.getUri())
		return false;

	return true;

}

/**
 * Natural order by index
 * @param other
 * @return
 */
inline bool operator<(const Title& lhs, const Title& rhs)
{
	int diff = lhs.getCollection()->getCollectionId() - rhs.getCollection()->getCollectionId();
	if (diff < 0)
		return false;
	if (diff > 0)
		return true;

	diff = lhs.getUri().compare(rhs.getUri());
	if (diff < 0)
		return false;
	if (diff > 0)
		return true;

	return false;
}

bool operator<(const shared_ptr<Title>& lhs, const shared_ptr<Title>& rhs)
{
	int diff = lhs->getCollection()->getCollectionId() - rhs->getCollection()->getCollectionId();
	if (diff < 0)
		return false;
	if (diff > 0)
		return true;

	diff = lhs->getUri().compare(rhs->getUri());
	if (diff < 0)
		return false;
	if (diff > 0)
		return true;

	return false;
}
