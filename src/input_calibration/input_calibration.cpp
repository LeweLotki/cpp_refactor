#include "input_calibration.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

StereoCalibration::StereoCalibration(const std::string& calib_images_dir_left, const std::string& calib_images_dir_right, const cv::Size& chessboard_size, const cv::Size& frame_size, const double& size_of_chessboard_squares_mm)
    : chessboard_size_(chessboard_size), frame_size_(frame_size), size_of_chessboard_squares_mm_(size_of_chessboard_squares_mm) {}

void StereoCalibration::findChessboardCorners(cv::TermCriteria criteria) {
    // Przygotowanie obiektów punktów 3D
    std::vector<cv::Point3f> objp;
    for(int i = 0; i < chessboard_size_.height; ++i) {
        for(int j = 0; j < chessboard_size_.width; ++j) {
            objp.push_back(cv::Point3f(j * size_of_chessboard_squares_mm_, i * size_of_chessboard_squares_mm_, 0));
        }
    }

    // Przetwarzanie obrazów lewego i prawego
    std::vector<std::string> image_paths_left;
    std::vector<std::string> image_paths_right;

    // Wczytanie ścieżek obrazów
    for(const auto& entry : fs::directory_iterator(calib_images_dir_left)) {
        image_paths_left.push_back(entry.path().string());
    }
    for(const auto& entry : fs::directory_iterator(calib_images_dir_right)) {
        image_paths_right.push_back(entry.path().string());
    }

    // Dla każdego obrazu znajdź rogi szachownicy i dodaj punkty
    for(size_t i = 0; i < image_paths_left.size(); ++i) {
        cv::Mat img_left = cv::imread(image_paths_left[i]);
        cv::Mat img_right = cv::imread(image_paths_right[i]);
        
        std::vector<cv::Point2f> corners_left, corners_right;
        bool found_left = cv::findChessboardCorners(img_left, chessboard_size_, corners_left);
        bool found_right = cv::findChessboardCorners(img_right, chessboard_size_, corners_right);

        if(found_left && found_right) {
            cv::Mat gray_left, gray_right;
            cv::cvtColor(img_left, gray_left, cv::COLOR_BGR2GRAY);
            cv::cvtColor(img_right, gray_right, cv::COLOR_BGR2GRAY);

            cv::cornerSubPix(gray_left, corners_left, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            cv::cornerSubPix(gray_right, corners_right, cv::Size(11, 11), cv::Size(-1, -1), criteria);

            imgpointsL_.push_back(corners_left);
            imgpointsR_.push_back(corners_right);
            objpoints_.push_back(objp);
        }
    }
}

void StereoCalibration::calibrateCameras() {
    // Kalibracja lewej kamery
    cv::calibrateCamera(objpoints_, imgpointsL_, frame_size_, cameraMatrixL_, distL_, cv::noArray(), cv::noArray());

    // Kalibracja prawej kamery
    cv::calibrateCamera(objpoints_, imgpointsR_, frame_size_, cameraMatrixR_, distR_, cv::noArray(), cv::noArray());
}

void StereoCalibration::stereoCalibrate() {
    // Kalibracja stereo
    cv::stereoCalibrate(objpoints_, imgpointsL_, imgpointsR_, cameraMatrixL_, distL_, cameraMatrixR_, distR_, frame_size_, R_, T_);
}

void StereoCalibration::saveCalibrationFiles(const std::string& output_dir) {
    // Utwórz katalog wyjściowy, jeśli nie istnieje
    if (!fs::exists(output_dir))
        fs::create_directory(output_dir);

    // Zapisz parametry kalibracji do plików
    std::string output_file_prefix = output_dir + "/calibration_";
    std::string ext = ".txt";

    std::ofstream cameraMatrixL_file(output_file_prefix + "cameraMatrixL" + ext);
    if (cameraMatrixL_file.is_open()) {
        cameraMatrixL_file << cameraMatrixL_;
        cameraMatrixL_file.close();
    }

    std::ofstream distL_file(output_file_prefix + "distL" + ext);
    if (distL_file.is_open()) {
        distL_file << distL_;
        distL_file.close();
    }

    std::ofstream cameraMatrixR_file(output_file_prefix + "cameraMatrixR" + ext);
    if (cameraMatrixR_file.is_open()) {
        cameraMatrixR_file << cameraMatrixR_;
        cameraMatrixR_file.close();
    }

    std::ofstream distR_file(output_file_prefix + "distR" + ext);
    if (distR_file.is_open()) {
        distR_file << distR_;
        distR_file.close();
    }

    std::ofstream R_file(output_file_prefix + "R" + ext);
    if (R_file.is_open()) {
        R_file << R_;
        R_file.close();
    }

    std::ofstream T_file(output_file_prefix + "T" + ext);
    if (T_file.is_open()) {
        T_file << T_;
        T_file.close();
    }
}
