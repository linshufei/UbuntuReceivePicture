cmake_minimum_required(VERSION 2.8)
project(ReceiveSocket)

set(CMAKE_CXX_STANDARD 11)

set(FFMPEG_LIBS libavcodec.so libavformat.so libavutil.so)
set(JRTP_LIBS /usr/local/lib/libjrtp.so)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/usr/local/include)

set(SOURCE_FILES main.cpp ReceiveSocket.h ReceiveSocket.cpp
        JPEGDecoder.h JPEGDecoder.cpp
        ReceiveRTP.h ReceiveRTP.cpp
        H264Decoder.h H264Decoder.cpp
        JPEGEncoder.h JPEGEncoder.cpp)
add_executable(ReceiveSocket ${SOURCE_FILES})

target_link_libraries(ReceiveSocket
        ${OpenCV_LIBS}
        ${FFMPEG_LIBS}
        ${JRTP_LIBS}
        )
