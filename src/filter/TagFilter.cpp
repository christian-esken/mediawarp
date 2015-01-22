/*
 * TagFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "TagFilter.h"

TagFilter::TagFilter(QString tagValue) : BaseFilter(), tagValue(tagValue)
{
	QRegularExpression::PatternOption ci = QRegularExpression::CaseInsensitiveOption;
	tagExpr = QRegularExpression(tagValue, ci);
}

TagFilter::~TagFilter()
{
}

