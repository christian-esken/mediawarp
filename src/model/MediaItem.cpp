#include "MediaItem.h"

#include <iostream>
#include <stdlib.h>

int MediaItem::indexCounter = 1;

MediaItem::MediaItem() :
	filename(QString()), playcount(0), skipcount(0), lengthMillis(0), lastplayedMillis(0), currentPlayposition(0), ctimeMillis(0),
		mtimeMillis(0), atimeMillis(0), genre(QString()), score(0), rating(0)
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
	os << "score=" << score << " ";
	os << "rating=" << rating << " ";
	os << "playcount=" << playcount << " ";
	if (filename.isNull())
		os << "-null";
	else
		os << qPrintable(filename);
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
	return filename;
}

const QString MediaItem::getAlbum() const
{
	// TODO implement properly. This "field" possibly needs to go to the constructor
	int slashIndex = filename.lastIndexOf('/');
	return slashIndex == -1 ? QString() : filename.left(slashIndex-1);
}

const QString MediaItem::getTitle() const
{
	// TODO implement properly. This "field" possibly needs to go to the constructor
	int slashIndex = filename.lastIndexOf('/');
	return slashIndex == -1 ? filename : filename.mid(slashIndex);
}

void MediaItem::setFilename(const QString& filename)
{
	this->filename = filename;
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

int MediaItem::getRating() const
{
	return rating;
}

void MediaItem::setRating(int rating)
{
	this->rating = rating;
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


