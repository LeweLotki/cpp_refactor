#pragma once
#include <boost/program_options.hpp>
#include <map>
#include <string>

class CentralParser {
public:
    static boost::program_options::variables_map parseCommandLine(int argc, char* argv[]);
};

