#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include <string>

class StereoCalibration {
public:
    StereoCalibration(const std::string& calib_images_dir_left, const std::string& calib_images_dir_right, const cv::Size& chessboard_size, const cv::Size& frame_size, const double& size_of_chessboard_squares_mm);

    void findChessboardCorners(cv::TermCriteria criteria);
    void calibrateCameras();
    void stereoCalibrate();

    void saveCalibrationFiles(const std::string& output_dir);

private:
    cv::Size chessboard_size_;
    cv::Size frame_size_;
    double size_of_chessboard_squares_mm_;

    std::vector<cv::Point3f> objpoints_;
    std::vector<std::vector<cv::Point2f>> imgpointsL_;
    std::vector<std::vector<cv::Point2f>> imgpointsR_;

    cv::Mat cameraMatrixL_;
    cv::Mat distL_;
    cv::Mat cameraMatrixR_;
    cv::Mat distR_;
    cv::Mat R_;
    cv::Mat T_;
};
