#include "stream.hpp"
#include <boost/filesystem/operations.hpp>
#include <iostream>

#ifndef ESC_KEY
#define ESC_KEY 27
#endif
#ifndef s_KEY
#define s_KEY 115
#endif

namespace filesystem  = boost::filesystem;

Stream::Stream()
{
    device_id = 0;
    api_id = cv::CAP_ANY;
    frame_count = 0;
}

void Stream::run(std::string mode, boost::filesystem::path output_dir, int frame_limit)
{
    this->output_dir = output_dir;
    this->frame_limit = frame_limit;
    if (mode == "display_mode")
    {
        this -> display_mode();
    }
}

void Stream::display_mode()
{
    bool frame_saved = false;
    bool save_mode = false;
    bool ret;
    cv::Mat frame;

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

        if ((char)cv::waitKey(29) == (char)ESC_KEY) { break; } 
        if ((char)cv::waitKey(31) == (char)s_KEY || save_mode) 
        {
            if (!frame_saved)
            {
                this -> create_output_dir();
                this->resolution[0] = frame.cols;
                this->resolution[1] = frame.rows;
                frame_saved = true;
                save_mode = true;
            }
            this -> save_images(frame);
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

void Stream::create_output_dir()
{
    if (filesystem::exists(this->output_dir))
    {
        filesystem::remove_all(this->output_dir);
    }
    filesystem::create_directory(this->output_dir);
    this->left_dir = this->output_dir / "L";
    this->right_dir = this->output_dir / "R";
    filesystem::create_directory(this->left_dir);
    filesystem::create_directory(this->right_dir);
}

void Stream::save_images(cv::Mat frame)
{
    std::string filename_left = (this->left_dir / (std::to_string(this->frame_count) + ".png")).string();
    std::string filename_right = (this->right_dir / (std::to_string(this->frame_count) + ".png")).string();

    std::vector<cv::Mat> frames = this -> subdivide_camera_image(frame);

    cv::imwrite(filename_left, frames[0]);
    cv::imwrite(filename_right, frames[1]);
}

std::vector<cv::Mat> Stream::subdivide_camera_image(cv::Mat frame)
{
    cv::Mat frame_left = frame(
        cv::Range(0, resolution[1]), 
        cv::Range(0, (int)(resolution[0] / 2))
    );
    cv::Mat frame_right = frame(
        cv::Range(0, resolution[1]), 
        cv::Range((int)(resolution[0] / 2), resolution[0])
    );
    
    std::vector<cv::Mat> frames { frame_left, frame_right };    

    return frames;
}

