#include "stream.hpp"

Stream::Stream()
{
    std::cout << "another file" << std::endl;
    cv::Mat image = cv::imread("test2.png");
    cv::imshow("test2",image);
    cv::waitKey(0);
}
