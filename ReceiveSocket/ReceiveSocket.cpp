/****************************************************************************
filename:           ReceiveSocket.cpp
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#include "ReceiveSocket.h"
#include <string.h>


CReceiveSocket::CReceiveSocket()
{
    memset((void*)&addrServer,0,sizeof(addrServer));
    pData = new char[MAX_IMAGE_SIZE];
    //WSAStartup(MAKEWORD(2, 2), &wsaData);
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY��ʾ�κ�IP
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(6000); //�󶨶˿�6000
    sockServer = socket(AF_INET, SOCK_STREAM, 0); //socket(int domain, int type, int protocol)
    bind(sockServer, (struct sockaddr*)&addrServer, sizeof(addrServer));
}

CReceiveSocket::~CReceiveSocket()
{
    if (pData == nullptr)
    {
        delete[] pData;
        pData = nullptr;
    }

    close(sockClient);
   // WSACleanup();
}

int CReceiveSocket::Listen()
{
    listen(sockServer, 1); //only one client can link
    std::cout << "Server start working" << std::endl << "Listening" << std::endl;
    return 0;
}

int CReceiveSocket::AcceptFromClient()
{
    socklen_t len;
    sockClient = accept(sockServer, (struct sockaddr*)& addrClient, &len);
    return 0;
}

int CReceiveSocket::ReceiveFromClient(char* recvBuf, int recvBufLen)
{
    int pos = 0;
    SImageHeader header;
    int len = read(sockClient, &header, sizeof(SImageHeader));
    while (true)
    {
        len = read(sockClient, &recvBuf[pos], 1024);
        pos += len;
        std::cout << "pos:" << pos << "/"<< header.dataSize <<std::endl;
        if (pos >= header.dataSize)
        {
            break;
        }
    }

    std::cout << "length:" << len << std::endl;
    memcpy(pData, recvBuf, header.dataSize);
    SetSize(header.width, header.height, header.dataSize);
    return 0;
}

int CReceiveSocket::SetSize(int &w, int &h ,int &size)
{
    width = w;
    height = h;
    imageSize = size;
    return 0;
}