#include "stream.hpp"
#include <iostream>
#include <ostream>

Stream::Stream()
{
    device_id = 0;
    api_id = cv::CAP_ANY;
    frame_count = 0;
}

void Stream::run(std::string mode, std::string output_dir, int frame_limit)
{
    this->frame_limit = frame_limit;
    if (mode == "display_mode")
    {
        this->display_mode();
    }
}

void Stream::display_mode()
{
    bool frame_saved = false;
    bool save_mode = false;
    bool ret;
    cv::Mat frame;
    int frame_count = 0;

    this->open_camera();

    while(frame_limit == -1 || frame_limit > frame_count)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }

        imshow("stream", frame);

        if ((char)cv::waitKey(29) == (char)27) { break; } //esc
        if ((char)cv::waitKey(31) == (char)115 || save_mode) //s
        {
            if (!frame_saved)
            {
                this->create_output_dir(output_dir);
                frame_saved = true;
                save_mode = true;
            }
            this->save_images(frame);
        }
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

void Stream::set_resolution(int* resolution[])
{
    this->resolution[0] = *resolution[0];
    this->resolution[1] = *resolution[1];
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, this->resolution[0]);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, this->resolution[1]);
}

void Stream::create_output_dir(std::string path)
{

}

void Stream::save_images(cv::Mat frame)
{
    std::cout << "save image" << std::endl;
}

