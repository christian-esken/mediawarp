/*
 * DeviceIfc.cpp
 *
 *  Created on: 21.01.2015
 *      Author: chris
 */

#include <device/DeviceIfc.h>

DeviceIfc::DeviceIfc(QString uri) : uri(uri)
{
}

DeviceIfc::~DeviceIfc()
{
}

std::vector<shared_ptr<MediaItem> > DeviceIfc::load()
{
	throw std::runtime_error(std::string("DeviceIfc should not be instanciated" ));

}
