#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include <string>
#include <boost/filesystem>
#include <vector>
class StereoCalibration {

    int chessboard_size[2] = { 7, 7 };
    int frame_size[2] = { 672, 376 };
    int size_of_chessboard_squares_mm = 20;

    // boost::filesystem::path
    // potem dorób dla L i R z join
    boost::filesystem::path calibration_images_dir;
    boost::filesystem::path output_dir;

    std::vector<std::vector<float>> objp;
    std::vector<std::vector<float>> obj_points;
    std::vector<std::vector<float>> img_points_L;
    std::vector<std::vector<float>> img_points_R;

    float criteria[3] = {
        (float)cv::TERM_CRITERIA_EPS + (float)cv::TERM_CRITERIA_MAX_ITER,
        30, 
        0.001
    };

    // line 26

};
