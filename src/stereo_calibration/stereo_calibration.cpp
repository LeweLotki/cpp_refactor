#include "stereo_calibration.hpp"

namespace filesystem  = boost::filesystem;

StereoCalibration::StereoCalibration()
{
    int chessboard_size[2] = { 7, 7 };
    int frame_size[2] = { 672, 376 };
    int size_of_chessboard_squares_mm = 20;
    output_dir = "../calibration_files";
}


StereoCalibration::StereoCalibration(filesystem::path output_dir) 
{
     int chessboard_size[2] = { 7, 7 };
     int frame_size[2] = { 672, 376 };
     int size_of_chessboard_squares_mm = 20;
     this->output_dir = output_dir;
}


void calibrate(std::string mode) 
{
    // tu cała logika z kodu ycalib.py 
}

void StereoCalibration::find_chessboard_corners()
{
/*    
    std::vector<cv::String> filenames;
    cv::glob(images_dir, filenames);
    std::vector<std::vector<cv::Point3f>> objpoints_temp; 
    std::vector<std::vector<cv::Point2f>> imgpoints_temp; 

    for (const auto& filename : filenames)
    {
        cv::Mat img = cv::imread(filename);
        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Point2f> corners;
        bool ret, corners = cv::findChessboardCorners(gray, chessboard_size, None);

        if (ret)
        {
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            imgpoints_temp.push_back(corners);
            objpoints_temp.push_back(objp);
        }
    }

    // Tutaj możesz zrobić coś z objpoints_temp i imgpoints_temp, np. przypisać je do odpowiednich pól klasy
*/
}
