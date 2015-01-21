/*
 * IPod.h
 *
 *  Created on: 21.01.2015
 *      Author: chris
 */

#ifndef SRC_DEVICE_IPOD_H_
#define SRC_DEVICE_IPOD_H_

#include <device/DeviceIfc.h>

#include <glib.h>
#include <gpod/itdb.h>

//#include <itdb.h>
//#include <gpod-1.0/gpod/itdb.h>

class IPod: public DeviceIfc
{
public:
	IPod(QString uri);
	virtual ~IPod();

	virtual std::vector<shared_ptr<MediaItem> > load() override;

	virtual std::vector<QString> listDevices() override;
};

#endif /* SRC_DEVICE_IPOD_H_ */
