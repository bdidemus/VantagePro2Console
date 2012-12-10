cmake_minimum_required(VERSION 2.6)

project(VantagePro2Console)

set(APP_NAME DavisConsole)

include ( CheckIncludeFile )
include ( CheckCSourceCompiles )

find_package( CURL REQUIRED )

# A whole lot of unix gcc/g++ mess
set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb -W -Wall -Wno-long-long -Wno-unused" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++0x" )
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -W -Wall -Wno-long-long -Wno-unused" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c++0x" )

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}/include
	CURL_INCLUDE_DIR
)

file( GLOB_RECURSE EXECUTABLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	src/postdata.cpp
	src/vantageconsole.cpp
	src/VantageData.cpp
	src/main.cpp
)

add_executable( ${APP_NAME} ${EXECUTABLE_SRCS} )

target_link_libraries( ${APP_NAME}
	${CURL_LIBRARY}
)

message( "All done!" )





