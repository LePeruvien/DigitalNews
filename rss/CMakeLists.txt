CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(DigitalNews-rss)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMake/;${CMAKE_MODULE_PATH}")

FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
FIND_PACKAGE(XalanC REQUIRED)
FIND_PACKAGE(XercesC REQUIRED)

INCLUDE_DIRECTORIES(
	libs/feedreader/include/feedreader
	${XALAN_INCLUDE_DIR}
	${XERCESC_INCLUDE}
)

ADD_LIBRARY(
	feedreader
	SHARED
	libs/feedreader/src/Curl.cpp
	libs/feedreader/src/Curl.hpp
	libs/feedreader/src/Entry.cpp
	libs/feedreader/src/FeedConfig.cpp
	libs/feedreader/src/Feed.cpp
	libs/feedreader/src/MemParseHandlers.cpp
	libs/feedreader/src/StdAfx.cpp
	libs/feedreader/src/Utils.cpp
	libs/feedreader/src/Validator.cpp
	libs/feedreader/src/XmlGlobalState.cpp
	libs/feedreader/include/feedreader/Curl.hpp
	libs/feedreader/include/feedreader/Entry.hpp
	libs/feedreader/include/feedreader/export_cfg.hpp
	libs/feedreader/include/feedreader/FeedConfig.hpp
	libs/feedreader/include/feedreader/Feed.hpp
	libs/feedreader/include/feedreader/MemParseHandlers.hpp
	libs/feedreader/include/feedreader/StdAfx.hpp
	libs/feedreader/include/feedreader/Utils.hpp
	libs/feedreader/include/feedreader/Validator.hpp
	libs/feedreader/include/feedreader/XmlGlobalState.hpp
)

ADD_EXECUTABLE(
	rss
	src/main.cpp
)

TARGET_LINK_LIBRARIES(
	feedreader
	${Boost_LIBRARIES}
	${XALAN_LIBRARIES}
	${XERCESC_LIBRARY}
)

TARGET_LINK_LIBRARIES(
	rss-ivy
	feedreader
)
