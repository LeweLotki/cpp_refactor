/* #include "depth_map_processing.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <skimage/graph/route_through_array.h>

DepthMapProcessor::DepthMapProcessor(const std::string& calib_dir, const std::string& left_images_dir, const std::string& right_images_dir)
    : calib_dir_(calib_dir), left_images_dir_(left_images_dir), right_images_dir_(right_images_dir) {}

void DepthMapProcessor::processDepthMaps() {
    for (cv::Mat occupancy_map : generateOccupancyGrid()) {
        cv::Mat occupancy_map_inv;
        cv::bitwise_not(occupancy_map, occupancy_map_inv);

        // Start point is the center column at the highest row, and end point is the same column at the lowest row
        int rows = occupancy_map_inv.rows;
        int cols = occupancy_map_inv.cols;
        cv::Point start(cols / 2, 0);  // Start at the top center
        cv::Point end(cols / 2, rows - 1);  // End at the bottom center

        // Compute the path using route_through_array from skimage.graph
        std::vector<cv::Point> path;
        float weight;
        skimage::graph::route_through_array(occupancy_map_inv, start, end, true, path, weight);

        // Plotting the path on the occupancy map
        cv::Mat occupancy_map_rgb;
        cv::cvtColor(occupancy_map_inv, occupancy_map_rgb, cv::COLOR_GRAY2BGR);
        for (size_t i = 0; i < path.size(); ++i) {
            cv::circle(occupancy_map_rgb, path[i], 1, cv::Scalar(0, 0, 255), -1); // path points
        }
        cv::circle(occupancy_map_rgb, start, 3, cv::Scalar(255, 0, 0), -1); // start point
        cv::circle(occupancy_map_rgb, end, 3, cv::Scalar(255, 0, 0), -1); // end point

        cv::imshow("Occupancy Map", occupancy_map_rgb);
        cv::waitKey(100); // Pauses for 100 milliseconds
    }
}

std::vector<cv::Mat> DepthMapProcessor::generateOccupancyGrid() {
    // This function should generate and return a vector of occupancy maps
    // based on the calibration directory and left/right images directories.
    // Replace this with your implementation.
    std::vector<cv::Mat> occupancy_grids;
    // Your implementation here...
    return occupancy_grids;
}
*/