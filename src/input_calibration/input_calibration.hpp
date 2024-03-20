#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

class StereoCalibration {

    cv::Size chessboard_size;
    int size_of_chessboard_squares_mm;
    boost::filesystem::path output_dir;
    cv::TermCriteria criteria;

    std::vector<std::vector<cv::Point3f>> obj_points;
    std::vector<std::vector<cv::Point2f>> img_points_L;
    std::vector<std::vector<cv::Point2f>> img_points_R;

public:
    StereoCalibration();
    StereoCalibration(boost::filesystem::path output_dir);
    void calibrate(std::string mode="default");
    void find_chessboard_corners(const std::string& images_dir, const cv::Size& chessboardSize, const cv::TermCriteria& criteria);

private:
    void calibrate_camera(); // Placeholder
    void stereo_calibrate(); // Placeholder
    void save_calibration_files(); // Placeholder
};
