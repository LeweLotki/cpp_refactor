#include "main.hpp"

enum class Module {
    Unknown,
    Stream,
};

Module getModuleFromString(const std::string& module) {
    if (module == "stream") return Module::Stream;
    return Module::Unknown;
}

int main(int argc, char* argv[]) {
    auto vm = CentralParser::parseCommandLine(argc, argv);
    Module selectedModule = getModuleFromString(vm["module"].as<std::string>());

    switch (selectedModule) {
        case Module::Stream: {
            Stream stream;
            std::string mode = vm["mode"].as<std::string>();
            std::string output_dir = vm["output_dir"].as<std::string>();
            int frame_limit = vm["frame_limit"].as<int>();
            stream.run(mode, output_dir, frame_limit);
            break;
        }
        default:
            std::cout << "No valid module selected or implemented." << std::endl;
            break;
    }

    return 0;
}

