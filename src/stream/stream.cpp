#include "stream.hpp"
#include <iostream>

Stream::Stream()
{
    int device_id = 0;
    int api_id = cv::CAP_ANY;
    cap = cv::VideoCapture(device_id + api_id);
    // cap.open(device_id + api_id);
    if (!cap.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
    }
}

void Stream::run(
    std::string mode="display_mode",
    std::string output_dir="../stream_output",
    int frame_limit=(int)1e3
    )
{
    if (mode == "display_mode")
    {
        this->display_mode();
    }
}

void Stream::display_mode()
{
    bool fram_saved = false;
    bool ret;
    cv::Mat frame;

    while(true)
    {
        cap.read(frame);
        // Stream::_frame_count += 1; 
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }
        imshow("stream", frame);
        if (cv::waitKey(5) >= 0) { break; }
    }
}
