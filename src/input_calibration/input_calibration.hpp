#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

#include "../observer/observer.hpp"

class StereoCalibration : public Observer<cv::Mat>
{

    cv::Size chessboard_size;
    int size_of_chessboard_squares_mm;

    boost::filesystem::path output_dir;
    cv::TermCriteria criteria;
    std::string mode;

    public:

        StereoCalibration();
        StereoCalibration(std::string mode, boost::filesystem::path output_dir);
        void calibrate(cv::Mat frame);
        void update(const cv::Mat& frame) override;

    private:

        void find_chessboard_corners(); // przyjmuje nazwe zdjecia, zdeklarowany w atrybutach chessboardsize i criteria
        void calibrate_camera(); // przyjmuje atrybuty a zwraca macierz i dist (int?)
        void stereocalibrate(); // przyjmuje zeklarowane atrybuty: obpoints, imgpoints L & R i imageSize, 2 macierze cameraMatrix Li R dist L & R zwraca 4 macierze
        void save_calibration_files(); // przyjmuje z atrybutow output_dir, cameraMarix L & R dist L & R i macierze R i T 
        void test_method();

        std::vector<std::vector<cv::Point3f>> obj_points;
        std::vector<std::vector<cv::Point2f>> img_points_L;
        std::vector<std::vector<cv::Point2f>> img_points_R;

    
        void find_chessboard_corners(cv::Mat frame);
// >>>>>>> julka

// private:
//     void calibrate_camera(); // Placeholder
//     void stereo_calibrate(); // Placeholder
//     void save_calibration_files(); // Placeholder
};
