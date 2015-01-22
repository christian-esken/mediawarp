#include "MediaItem.h"

#include <iostream>
#include <stdlib.h>

int MediaItem::indexCounter = 1;

MediaItem::MediaItem() :
	uri(QString()), playcount(0), skipcount(0), lengthMillis(0), lastplayedMillis(0), currentPlayposition(0), ctimeMillis(0),
		mtimeMillis(0), atimeMillis(0), genre(QString()), score(0), starrating(0)
{
	index = indexCounter;
	++indexCounter;
	randomizer = rand();

//	std::cout << "Created MediaItem: " << this << std::endl;
}

MediaItem::~MediaItem()
{
//	std::cout << "Deleted MediaItem: " << this << std::endl;
}

///**
// * Natural order by index
// * @param other
// * @return
// */
//int MediaItem::operator<(const MediaItem& other)
//{
//	return index - other.index;
//}



std::ostream& operator<< (std::ostream& os, const MediaItem& mediaItem)
{
	return mediaItem.toStream(os);
}

//uint qHash ( const MediaItem & key )
//{
//	return key.getIndex();
//}

std::ostream& MediaItem::toStream(std::ostream& os) const
{
//	os.operator<<(122);
//	std::string s;
	os << index << ". ";
	os << qPrintable(artist) << " - ";
	os << qPrintable(album) << " - ";
	os << qPrintable(title) << " | ";
	os << "score=" << score << "% ";
	os << qPrintable(getStarratingString());
	if (playcount > 0)
		os << " #" << playcount;
	else
		os << " #unheared";

//	if (uri.isNull())
//		os << "-null";
//	else
//		os << qPrintable(uri);
//	os << s;//"122"; //index;
//	os << filename.toUtf8().constData();
//	os << filename.toUtf8();
	return os;
}

long MediaItem::getAtimeMillis() const
{
	return atimeMillis;
}

void MediaItem::setAtimeMillis(long atimeMillis)
{
	this->atimeMillis = atimeMillis;
}

long MediaItem::getCtimeMillis() const
{
	return ctimeMillis;
}

void MediaItem::setCtimeMillis(long ctimeMillis)
{
	this->ctimeMillis = ctimeMillis;
}

long MediaItem::getCurrentPlayposition() const
{
	return currentPlayposition;
}

void MediaItem::setCurrentPlayposition(long currentPlayposition)
{
	this->currentPlayposition = currentPlayposition;
}

const QString& MediaItem::getFilename() const
{
	return uri;
}

//const QString MediaItem::getAlbum() const
//{
//	// TODO implement properly. This "field" possibly needs to go to the constructor
//	int slashIndex = uri.lastIndexOf('/');
//	return slashIndex == -1 ? QString() : uri.left(slashIndex);
//}
//
//const QString MediaItem::getTitle() const
//{
//	// TODO implement properly. This "field" possibly needs to go to the constructor
//	int slashIndex = uri.lastIndexOf('/');
//	return slashIndex == -1 ? uri : uri.mid(slashIndex-1);
//}

void MediaItem::setUri(const QString& filename)
{
	this->uri = filename;
//	this->filename.detach();
}

const QString& MediaItem::getGenre() const
{
	return genre;
}

void MediaItem::setGenre(const QString& genre)
{
	this->genre = genre;
}

long MediaItem::getLastplayedMillis() const
{
	return lastplayedMillis;
}

void MediaItem::setLastplayedMillis(long lastplayedMillis)
{
	this->lastplayedMillis = lastplayedMillis;
}

long MediaItem::getLengthMillis() const
{
	return lengthMillis;
}

void MediaItem::setLengthMillis(long lengthMillis)
{
	this->lengthMillis = lengthMillis;
}

long MediaItem::getMtimeMillis() const
{
	return mtimeMillis;
}

void MediaItem::setMtimeMillis(long mtimeMillis)
{
	this->mtimeMillis = mtimeMillis;
}

int MediaItem::getPlaycount() const
{
	return playcount;
}

void MediaItem::setPlaycount(int playcount)
{
	this->playcount = playcount;
}

int MediaItem::getStarrating() const
{
	return starrating;
}

QString MediaItem::getStarratingString() const
{
	if (starrating < 10)
		return QString("-");
	if (starrating < 20)
		return QString("*");
	if (starrating < 30)
		return QString("**");
	if (starrating < 40)
		return QString("***");
	if (starrating < 50)
		return QString("****");

	// (starrating == 50)
	return QString("*****");
}

/**
 * Set the star rating in the range [0 .. 50].
 * For example 40 = 4.0 stars = "****", or 35 = 3.5 stars = "***+"
 *
 * @param rating
 */
void MediaItem::setStarrating(int rating)
{
	if (rating > 50)
		rating = 50;
	else if (rating < 0)
		rating = 0;
	this->starrating = rating;
}

int MediaItem::getScore() const
{
	return score;
}

void MediaItem::setScore(int score)
{
	this->score = score;
}

int MediaItem::getSkipcount() const
{
	return skipcount;
}

void MediaItem::setSkipcount(int skipcount)
{
	this->skipcount = skipcount;
}

int MediaItem::getIndex() const
{
	return index;
}

int MediaItem::getRandomizer() const
{
	return randomizer;
}


