/****************************************************************************
filename:           JPEGDecoder.cpp
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#include "JPEGDecoder.h"
#include <iostream>

CJPEGDecoder::CJPEGDecoder()
{
	avcodec_register_all();
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	pCodec = avcodec_find_decoder(AV_CODEC_ID_MJPEG);
	if (pCodec == nullptr)
	{
		printf("Fail to get decoder !\n");
	}

	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (pCodecCtx == nullptr)
	{
		printf("Fail to get decoder context !\n");
	}

	pCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ444P;
	pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;

	if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0)
	{
		printf("Fail to open decoder !\n");
	}

    pFrame = av_frame_alloc();

    frameCount = 0;
}

CJPEGDecoder::~CJPEGDecoder()
{
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);
	av_free(pFrame);
	if (packet != nullptr)
	{
		av_free(packet);
        packet = nullptr;
	}
}

int CJPEGDecoder::Decode(uint8_t *pDataIn, int nInSize)
{
	packet->size = nInSize;
	packet->data = pDataIn;
    std::cout << nInSize << std::endl;

	int gotPicture;
    int ret = avcodec_decode_video2(pCodecCtx, pFrame, &gotPicture, packet);

	if (ret <= 0)
	{
		printf("Decode Error.\n");
	}
	if (gotPicture)
    {
		return 0;
	}
    else
    {
        std::cout << "does not exist pciture" << std::endl;
    }

	return -1;
}

int CJPEGDecoder::GetSize(int& width, int& height)
{
	width = pFrame->width;
	height = pFrame->height;

	return 0;
}

int CJPEGDecoder::GetData(uint8_t* pData)
{
	memcpy(pData, pFrame->data[0], pFrame->width * pFrame->height * sizeof(uint8_t));
	return 0;
}