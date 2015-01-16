/*
 * AudiobookFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "AudiobookFilter.h"

#include <QRegularExpression>
#include <QString>

AudiobookFilter::AudiobookFilter() : BaseFilter()
{
}

AudiobookFilter::~AudiobookFilter()
{
}


bool AudiobookFilter::match(shared_ptr<MediaItem> mediaItem)
{
	const QString filename = mediaItem->getFilename();

	QRegularExpression::PatternOption ci = QRegularExpression::CaseInsensitiveOption;

	// TODO This is an experimental implementation.
	// Final solution must be multi-language, user-configurable, and also look at ID3 Tags.
	// Additionally, we might only look for full path elements, e.g. ".*/hoerbuch/.*"

	if (QRegularExpression("h(oe|ö)rspiele?", ci).match(filename).hasMatch())
		return true;

	if (QRegularExpression("h(oe|ö)rb(uch|ücher)", ci).match(filename).hasMatch())
		return true;

	if (QRegularExpression("audiobooks?", ci).match(filename).hasMatch())
		return true;

	return false;
}
