#include <iostream>
#include "opencv2/opencv.hpp"
#include "stream/stream.hpp"

int main()
{
    cv::Mat image = cv::imread("test.png");

    if (image.empty())
        std::cout << "Foto not found!" << std::endl;
    
    cv::imshow("test", image);
    cv::waitKey(0);
    std::cout << "Hello, World!" << std::endl;
    Stream stream;
    return 0;
}

