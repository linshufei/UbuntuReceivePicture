/****************************************************************************
filename:           SendSocket.h
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
#define DATA_ADDR 5;
#define SERVER_TYPE 0;

//文件头结构体
typedef struct SImageHeader
{
    int width;          //图片的宽度
    int height;         //图片的高度
    int serverType;     //请求的服务类型
    int dataOffset;     //图片数据头的位置
    int dataSize;       //图片大小
} SImageHeader;

class CSendSocket
{
public:
    //WSADATA wsaData;
    ssize_t sockClient;          //客户端Socket
    ssize_t sockServer;          //服务器Socket
    struct sockaddr_in addrClient;     //客户端地址
    struct sockaddr_in addrServer;     //服务端地址

    int width;
    int height;

    CSendSocket();
    ~CSendSocket();
    int Connect2Server();  
    int Send2Server(char* pData, int size);
    int GetSize(int w, int h);
    int RecvRes();
};

