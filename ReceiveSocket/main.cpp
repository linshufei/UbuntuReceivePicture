#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#if 0
#include "JPEGDecoder.h"
#include "ReceiveSocket.h"
int main() {
    CJPEGDecoder decoder;
    CReceiveSocket s;
    s.Listen();
    s.AcceptFromClient();
    char* pData;   //分配接收客户端返回内容的内存
    pData = new char[MAX_IMAGE_SIZE];
    s.ReceiveFromClient(pData, MAX_IMAGE_SIZE);

    if (!decoder.Decode((uint8_t*)s.pData , s.imageSize))
    {
        int width;
        int height;
        decoder.GetSize(width, height);
        std::cout << width << " && " << height << std::endl;
        cv::Mat image(cv::Size(s.width, s.height), CV_8UC1, cv::Scalar(255));
        decoder.GetData(image.data);
        cv::imshow("receive image", image);
    }

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

    while (true)
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

                        cv::imshow("image", image);
                        cv::waitKey(3);
                        std::cout << "Lena is coming!" << std::endl;
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