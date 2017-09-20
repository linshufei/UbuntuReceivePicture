/****************************************************************************
filename:           ReceiveRTP.h
Author:             linlongqing
Date:               2017/9/13
Discription:

****************************************************************************/
#pragma once
#include "jrtp/rtpsession.h"
#include "jrtp/rtpudpv4transmitter.h"
#include "jrtp/rtpipv4address.h"
#include "jrtp/rtpsessionparams.h"
#include "jrtp/rtperrors.h"
#include "jrtp/rtppacket.h"

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <netinet/in.h>  
#include <arpa/inet.h>  
#endif //_WIN32

#pragma comment(lib,"avcodec.lib")  
#pragma comment(lib,"avdevice.lib")  
#pragma comment(lib,"avfilter.lib")  
#pragma comment(lib,"avformat.lib")  
#pragma comment(lib,"avutil.lib")  
#pragma comment(lib,"swscale.lib")
#pragma comment(lib,"jrtplib.lib")

class ReceiveRTP
{
private:
    int pos;
    uint16_t portBase;
    jrtplib::RTPSession sess;
    jrtplib::RTPSessionParams sessParams;
    jrtplib::RTPUDPv4TransmissionParams transParams;

    double timeStampUnit;
    jrtplib::RTPPacket* pack;
    jrtplib::RTPTime delay{ 0.001 };

    void CheckError(int rtpErr);
public:
    uint8_t *pBuff;

    ReceiveRTP();
    ~ReceiveRTP(){};

    void Init();
    void Destroy();
    int GetH264Packet();
	int GetJPEGPacket();
    int GetFirstSourceWithData();
    int GotoNextSourceWithData();
};