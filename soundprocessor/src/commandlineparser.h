#pragma once
#include <vector>
#include <string>

struct comdata {
    char mode;
    std::string config_path;
    std::vector<std::string> wav_file_path;
};

void parse_command_line(int argc, char** argv, comdata& data);
inline void check_correct_wav(const std::vector<std::string>& files);
