#pragma once

#include <string>
#include <vector>
#include <opencv2/core.hpp>

class DepthPostProcessor {
public:
    DepthPostProcessor(const std::string& calib_dir, const std::string& left_images_dir, const std::string& right_images_dir);
    std::vector<cv::Mat> generate_occupancy_grid();
};
