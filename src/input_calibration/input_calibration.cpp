#include "input_calibration.hpp"
#include<glob.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace filesystem  = boost::filesystem;
using namespace cv;

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



// jak mieć dostęp do zdeklarowanych w konstruktorze zmiennych? i jak do kryteriów
// nw o co chodzi arturowi z tym kom z klasami

void find_chessboard_corners() {

    std::vector<std::string> images; // tworze wektor o nazwie images
    for (const auto& entry : filesystem::directory_iterator(images_dir)) { // iteracja po plikach z katalogu images_dir
        if (entry.path().extension() == ".png") { // jeżeli warunek jest spełniony
            images.push_back(entry.path().string()); // dodawany jest do wektora images
        }
    }
    std::sort(images.begin(), images.end()); // sortowanie alfabetyczne
    
    std::vector<Point3f> objp; // tworzenie wektora 3D obrazującego szachownice
    for (int i = 0; i < chessboard_size.height; ++i) {
        for (int j = 0; j < chessboard_size.width; ++j) {
            objp.push_back(Point3f(j * 20, i * 20, 0)); // 20 bo size_of_chessboard_squares_mm = 20;
        }
    }

    for (const auto& img_path : images) { // iteruje przez wszystkie ścieżki po wektorze images
        Mat img = imread(img_path); // tworzy macierz wczytującą każdą ścieżkę zdjęcia
        Mat gray; // macierz na szare zdj
        cvtColor(img, gray, COLOR_BGR2GRAY); // przetworzenie zdj na szare

        std::vector<Point2f> corners; // tworzenie wektora 2D na rogi
        bool ret = findChessboardCorners(gray, chessboard_size, corners); // sprawdzenie warunku czy róg został znaleziony

        if (ret) {
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), criteria); // po znalezieniu rogów chcemy znać dokładniejszą pozycję rogów
            std::vector<Point2f>imgpoints_temp.push_back(corners); 
            std::vector<Point3f> objpoints_temp.push_back(objp); // w tych linijkach cos ewidentnie zepsulam
        }
    }
}