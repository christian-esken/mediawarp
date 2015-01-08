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
	void setFilename(const QString& filename);
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
	int getRating() const;
	void setRating(int rating);
	int getScore() const;
	void setScore(int score);
	int getSkipcount() const;
	void setSkipcount(int skipcount);



//	int operator<(const MediaItem& other);

	std::ostream& toStream(std::ostream& os) const;
//	uint qHash ( const MediaItem & key );

	int getIndex() const;
	int getRandomizer() const;

private:
  QString filename;
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
  int rating; // 0 - 10000

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

