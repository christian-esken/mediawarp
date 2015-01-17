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
#include <QStringList>

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

	const QStringList getFolderExpressions() const
	{
		QStringList folderExpressions;
		folderExpressions.clear();
		folderExpressions.append(QString("audiobooks?"));
		folderExpressions.append("h(oe|ö)rspiele?");
		folderExpressions.append("h(oe|ö)rb(uch|ücher)");
		return folderExpressions;
	}

	const QStringList getTagExpressions() const
	{
		QStringList tagExpressions;
		tagExpressions.clear();
		tagExpressions.append("audiobook");
		tagExpressions.append("h(oe|ö)rspiel");
		tagExpressions.append("h(oe|ö)rbuch");

		return tagExpressions;
	}

//
//	QStringList folderExpressions;
//	folderExpressions.append("h(oe|ö)rspiele?");
//	folderExpressions.append("h(oe|ö)rb(uch|ücher)");
//	folderExpressions.append("audiobooks?");

private:
	int limit;
	QString order;
	QString filter;
//	mediawarp::Constants::MediaType mediaType;
	mediawarp::Constants::Unit unit;

//	QStringList tagExpressions;
//	QStringList folderExpressions;

};

#endif /* SRC_UTIL_PARAM_H_ */
