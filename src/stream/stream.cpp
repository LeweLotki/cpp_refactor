#include "stream.hpp"
#include <iostream>

Stream::Stream()
{
    device_id = 0;
    api_id = cv::CAP_ANY;
    frame_count = 0;

}

void Stream::run(std::string mode, std::string output_dir, int frame_limit)
{
    if (mode == "display_mode")
    {
        this->display_mode();
    }
}

void Stream::display_mode()
{
    bool frame_saved = false;
    bool ret;
    cv::Mat frame;

    this->open_camera();

    while(true)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }
        imshow("stream", frame);
        if (cv::waitKey(5) >= 0) { break; }
        frame_count += 1;
    }
}

void Stream::open_camera()
{
    cap = cv::VideoCapture(device_id + api_id);
    
    if (!cap.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
    }
}
