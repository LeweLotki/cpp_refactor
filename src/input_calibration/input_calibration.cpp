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
            this -> frame = frame;
            calibrate_camera();
        }
        std::cout << found << std::endl;
}


std::vector<cv::Mat> StereoCalibration::subdivide_camera_image()
{
    cv::Mat frame_left = frame(
        
        cv::Range(0, frame.size().width), 
        cv::Range(0, (int)(frame.size().height / 2))
    );
    cv::Mat frame_right = frame(
        cv::Range(0, frame.size().width), 
        cv::Range((int)(frame.size().height / 2), frame.size().height)
    );
    
    std::vector<cv::Mat> frames { frame_left, frame_right };    

    return frames;
}

void StereoCalibration::calibrate_camera(){
    bool retL, retR;
    cv::Mat cameraMatrixL = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat cameraMatrixR = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffsL;
    cv::Mat distCoeffsR;
    std::vector<cv::Mat> rvecs, tvecs;

    std::vector<cv::Mat> frames = subdivide_camera_image();

    cv::Mat frame_L = frames[0];
    cv::Mat frame_R = frames[1];

    retL = cv::calibrateCamera(obj_points, img_points_L, frame.size() , cameraMatrixL, distCoeffsL, rvecs, tvecs);
    retR = cv::calibrateCamera(obj_points, img_points_R, frame.size() , cameraMatrixR, distCoeffsR, rvecs, tvecs);
    
    if(retL && retR) {
        // Tutaj możesz kontynuować z przetworzonymi danymi, np. zapisując je do pliku lub dalej je przekazując.
        // Poniżej znajduje się przykład, jak można by zwrócić te dane, gdyby ta funkcja była częścią większej klasy.
        stereo_calibrate(cameraMatrixL, distCoeffsL, cameraMatrixR, distCoeffsR);
        
    } else {
        std::cout << "blad" << std::endl;
        // Obsługa błędu, np. poprzez zwrócenie pustych macierzy lub zgłoszenie wyjątku
        // return std::make_pair(cv::Mat(), cv::Mat());
    }
}

void StereoCalibration::stereo_calibrate(cv::Mat& cameraMatrixL, cv::Mat& distCoeffsL,cv::Mat& cameraMatrixR, cv::Mat& distCoeffsR)
{
  
    int flags = cv::CALIB_FIX_INTRINSIC;

    cv::Mat R, T, E, F; // Macierze wynikowe

    bool ret = cv::stereoCalibrate(
        obj_points, img_points_L, img_points_R,
        cameraMatrixL, distCoeffsL,
        cameraMatrixR, distCoeffsR,
        frame.size(), R, T, E, F,
        criteria, flags
    );
    // bool ret = true;
    if(ret) {
        // Możesz teraz korzystać z R, T, E, F
        // Na przykład, zwróć te wartości lub zapisz je gdzieś
    } else {
        // Obsługa błędu kalibracji
    }
}