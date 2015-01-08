
cmake_minimum_required (VERSION 2.6)
project (mediawarp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 


  message("xyz")

set (mediawarp_VERSION_MAJOR 1)
set (mediawarp_VERSION_MINOR 0)

#find_package (BZip2)
find_package (Sqlite REQUIRED)
find_package (Qt5Core REQUIRED)
find_package (Qt5Sql REQUIRED)
#find_package(Qt5Widgets)

#  Qt5::Core

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/mediawarpConfig.h.in"
  "${PROJECT_BINARY_DIR}/mediawarpConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find mediawarpConfig.h
include_directories("${PROJECT_BINARY_DIR}")




add_executable(mediawarp
src/main.cpp
src/storage/SQLiteConnection.cpp
src/model/MediaItem.cpp
src/selection/MediaItemSortFunctions.cpp
)



target_link_libraries(mediawarp
  Qt5::Core
  Qt5::Sql
  )

    
if (BZIP2_FOUND)
  include_directories(${BZIP_INCLUDE_DIRS})
  target_link_libraries (mediawarp ${BZIP2_LIBRARIES})
endif (BZIP2_FOUND)
