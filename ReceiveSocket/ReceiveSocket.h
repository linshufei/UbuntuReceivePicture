/****************************************************************************
filename:           ReceiveSocket.h
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#pragma once
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX_IMAGE_SIZE 1920 * 1080

typedef struct SImageHeader
{
    int width;
    int height;
    int serverType;
    int dataOffset;
    int dataSize;
} SImageHeader;

class CReceiveSocket
{
public:
    CReceiveSocket();
    ~CReceiveSocket();
    //WSADATA wsaData;
    ssize_t sockServer;
    struct sockaddr_in addrServer;
    ssize_t sockClient;
    struct sockaddr_in addrClient;

    char* pData;
    int width;
    int height;
    int imageSize;

    int Listen();
    int AcceptFromClient();
    int ReceiveFromClient(char* recvBuf, int recvBufLen);
    int SetSize(int &w, int &h, int &size);
    int SendRes();
    int SendImage(char* pData, int size ,int cols, int rows);
};


