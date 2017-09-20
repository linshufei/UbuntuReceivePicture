/****************************************************************************
filename:           ReceiveRTP.cpp
Author:             linlongqing
Date:               2017/9/14
Discription:

****************************************************************************/
#include "ReceiveRTP.h"
#include <iostream>

using namespace jrtplib;

#define MAX_BUFF_SIZE 1920 * 1080

ReceiveRTP::ReceiveRTP()
{
    pos = 0;
    portBase = 8000;
    timeStampUnit = 1.0 / 90000.0;
}

void ReceiveRTP::Init()
{

#ifdef WIN32  
    WSADATA dat;
    WSAStartup(MAKEWORD(2, 2), &dat);
#endif // WIN32 

    transParams.SetPortbase(portBase);
    sessParams.SetAcceptOwnPackets(true);
    sessParams.SetOwnTimestampUnit(portBase);

    int status = sess.Create(sessParams, &transParams);
    CheckError(status);

    sess.BeginDataAccess();
    pBuff = new uint8_t[MAX_BUFF_SIZE];
}

void ReceiveRTP::Destroy()
{
    if (NULL != pBuff)
    {
        delete[] pBuff;
    }

    sess.EndDataAccess();
    delay = RTPTime(10.0);
    sess.BYEDestroy(delay, 0, 0);
}

void ReceiveRTP::CheckError(int rtpErr)
{
    if (rtpErr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtpErr) << std::endl;
        exit(-1);
    }
}

int ReceiveRTP::GetFirstSourceWithData()
{
    int status = sess.Poll();
    CheckError(status);
    if (sess.GotoFirstSourceWithData())
    {
        return 1;
    }

    return 0;
}

int ReceiveRTP::GotoNextSourceWithData()
{
    return sess.GotoNextSourceWithData();
}

int ReceiveRTP::GetH264Packet()
{
    uint8_t* loadData;
    while ((pack = sess.GetNextPacket()) != NULL)
    {
        loadData = pack->GetPayloadData();
        int len = pack->GetPayloadLength();

        if (pack->GetPayloadType() == 96) //有效负载(载荷)类型 loadType H264=96
        {
            if (pack->HasMarker()) // the last packet
            {
                memcpy(&pBuff[pos], loadData, len);
                int size = len + pos;
                sess.DeletePacket(pack);
                pos = 0;
                return size;
            }
            else
            {
                memcpy(&pBuff[pos], loadData, len);
                pos = pos + len;
            }
        }
        else
        {
            printf("!!!  GetPayloadType = %d !!!! \n ", pack->GetPayloadType());
        }

        sess.DeletePacket(pack);
    }

    return 0;
}

int ReceiveRTP::GetJPEGPacket()
{
	uint8_t* loadData;
	while ((pack = sess.GetNextPacket()) != NULL)
	{
		loadData = pack->GetPayloadData();
		int len = pack->GetPayloadLength();
		if (pack->GetPayloadType() == 26) //有效负载(载荷)类型 loadType H264=96
		{
			if (pack->HasMarker()) // the last packet
			{
				memcpy(&pBuff[pos], loadData, len);
				int size = len + pos;
				sess.DeletePacket(pack);
				pos = 0;
				return size;
			}
			else
			{
				memcpy(&pBuff[pos], loadData, len);
				pos = pos + len;
			}
		}
		else
		{
			printf("!!!  GetPayloadType = %d !!!! \n ", pack->GetPayloadType());
		}

		sess.DeletePacket(pack);
	}

	return 0;
}