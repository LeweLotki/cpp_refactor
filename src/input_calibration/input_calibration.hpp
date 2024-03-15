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
    
    boost::filesystem::path output_dir;

    std::vector<std::vector<float>> objp;
    std::vector<std::vector<float>> obj_points_L;
    std::vector<std::vector<float>> obj_points_R;
    std::vector<std::vector<float>> img_points_L;
    std::vector<std::vector<float>> img_points_R;

    
    float criteria[3] = {
        (float)cv::TERM_CRITERIA_EPS + (float)cv::TERM_CRITERIA_MAX_ITER,
        30, 
        0.001
    };

    public:

        StereoCalibration();
        StereoCalibration(std::string output_dir);
        StereoCalibration(std::string mode);

        void find_chessboard_corners(const std::string& images_dir, const cv::Size& chessboardSize, const cv::TermCriteria& criteria); // przyjmuje nazwe zdjecia, zdeklarowany w atrybutach chessboardsize i criteria
        void calibrate_camera(); // przyjmuje atrybuty a zwraca macierz i dist (int?)
        void stereocalibrate(); // przyjmuje zeklarowane atrybuty: obpoints, imgpoints L & R i imageSize, 2 macierze cameraMatrix Li R dist L & R zwraca 4 macierze
        void save_calibration_files(); // przyjmuje z atrybutow output_dir, cameraMarix L & R dist L & R i macierze R i T 


};
