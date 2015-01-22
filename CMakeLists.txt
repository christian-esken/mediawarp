
cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0011 OLD)

project (mediawarp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

include(${CMAKE_MODULE_PATH}/Summary.cmake)
include(${CMAKE_MODULE_PATH}/OptionalSource.cmake)
#include(OptionalSource.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/src
  )
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 



set (mediawarp_VERSION_MAJOR 1)
set (mediawarp_VERSION_MINOR 0)

#find_package (BZip2)
find_package (Sqlite REQUIRED)
find_package (Qt5Core REQUIRED)
find_package (Qt5Sql REQUIRED)
#find_package(Qt5Widgets)
#  Qt5::Core

find_package(PkgConfig REQUIRED)

#find_package(GLIB2)
pkg_check_modules(GLIB glib-2.0)

###PKG_SEARCH_MODULE(IPOD libgpod-1.0)

pkg_check_modules(LIBGPOD libgpod-1.0>=0.7.92)
pkg_check_modules(LIBMTP libmtp>=1.0)
# pkg_check_modules(TAGLIB REQUIRED taglib>=1.6)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/mediawarpConfig.h.in"
  "${PROJECT_BINARY_DIR}/mediawarpConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find mediawarpConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#include_directories(${TAGLIB_INCLUDE_DIRS})

optional_component(LIBGPOD ON "Devices: iPod classic support"
DEPENDS "libgpod" LIBGPOD_FOUND
)

#
#optional_component(LIBMTP ON "Devices: MTP support"
#DEPENDS "libmtp" LIBMTP_FOUND
#)
 
#optional_component(GIO ON "Devices: GIO device backend"
#DEPENDS "libgio" GIO_FOUND
#DEPENDS "Linux or Windows" "NOT APPLE"
#)

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${GLIBCONFIG_INCLUDE_DIRS})
include_directories(${LIBGPOD_INCLUDE_DIRS})

  
add_executable(mediawarp
src/main.cpp

src/collection/ClementineCollection.cpp
src/collection/CollectionInterface.cpp

src/device/DeviceIfc.cpp
src/device/IPod.cpp

src/dao/MediawarpDAO.cpp

src/filter/FilterFactory.cpp
src/filter/FilterInterface.cpp
src/filter/AlbumFilter.cpp
src/filter/ArtistFilter.cpp
src/filter/AudiobookFilter.cpp
src/filter/BaseFilter.cpp
src/filter/ChainedAndFilter.cpp
src/filter/TagFilter.cpp
src/filter/UnhearedFilter.cpp

src/model/MediaItem.cpp
src/model/Title.cpp

src/selection/ElementSelector.cpp
src/selection/ElementSelectorAlbums.cpp
src/selection/ElementSelectorDuration.cpp
src/selection/ElementSelectorSongs.cpp
src/selection/MediaItemSortFunctions.cpp

src/storage/SQLiteConnection.cpp

src/util/Constants.cpp
src/util/Param.cpp
)

link_directories(${GLIB_LIBRARY_DIRS})
link_directories(${LIBGPOD_LIBRARY_DIRS})

target_link_libraries(mediawarp
  Qt5::Core
  Qt5::Sql
  ${LIBGPOD_LIBRARIES}
  )

    
if (BZIP2_FOUND)
  include_directories(${BZIP_INCLUDE_DIRS})
  target_link_libraries (mediawarp ${BZIP2_LIBRARIES})
endif (BZIP2_FOUND)
