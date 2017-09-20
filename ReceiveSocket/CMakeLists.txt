cmake_minimum_required(VERSION 3.8)
project(ReceiveSocket)

set(CMAKE_CXX_STANDARD 11)

set(FFMPEG_LIBS libavcodec.so libavformat.so libavutil.so libswscale.so)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp ReceiveSocket.h ReceiveSocket.cpp JPEGDecoder.h JPEGDecoder.cpp)
add_executable(ReceiveSocket ${SOURCE_FILES})
target_link_libraries(ReceiveSocket ${OpenCV_LIBS} ${FFMPEG_LIBS})