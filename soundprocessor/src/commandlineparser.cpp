#include "commandlineparser.h"
#include "excpts.h"
#include "audiofile.h"

void parse_command_line(int argc, char** argv, comdata& data) {
    if (argc <= 1)
        throw not_enough_arguments(0);

    if (!std::string(argv[1]).compare("-c")) {
        data.mode = 'c';
        if (argc >= 4) {
            data.config_path = argv[2];
            for (int i = 3; i < argc; i++)
                data.wav_file_path.push_back(std::string(argv[i]));
        }
        else {
            throw not_enough_arguments(2, 'c');
        }
    }
    else if (!std::string(argv[1]).compare("-h")) {
        data.mode = 'h';
    }
    else {
        throw unknown_command(argv[1][1]);
    }
}

inline void check_correct_wav(const std::vector<std::string>& files) {
    for (int i = 0; i < files.size(); i++)
        inaudiofile testing(files[i].c_str());
}
