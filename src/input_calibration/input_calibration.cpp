#include "input_calibration.hpp"
#include <boost/filesystem.hpp>
#include <opencv2/highgui.hpp>
namespace filesystem = boost::filesystem;

StereoCalibration::StereoCalibration() : mode("default"), chessboard_size(7, 7), size_of_chessboard_squares_mm(20), output_dir("Calibration_Files"), criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.001) {}

StereoCalibration::StereoCalibration(std::string mode, filesystem::path output_dir) : chessboard_size(7, 7), size_of_chessboard_squares_mm(20), criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.001)
{
     this->output_dir = output_dir;
     this->mode = mode;
}


void StereoCalibration::calibrate(cv::Mat frame) 
{
    std::cout << "New frame just dropped" << std::endl;
    // imshow("calibration", frame);
    // cv::waitKey(5000); 
    this -> find_chessboard_corners(frame);
}

void StereoCalibration::update(const cv::Mat& frame) 
{
    this -> calibrate(frame);
}

void StereoCalibration::find_chessboard_corners(cv::Mat frame) {
    
    std::vector<cv::Point3f> objp;
    for (int i = 0; i < chessboard_size.height; ++i) {
        for (int j = 0; j < chessboard_size.width; ++j) {
            objp.push_back(cv::Point3f(j * size_of_chessboard_squares_mm, i * size_of_chessboard_squares_mm, 0));
            
        }
    }

    

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(gray, chessboard_size, corners);

        if (found) {
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            img_points_L.push_back(corners); // Przykład dla obrazów z lewej kamery
            obj_points.push_back(objp);
            
        }
        std::cout << found << std::endl;
}


