#include <iostream>
#include "opencv2/opencv.hpp"
#include "stream/stream.hpp"

#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0); // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap.read(frame); // Capture a new frame
        if (frame.empty()) {
            std::cerr << "ERROR! Blank frame grabbed\n";
            break;
        }
        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }
    return 0;
}

/*
int main()
{
    cv::Mat image = cv::imread("test.png");

    if (image.empty())
        std::cout << "Foto not found!" << std::endl;
    
    cv::imshow("test", image);
    cv::waitKey(0);
    std::cout << "Hello, World!" << std::endl;

    std::cout << cv::getBuildInformation() << std::endl;

    Stream stream;
    return 0;
}
*/

