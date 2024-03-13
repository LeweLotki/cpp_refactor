#include "central_parser.hpp"
#include "../stream/stream_parser.hpp"
#include <iostream>

namespace po = boost::program_options;

po::variables_map CentralParser::parseCommandLine(int argc, char* argv[]) {
    
    po::options_description globalOptions("Global Options");
    globalOptions.add_options()
        ("help,h", "produce help message")
        ("module,m", po::value<std::string>(), "module to run");

    po::variables_map vm;
    
    po::options_description cmdline_options = globalOptions;
    cmdline_options.add(StreamParser::getOptions());
    
    po::store(po::command_line_parser(argc, argv).options(cmdline_options).run(), vm);

    if (vm.count("help")) {
        std::cout << globalOptions << std::endl;
        exit(0);
    }

    if (!vm.count("module")) {
        std::cerr << "Error: '--module' option is required." << std::endl;
        exit(1);
    }

    po::notify(vm);

    return vm;
}

