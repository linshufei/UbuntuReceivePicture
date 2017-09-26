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
    addrServer.sin_port = htons(8001); //�󶨶˿�6000
    //sockServer = socket(PF_INET, SOCK_STREAM, 0); //socket(int domain, int type, int protocol)

    int opt = 1;
    //将端口设置为可重用的端口
    setsockopt(sockServer, SOL_SOCKET, SO_REUSEPORT, &opt,sizeof(&opt));

    int ret = bind(sockServer, (struct sockaddr*)&addrServer, sizeof(addrServer));

    if(ret < 0)
    {
        std::cout << "Fail to bind ip or port, please use \"netstat -anpt\" check it!" << std::endl;
    }
}

CReceiveSocket::~CReceiveSocket()
{
    if (pData == nullptr)
    {
        delete[] pData;
        pData = nullptr;
    }
    close(sockClient);
    close(sockServer);
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
    puts("one");
    int len = recv(sockClient, &header, sizeof(SImageHeader), 0);
    puts("two");
    while (true)
    {
        len = recv(sockClient, &recvBuf[pos], 1024, 0);
        pos += len;
        std::cout << "pos:" << pos << "/"<< header.dataSize <<std::endl;
        if (pos >= header.dataSize)
        {
            //send(sockClient, "linglongqing", 20, 1);
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

int CReceiveSocket::SendRes()
{
    send(sockClient, "copy", 20, 1);
    std::cout << "Send response to client" << std::endl;
    return 0;
}

int CReceiveSocket::SendImage(char* pData, int size ,int cols, int rows)
{
    char* pictureBuf;
    pictureBuf = new char[MAX_IMAGE_SIZE];

    //写数据头
    SImageHeader imageHeader;
    imageHeader.width = cols;
    imageHeader.height = rows;
    imageHeader.dataSize = size;
    imageHeader.dataOffset = sizeof(imageHeader);

    memcpy(pictureBuf, &imageHeader, sizeof(imageHeader));
    memcpy(pictureBuf + sizeof(imageHeader), pData, size);

    //send picture
    send(sockClient, pictureBuf, size + sizeof(imageHeader), 0);
    delete pictureBuf;

    return 0;
}