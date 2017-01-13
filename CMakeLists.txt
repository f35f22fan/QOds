#cmake -G "MinGW Makefiles"
message(STATUS "${CMAKE_CURRENT_LIST_FILE}")
cmake_minimum_required(VERSION 2.8.12)
Project(QOds)

if(WIN32)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.7.1\\5.7\\msvc2015_64\\")
endif (WIN32)

set(LIBRARY_OUTPUT_PATH "${QOds_BINARY_DIR}/lib")

message(STATUS ${CMAKE_SYSTEM}) # print OS name

#set (BUILD_STATIC_LIBRARIES "1")
if (BUILD_STATIC_LIBRARIES)
	set(ODS_STATIC "1")
	set(QUAZIP_STATIC "1")
	set(ZLIB_STATIC "1")
endif (BUILD_STATIC_LIBRARIES)

add_subdirectory(zlib)
add_subdirectory(quazip)
add_subdirectory(ods)
add_subdirectory(app)
