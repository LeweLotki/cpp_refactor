#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>

class Stream
{
    static unsigned int _frame_count;
    std::string output_dir;
    std::string left_dir;
    std::string right_dir;

    public:
        
        Stream();
        void run(std::string mode, std::string output_dir, int
        frame_limit=(int)1e3);

    private:

        void save_display_mode(int frame_limit=(int)1e3);
        void display_mode();
        void save_mode(int frame_limit=(int)1e3);
        void void_mode(int frame_limit=(int)1e3);

        void create_output_dir(std::string path);
        cv::Mat subdivide_camera_image(cv::Mat frame);
        void display_images(cv::Mat frame);
        void save_images(cv::Mat frame);
};

