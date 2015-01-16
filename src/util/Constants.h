/*
 * Constants.h
 *
 *  Created on: 15.01.2015
 *      Author: chris
 */

#ifndef SRC_UTIL_CONSTANTS_H_
#define SRC_UTIL_CONSTANTS_H_

namespace mediawarp
{

class Constants
{
public:
	Constants();
	virtual ~Constants();

	enum Unit { Album, Title, Duration };
//	enum MediaType { ANY, Song, AudioBook, Podcast };
};

} /* namespace mediawarp */

#endif /* SRC_UTIL_CONSTANTS_H_ */
