#include <iostream>
#include "ReceiveSocket.h"
#include "JPEGDecoder.h"
#include <opencv2/opencv.hpp>

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