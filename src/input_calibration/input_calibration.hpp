#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

#include "../observer/observer.hpp"

class StereoCalibration : public Observer<cv::Mat>
{

    int chessboard_size[2] = { 7, 7 };
    int frame_size[2] = { 672, 376 };
    int size_of_chessboard_squares_mm = 20;
    std::string mode;
    // boost::filesystem::path
    // potem dorób dla L i R z join
    
    boost::filesystem::path output_dir;

    std::vector<std::vector<float>> objp;
    std::vector<std::vector<float>> obj_points_L;
    std::vector<std::vector<float>> obj_points_R;
    std::vector<std::vector<float>> img_points_L;
    std::vector<std::vector<float>> img_points_R;

    
    float criteria[3] = {
        (float)cv::TermCriteria::EPS + (float)cv::TermCriteria::MAX_ITER,
        30, 
        0.001
    };

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

};
