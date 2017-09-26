/****************************************************************************
filename:           SendSocket.cpp
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#include "SendSocket.h"
#include <string.h>

CSendSocket::CSendSocket()
{
    //WSAStartup(MAKEWORD(2, 2), &wsaData);

    //新建客户端socket
    sockClient = socket(AF_INET, SOCK_STREAM, 0);

    //定义要连接的服务端地址
    addrServer.sin_addr.s_addr = inet_addr("192.168.179.129");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(8001);
}

CSendSocket::~CSendSocket()
{
    close(sockClient);
    //WSACleanup();
}

//请求连接服务器  
int CSendSocket::Connect2Server()
{
    int ret = connect(sockClient, (struct sockaddr*)& addrServer, sizeof(addrServer));
    if (ret < 0)
    {
        std::cout << "connect failed!" << std::endl;
        return -1;
    }
    return 0;
}

//将数据发送到服务器端，输入为指向数据的指针pData和数据的大小size
int CSendSocket::Send2Server(char* pData ,int size)
{
    char* pictureBuf;
    pictureBuf = new char[MAX_IMAGE_SIZE];

    //写数据头
    SImageHeader imageHeader;
    imageHeader.width = width;
    imageHeader.height = height;
    imageHeader.dataSize = size;
    imageHeader.dataOffset = sizeof(imageHeader);
    
    memcpy(pictureBuf, &imageHeader, sizeof(imageHeader));
    memcpy(pictureBuf + sizeof(imageHeader), pData, size);

    //send picture
    send(sockClient, pictureBuf, size + sizeof(imageHeader), 0);    
    delete pictureBuf;

    return 0;
}

int CSendSocket::GetSize(int w, int h)
{
    width = w;
    height = h;
    return 0;
}

int CSendSocket::RecvRes()
{
    //receive the response from server
    //listen(sockClient, 1); //listen and wait for the server to link
    //std::cout << "Client start waitting for response" << std::endl;

    //int len = sizeof(SOCKADDR);
    //sockServer = accept(sockClient, (SOCKADDR*)& addrServer, &len);

    char Res[100];
    memset(&Res, 0, 100);
    int response = recv(sockClient, Res, 100, 0);
    std::cout << Res << std::endl;
    return 0;
}