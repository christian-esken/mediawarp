#ifndef X_MediaItem
#define X_MediaItem

#include <QString>

#include <iostream>
#include "../util/stdnamespaces.h"

class MediaItem
{
public:
	MediaItem();
	~MediaItem();

	long getAtimeMillis() const;
	void setAtimeMillis(long atimeMillis);
	long getCtimeMillis() const;
	void setCtimeMillis(long ctimeMillis);
	long getCurrentPlayposition() const;
	void setCurrentPlayposition(long currentPlayposition);
	const QString& getFilename() const;
	void setUri(const QString& filename);
	const QString& getGenre() const;
	void setGenre(const QString& genre);
	long getLastplayedMillis() const;
	void setLastplayedMillis(long lastplayedMillis);
	long getLengthMillis() const;
	void setLengthMillis(long lengthMillis);
	long getMtimeMillis() const;
	void setMtimeMillis(long mtimeMillis);
	int getPlaycount() const;
	void setPlaycount(int playcount);
	int getStarrating() const;
	QString getStarratingString() const;

	void setStarrating(int rating);
	int getScore() const;
	void setScore(int score);
	int getSkipcount() const;
	void setSkipcount(int skipcount);



//	int operator<(const MediaItem& other);

	std::ostream& toStream(std::ostream& os) const;
//	uint qHash ( const MediaItem & key );

	int getIndex() const;
	int getRandomizer() const;

	const QString& getArtist() const
	{
		return artist;
	}

	void setArtist(const QString& artist)
	{
		this->artist = artist;
	}

	const QString& getComposer() const
	{
		return composer;
	}

	void setComposer(const QString& composer)
	{
		this->composer = composer;
	}

	void setTitle(const QString& title)
	{
		this->title = title;
	}

	void setAlbum(const QString& album)
	{
		this->album = album;
	}

	const QString& getAlbum() const
	{
		return album;
	}

	const QString& getTitle() const
	{
		return title;
	}

private:
  QString uri;
  QString title;
  QString album;
  QString artist;
  QString composer;

  int playcount;
  int skipcount;
  long lengthMillis;
  long lastplayedMillis;
  long currentPlayposition;

  long ctimeMillis;
  long mtimeMillis;
  long atimeMillis;

  QString genre;

  int score;  // 0 - 10000
  int starrating; // 0 - 10000

  // Technical fields
  int index;
  int randomizer;

  static int indexCounter;
};

std::ostream& operator<< (std::ostream& os, const MediaItem& mediaItem);

/**
 * Natural order by index
 * @param other
 * @return
 */
inline bool operator< (const MediaItem& lhs, const MediaItem& rhs)
{
	std::cerr << "operator<() should not be called";
	exit(1);
	return lhs.getIndex() < rhs.getIndex();
}

inline bool operator== (const MediaItem& lhs, const MediaItem& rhs)
{
	std::cerr << "operator==() should not be called";
	exit(1);
	return lhs.getIndex() == rhs.getIndex();
}

#define MediaItem_T shared_ptr<MediaItem>
//#define MediaItem_T *MediaItem

#endif

