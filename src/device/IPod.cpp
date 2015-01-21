/*
 * IPod.cpp
 *
 *  Created on: 21.01.2015
 *      Author: chris
 */

#include "device/IPod.h"

#include <iostream>

#include <QDir>

IPod::IPod(QString uri) :
	DeviceIfc(uri)
{
}

IPod::~IPod()
{
}

std::vector<shared_ptr<MediaItem> > IPod::load()
{
	std::vector<shared_ptr<MediaItem> > titles;

	GError* error = nullptr;
	Itdb_iTunesDB* db = itdb_parse(QDir::toNativeSeparators(uri).toLocal8Bit(), &error);
	if (db != 0)
	{
		std::cerr << " iPod database for device " << qPrintable(uri) << " succesfully opened." << std::endl;
	}
	else if (error != 0)
	{
		throw std::runtime_error(
			std::string("Error reading iPod database for device ") + qPrintable(uri) + " , error=" + error->message);
	}
	else
	{
		throw std::runtime_error(
			std::string("Error reading iPod database for device ") + qPrintable(uri) + " , error=DB and error are both null");
	}


	for (GList* tracks = db->tracks; tracks != nullptr; tracks = tracks->next)
	{
		Itdb_Track* track = static_cast<Itdb_Track*>(tracks->data);
		shared_ptr<MediaItem> mi(new MediaItem());
		mi->setGenre(track->genre);
		mi->setFilename(track->ipod_path);
		mi->setRating(track->rating);
		mi->setPlaycount(track->playcount);
		// TODO Continue to add all the other fields
		titles.push_back(mi);
	}

	return titles;
}

std::vector<QString> IPod::listDevices()
{
	// TODO Implement "probing", e.g. via Solid or getmntent()
	std::vector<QString> devs;
	devs.push_back("/run/media/chris/BEAUMONDE");
	return devs;
}
