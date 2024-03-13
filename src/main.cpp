#include "main.hpp"

enum class Module {
    Unknown,
    Stream,
    // Other modules can be added here
};

Module getModuleFromString(const std::string& module) {
    if (module == "stream") return Module::Stream;
    // Additional modules can be handled here
    return Module::Unknown;
}

int main(int argc, char* argv[]) {
    auto vm = CentralParser::parseCommandLine(argc, argv);
    Module selectedModule = getModuleFromString(vm["module"].as<std::string>());

    switch (selectedModule) {
        case Module::Stream: {
            Stream stream;
            // Retrieve specific command line options
            std::string mode = vm["mode"].as<std::string>();
            int frame_limit = vm["frame_limit"].as<int>();
            stream.run(mode, "../stream_output",frame_limit);
            break;
        }
        default:
            std::cout << "No valid module selected or implemented." << std::endl;
            break;
    }

    return 0;
}

