#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#if 0
#include "JPEGDecoder.h"
#include "JPEGEncoder.h"
#include "ReceiveSocket.h"
int main() {
    CJPEGDecoder decoder;
    CReceiveSocket s;
    s.Listen();
    s.AcceptFromClient();
    char* pData;   //分配接收客户端返回内容的内存
    pData = new char[MAX_IMAGE_SIZE];
    s.ReceiveFromClient(pData, MAX_IMAGE_SIZE);
    s.SendRes();

    if (!decoder.Decode((uint8_t*)s.pData , s.imageSize))
    {
        std::cout << "decoder successful!" << std::endl;
    }

    int width;
    int height;
    decoder.GetSize(width, height);
    std::cout << width << " && " << height << std::endl;
    cv::Mat image(cv::Size(s.width, s.height * 3 / 2), CV_8UC1, cv::Scalar(255));
    decoder.GetData(image.data);
    cv::cvtColor(image, image, CV_YUV2BGR_I420);
//    cv::cvtColor(image, image, CV_BGR2GRAY);
//    cv::Mat edge;
//    cv::blur(image, edge, cv::Size(3,3));
//    cv::Canny(edge, edge, 50, 150, 3);
//
//    cv::Mat edge3Channels(image.rows, image.cols, CV_8UC3);
//    for(int i = 0; i < edge.rows; i++)
//    {
//        for(int j = 0; j < edge.cols; j++)
//        {
//            edge3Channels.ptr<uchar>(i)[3 * j] = edge.ptr<uchar>(i)[j];
//            edge3Channels.ptr<uchar>(i)[3 * j + 1] = edge.ptr<uchar>(i)[j];
//            edge3Channels.ptr<uchar>(i)[3 * j + 2] = edge.ptr<uchar>(i)[j];
//        }
//    }
//    cv::cvtColor(edge3Channels, edge3Channels, CV_BGR2YUV_I420);
//    CJPEGEncoder encoder(edge3Channels.cols, edge3Channels.rows * 2 / 3);
//    encoder.Encode(edge3Channels.data);
//    std::cout << encoder.packet.size << std::endl;
//    s.SendImage((char*)encoder.packet.data, encoder.packet.size, edge3Channels.cols, edge3Channels.rows);

    cv::imshow("receive image", image);
//    cv::imshow("send image", edge3Channels);
    cv::waitKey(0);

    delete []pData;

    return 0;
}
#else
#include "ReceiveRTP.h"
#include "H264Decoder.h"
int main()
{
    CH264Decoder decoder;
    ReceiveRTP receive;

    //Receive a audio/video stream from client
    receive.Init();

    while (1)
    {
        if (receive.GetFirstSourceWithData())
        {
            do
            {
                int size = receive.GetH264Packet();
                //int size = receive.GetJPEGPacket();
                if (size)
                {
                    if (!decoder.Decode(receive.pBuff, size, NULL))
                    {
                        int width;
                        int height;
                        decoder.GetSize(width, height);
                        cv::Mat image(cv::Size(width, height), CV_8UC1);
                        decoder.GetData(image.data);

                        cv::imshow("receive image", image);
                        cv::waitKey(3);
                        //std::cout << "Lena is coming!" << std::endl;
                    }
                }
            } while (receive.GotoNextSourceWithData());
        }
        sleep(0.1);
    }

    receive.Destroy();

    return 0;
}
#endif