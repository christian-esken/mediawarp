# mediawarp - Warp Media to your mobile devices easily

mediawarp is a tool that warps your favorite MP3's to your Media player.
It is specially designed that it allows you to fill your player with one click.
It can add new songs, and also rediscover music you may have forgotten. It
keeps track of your media players content, and can exchange the media on it.

## Status
Important note: mediawarp is in development, and Alpha status is planned
for March 2015. Media device support shall be:
 - iPod (primary)
 - MTP (secondary)
 - generic USB drive (needs volunteer)

## Rule based filling of your media player
mediawarp interacts with your favorite music collection, and the plan
is to let it interact with as many Collections a possible, like:
 - Clementine (currently the development focus)
 - Amarok (needs volunteer)
 - Synology Media Station (definitely planned)
 - iTunes media server (may need volunteer)

You can use two types of selectors:
 - Sorting (basically done)
 - Filters (tbd)
 - Max Limit (done)

## Sorting
 Described at section "Running"
 
## Filters (tbd)
- "Last 3 albums"
- "100 random songs"
- "50 songs not yet heard"
- "My 30 favorite tunes"

You can combine as many rules as possibe. Also, all rules allow randomness, so
for example the "30 favorite tunes" can vary if you want. For example, you could define
randomness to be 75%. In that case, 3 out of 4 of your most favorite songs will be skipped, but
the selection will still contain 30 songs.


## Building
Build requires CMake.
Most important dependency is a C++11 capable compiler and a Qt5 development environment.

```
mkdir mediawarp.obj
cd mediawarp.obj
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../mediawarp
make
make install
```

Run with
```
mediawarp

# In general:
mediawarp <count> <sort-rules>

# Example: 50 songs sorted by LIKING ASC, if a tie use RANDOM
mediawarp 50 +LIKING,RANDOM

# Example: 100 completely random songs
mediawarp 100 RANDOM
```

Supported sort rules fore all media collections are:
- NAME     - Complete name of the file, including path elements if the media collection support it
- LIKING   - Liking, as given by the media collection (may be based on a rating, listen count, or anything else)
- RANDOM   - Completely random order
- INDEX    - Always a fixed order, as given by the media collection

## License
Apache License 2.0

Copyright 2015-present Christian Esken

