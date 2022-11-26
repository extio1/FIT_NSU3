#include <iostream>
#include <string>
#include <vector>
#include "wavinfo.h"

struct configs {
    std::string configpath;
    std::vector<std::string> infilepaths;
    std::string outfilepath;
};

struct parsedata {
    char option;
    struct configs;
};

int main()
{
    wavinfo wav_file;
    wav_file.read_header("district_four.wav");
}
