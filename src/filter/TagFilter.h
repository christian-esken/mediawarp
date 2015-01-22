/*
 * TagFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef TagFILTER_H_
#define TagFILTER_H_

#include "BaseFilter.h"

#include <QRegularExpression>
#include <QString>

class TagFilter: public BaseFilter
{
public:
	TagFilter(QString tagValue);
	virtual ~TagFilter();

protected:
	QString tagValue;
	QRegularExpression tagExpr;

};

#endif /* TagFILTER_H_ */
