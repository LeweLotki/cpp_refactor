#include "StereoCalibration.hpp"
#include <boost/filesystem.hpp>
#include <opencv2/highgui.hpp>

StereoCalibration::StereoCalibration() : chessboard_size(7, 7), size_of_chessboard_squares_mm(20), output_dir("Calibration_Files"), criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.001) {}

StereoCalibration::StereoCalibration(boost::filesystem::path output_dir) : chessboard_size(7, 7), size_of_chessboard_squares_mm(20), output_dir(output_dir), criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.001) {}

void StereoCalibration::find_chessboard_corners(const std::string& images_dir, const cv::Size& chessboardSize, const cv::TermCriteria& criteria) {
    std::vector<cv::Point3f> objp;
    for (int i = 0; i < chessboardSize.height; ++i) {
        for (int j = 0; j < chessboardSize.width; ++j) {
            objp.push_back(cv::Point3f(j * size_of_chessboard_squares_mm, i * size_of_chessboard_squares_mm, 0));
        }
    }

    boost::filesystem::path dir(images_dir);
    boost::filesystem::directory_iterator end_iter;

    for (boost::filesystem::directory_iterator dir_iter(dir); dir_iter != end_iter; ++dir_iter) {
        if (boost::filesystem::is_regular_file(dir_iter->status())) {
            cv::Mat img = cv::imread(dir_iter->path().string());
            cv::Mat gray;
            cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

            std::vector<cv::Point2f> corners;
            bool found = cv::findChessboardCorners(gray, chessboardSize, corners);

            if (found) {
                cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
                img_points_L.push_back(corners); // Przykład dla obrazów z lewej kamery
                obj_points.push_back(objp);
            }
        }
    }
}

// Placeholder implementations for the remaining methods
void StereoCalibration::calibrate(std::string mode) {}
void StereoCalibration::calibrate_camera() {}
void StereoCalibration::stereo_calibrate() {}
void StereoCalibration::save_calibration_files() {}
