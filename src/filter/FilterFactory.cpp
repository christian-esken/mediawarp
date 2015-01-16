/*
 * FilterFactory.cpp
 *
 *  Created on: 15.01.2015
 *      Author: chris
 */

#include <src/filter/FilterFactory.h>

#include <QRegularExpression>
#include <QString>
#include <QStringList>

#include "ChainedAndFilter.h"
#include "AudiobookFilter.h"
#include "UnhearedFilter.h"
#include "../util/Param.h"

FilterFactory::FilterFactory()
{
}

FilterFactory::~FilterFactory()
{
}

/**
 * Factory that creates a Filter from a QString
 *
 * @param filterString
 * @return
 */
BaseFilter* FilterFactory::build(QString filterString)
{
	QStringList filterList = filterString.split(',', QString::SplitBehavior::SkipEmptyParts);
	ChainedAndFilter* filterChain = new ChainedAndFilter();
	QRegularExpression::PatternOption ci = QRegularExpression::CaseInsensitiveOption;
	for (QString filterString : filterList)
	{
		FilterInterface* filter = 0;
		bool reverse = filterString.startsWith('-');

		if (QRegularExpression("^-?unheared$", ci).match(filterString).hasMatch())
			filter = new UnhearedFilter();
		else if (QRegularExpression("^-?audiobook$", ci).match(filterString).hasMatch())
			filter = new AudiobookFilter();
		else
		{
			Param::errorexit(QString("Unknown filter: ") + filterString, 1);
		}

		if (filter != 0)
		{
			filter->setReverse(reverse);
			filterChain->addFilter(filter);
		}
	}

	return filterChain;
}


