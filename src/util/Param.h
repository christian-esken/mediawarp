/*
 * Param.h
 *
 *  Created on: 15.01.2015
 *      Author: chris
 */

#ifndef SRC_UTIL_PARAM_H_
#define SRC_UTIL_PARAM_H_

#include "Constants.h"

#include <QString>


class Param
{
public:
	Param(int argc, char *argv[]);
	virtual ~Param();

	int getLimit() const
	{
		return limit;
	}


	static void errorexit(QString msg, int status);

//	mediawarp::Constants::MediaType getMediaType() const
//	{
//		return mediaType;
//	}

	mediawarp::Constants::Unit getUnit() const
	{
		return unit;
	}

	const QString& getFilter() const
	{
		return filter;
	}

	const QString& getOrder() const
	{
		return order;
	}

private:
	int limit;
	QString order;
	QString filter;
//	mediawarp::Constants::MediaType mediaType;
	mediawarp::Constants::Unit unit;

};

#endif /* SRC_UTIL_PARAM_H_ */
