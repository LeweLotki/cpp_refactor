#include "central_parser.hpp"
#include "../stream/stream_parser.hpp"
#include <iostream>

namespace po = boost::program_options;

po::variables_map CentralParser::parseCommandLine(int argc, char* argv[]) {
    po::options_description global("Global Options");
    global.add_options()
        ("help,h", "produce help message")
        ("module,m", po::value<std::string>()->required(), "module to run");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, global), vm);

    if (vm.count("help")) {
        std::cout << global << "\n";
        exit(0);
    }

    po::notify(vm); // Throws if 'module' is not provided

    // Merge module-specific options based on the selected module
    if (vm["module"].as<std::string>() == "stream") {
        auto streamOptions = StreamParser::getOptions();
        global.add(streamOptions);
        po::store(po::parse_command_line(argc, argv, global), vm);
        po::notify(vm); // Update vm with the new options, required for later access
    }

    return vm;
}

