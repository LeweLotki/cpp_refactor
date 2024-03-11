#include "DepthPostProcessor.hpp"
#include <opencv2/imgcodecs.hpp>

DepthPostProcessor::DepthPostProcessor(const std::string& calib_dir, const std::string& left_images_dir, const std::string& right_images_dir) {
    // Tutaj możemy dodać implementację konstruktora, jeśli jest potrzebna
}

std::vector<cv::Mat> DepthPostProcessor::generate_occupancy_grid() {
    std::vector<cv::Mat> occupancy_grids;

    // Pętla dla przetwarzania danych głębokości
    for (int i = 0; i < number_of_depth_maps_to_process; ++i) {
        // Wczytanie mapy głębokości
        cv::Mat depth_map_left = cv::imread(left_images_dir + "/depth_map_" + std::to_string(i) + ".png", cv::IMREAD_GRAYSCALE);
        cv::Mat depth_map_right = cv::imread(right_images_dir + "/depth_map_" + std::to_string(i) + ".png", cv::IMREAD_GRAYSCALE);

        // Zaimplementuj logikę przetwarzania mapy głębokości, aby uzyskać mapę zajętości
        // Tutaj można użyć różnych metod przetwarzania, w zależności od potrzeb
        
        // Przykładowo, zakładając, że depth_map_single_binary jest mapą zajętości, a nie mapą głębokości
        cv::Mat occupancy_map = depth_map_single_binary.clone();

        // Odwrócenie mapy, ponieważ funkcja route_through_array traktuje wartości niezerowe jako przeszkody
        cv::bitwise_not(occupancy_map, occupancy_map);

        // Dodanie obliczonej mapy zajętości do wektora
        occupancy_grids.push_back(occupancy_map);
    }

    return occupancy_grids;
}
