/*
 * AudiobookFilter.h
 *
 *  Created on: 12.01.2015
 *      Author: chris
 */

#ifndef AudiobookFILTER_H_
#define AudiobookFILTER_H_

#include "BaseFilter.h"

#include <QStringList>

class AudiobookFilter: public BaseFilter
{
public:
	AudiobookFilter(QStringList tags, QStringList folders);
	virtual ~AudiobookFilter();

	virtual bool match(shared_ptr<MediaItem> mediaItem);

protected:
	bool matchFolders(shared_ptr<MediaItem> mediaItem);
	bool matchTags(shared_ptr<MediaItem> mediaItem);

	QList<QRegularExpression> tagExpressions;
	QList<QRegularExpression> folderExpressions;
};

#endif /* AudiobookFILTER_H_ */
