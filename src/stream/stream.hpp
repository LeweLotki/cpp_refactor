#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <mutex>
#include <thread>

#ifndef ESC_KEY
#define ESC_KEY 27
#endif
#ifndef s_KEY
#define s_KEY 115
#endif

class Stream
{
    unsigned int frame_count = 0;
    boost::filesystem::path output_dir;
    boost::filesystem::path left_dir;
    boost::filesystem::path right_dir;
    int device_id;
    int api_id;
    cv::VideoCapture cap;
    int resolution[2];
    int frame_limit;
    cv::Mat frame;
    mutable std::mutex frame_mutex;

    enum Modes
    {
        DISPLAY_MODE,
        SAVE_MODE,
        SAVE_DISPLAY_MODE,
        VOID_MODE,
        INVALID_MODE
    };

    public:
        
        Stream();
        void run(
            const std::string& mode="display_mode",
            boost::filesystem::path output_dir="../stream_output",
            int frame_limit=(int)1e3
        );
        void set_resolution(int* resolution[]);
        cv::Mat get_current_frame() const;

    private:

        void save_display_mode();
        void display_mode();
        void save_mode();
        void void_mode();

        void create_output_dir();
        std::vector<cv::Mat> subdivide_camera_image(cv::Mat frame);
        void display_images(cv::Mat frame);
        void save_images(cv::Mat frame);
        void open_camera();
        Modes resolve_mode(const std::string& mode);
};

