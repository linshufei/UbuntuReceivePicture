/****************************************************************************
filename:           JPEGDecoder.h
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#pragma once
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

class CJPEGDecoder
{
private:
	//FFmpeg
	int             frameCount;
	int             videoIndex;
	AVCodec         *pCodec = nullptr;
	AVFrame         *pFrame = nullptr;
	AVPacket        *packet = nullptr;
	AVCodecContext  *pCodecCtx = nullptr;
public:
	CJPEGDecoder();
	~CJPEGDecoder();
	int Decode(uint8_t *pDataIn, int nInSize);
	int GetSize(int& width, int& height);
	int GetData(uint8_t *pData);

};

