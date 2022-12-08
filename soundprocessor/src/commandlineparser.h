#pragma once
#include <vector>
#include <string>

struct comdata {
    char mode;
    std::string config_path;
    std::string output_path;
    std::vector<std::string> input_path;
};

void parse_command_line(int argc, char** argv, comdata& data);
void check_correct_wav(const std::vector<std::string>& files);
