#include "stream_parser.hpp"

namespace po = boost::program_options;

po::options_description StreamParser::getOptions() {
    po::options_description streamDesc("Stream Options");
    streamDesc.add_options()
        ("mode", po::value<std::string>()->default_value("display_mode"), "stream mode to run")
        ("frame_limit", po::value<int>()->default_value(50), "limit of frames to save during stream")
        ("output_dir", po::value<std::string>()->default_value("../stream_output"), "Directory at which frames will be stored");
    return streamDesc;
}

