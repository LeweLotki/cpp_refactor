#include "main.hpp"

enum class Module {
    UNKNOWN,
    STREAM,
    CALIBRATION
};

Module getModuleFromString(const std::string& module) {
    if (module == "stream") return Module::STREAM;
    else if (module == "calibration") return Module::CALIBRATION; 
    return Module::UNKNOWN;
}

int main(int argc, char* argv[]) {
    auto vm = CentralParser::parseCommandLine(argc, argv);
    Module selectedModule = getModuleFromString(vm["module"].as<std::string>());

    switch (selectedModule) 
    {

        case Module::STREAM: 
        {
            Stream stream;
            std::string mode = vm["mode"].as<std::string>();
            std::string output_dir = vm["output_dir"].as<std::string>();
            int frame_limit = vm["frame_limit"].as<int>();
            stream.run(mode, output_dir, frame_limit);
            break;
        }

        case Module::CALIBRATION:
        {
            Stream stream;
            StereoCalibration calibration;

            stream.add_observer(&calibration);

            stream.run("void_mode");

            break;
        }
        
        case Module::UNKNOWN:
        {
            std::cout << "No valid module selected or implemented." << std::endl;
            break;
        }

        default:
        {
            std::cout << "No valid module selected or implemented." << std::endl;
            break;
        }
    }

    return 0;
}

