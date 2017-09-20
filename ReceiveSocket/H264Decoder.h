/****************************************************************************
filename:           H264Decoder.h
Author:             linlongqing
Date:               2017/9/12
Discription:

****************************************************************************/

#ifndef __DECODER_H
#define __DECODER_H
#include <stdio.h>

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};

#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL/SDL.h>
#ifdef __cplusplus
};
#endif
#endif

class CH264Decoder
{
private:
    //FFmpeg
    int             frameCount;
    int             videoIndex;
    AVCodec         *pCodec = NULL;
    AVCodecContext  *pCodecCtx = NULL;
    AVFrame         *pFrame = NULL;
    AVPacket        *packet = NULL;
    AVFormatContext *pFormatCtx = NULL;
public:
	CH264Decoder();
	~CH264Decoder();
    int Decode(uint8_t *pDataIn, int nInSize, uint8_t *pDataOut);
	int GetSize(int& width, int& height);
	int GetData(uint8_t *pData);
};

#endif