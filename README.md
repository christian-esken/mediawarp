# mediawarp - Warp Media to your mobile devices easily

mediawarp is a tool that warps your favorite MP3's to your Media player.
It is specially designed as a 1-click fill-your-player solution.
It can add new songs by rules or randomly, helping you to rediscover music you may have forgotten. It
keeps track of your media players content, and can exchange the media on it.

## Status
Important note: mediawarp is in development, and Alpha status is planned
for March 2015. You can already use it to easily create favorite playlists,
but you need a separate application like Clementine to sync the files to your
media player.   


## Media player support
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

You can use the following criteria:
 - Sorting (done)
 - Filters (done)
 - Max Limit (done)

## Sorting
 Described at section "Running"
 
## Filters (tbd)
- "Last 3 albums" (open)
- "100 random songs" (done)
- "50 songs not yet heard" (done)
- "My 30 favorite tunes" (done

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

# Example: Your 50 most liked songs
mediawarp 50 titles +LIKING,RANDOM

# Example: 1 random audiobook
mediawarp 1 album random audiobook

# Example: 100 completely random songs (titles), excluding audiobooks 
mediawarp 100 titles random -audiobook

```

Supported sort rules fore all media collections are:
- NAME     - Complete name of the file, including path elements if the media collection support it
- LIKING   - Liking, as given by the media collection (may be based on a rating, listen count, or anything else)
- RANDOM   - Completely random order
- INDEX    - Always a fixed order, as given by the media collection

## License
Apache License 2.0

Copyright 2015-present Christian Esken

