/*
 * CollectionInterface.cpp
 *
 *  Created on: 13.01.2015
 *      Author: chris
 */

#include "CollectionInterface.h"

#include <exception>


CollectionInterface::CollectionInterface(int collectionId) : collectionId(collectionId)
{
}

CollectionInterface::~CollectionInterface()
{
}

std::vector<shared_ptr<MediaItem> > CollectionInterface::load()
{
	throw std::runtime_error(std::string("CollectionInterface should not be instanciated" ));
}
