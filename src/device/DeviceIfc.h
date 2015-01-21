/*
 * DeviceIfc.h
 *
 *  Created on: 21.01.2015
 *      Author: chris
 */

#ifndef SRC_DEVICE_DEVICEIFC_H_
#define SRC_DEVICE_DEVICEIFC_H_

#include <vector>

#include <QString>

#include "model/MediaItem.h"
#include "util/stdnamespaces.h"

class DeviceIfc
{
public:
	DeviceIfc(QString uri);
	virtual ~DeviceIfc();

	virtual std::vector<shared_ptr<MediaItem> > load();


	virtual std::vector<QString> listDevices() = 0;

	const QString& getUri() const
	{
		return uri;
	}


protected:
	QString uri;
};

#endif /* SRC_DEVICE_DEVICEIFC_H_ */
