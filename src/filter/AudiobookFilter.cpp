/*
 * AudiobookFilter.cpp
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#include "AudiobookFilter.h"

#include <QRegularExpression>
#include <QString>

AudiobookFilter::AudiobookFilter(QStringList tags, QStringList folders) : BaseFilter()
{
	// Precompile regexp's, as they are used several thousand times
	QRegularExpression::PatternOption ci = QRegularExpression::CaseInsensitiveOption;

	for (const QString& tag : tags)
	{
		tagExpressions.append(QRegularExpression(tag, ci));
	}

	for (const QString& folder : folders)
	{
		folderExpressions.append(QRegularExpression(folder, ci));
	}
}

AudiobookFilter::~AudiobookFilter()
{
}


bool AudiobookFilter::match(shared_ptr<MediaItem> mediaItem)
{
	bool ret = matchFolders(mediaItem);
	if (ret)
		return true;

	ret = matchTags(mediaItem);

	return ret;
}

bool AudiobookFilter::matchFolders(shared_ptr<MediaItem> mediaItem)
{
	// TODO This is an experimental implementation.
	// Final solution must be multi-language, user-configurable, and also look at ID3 Tags.
	// Additionally, we might only look for full path elements, e.g. ".*/hoerbuch/.*"

	const QString& filename = mediaItem->getFilename();
	for (const QRegularExpression& folderExpr : folderExpressions)
	{
		if (folderExpr.match(filename).hasMatch())
			return true;
	}

	return false;
}

bool AudiobookFilter::matchTags(shared_ptr<MediaItem> mediaItem)
{
	// TODO This is an experimental implementation.
	// Final solution must be multi-language, user-configurable, and also look at ID3 Tags.
	// Additionally, we might only look for full path elements, e.g. ".*/hoerbuch/.*"

	const QString& genre = mediaItem->getGenre();

	for (const QRegularExpression& tagExpr : tagExpressions)
	{
		if (tagExpr.match(genre).hasMatch())
			return true;
	}

	return false;
}

