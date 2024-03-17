/*#ifndef DEPTH_MAP_PROCESSOR_HPP
#define DEPTH_MAP_PROCESSOR_HPP

#include <string>
#include <vector>
#include <opencv2/core.hpp>

class DepthMapProcessor {
public:
    DepthMapProcessor(const std::string& calib_dir, const std::string& left_images_dir, const std::string& right_images_dir);

    void processDepthMaps();

private:
    std::string calib_dir_;
    std::string left_images_dir_;
    std::string right_images_dir_;

    std::vector<cv::Mat> generateOccupancyGrid();
};

#endif // DEPTH_MAP_PROCESSOR_HPP

*/