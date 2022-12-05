#include <iostream>
#include <string>
#include <vector>

#include "excpts.h"
#include "audiofile.h"
#include "converter.h"
#include "convasciiint.h"
#include "commandlineparser.h"
#include "configfileparser.h"


int main(int argc, char** argv) {
    comdata data;/*
    try {
        parse_command_line(argc, argv, data);
        check_correct_wav(data.wav_file_path);
    }
    catch (not_enough_arguments nof) {
        std::cout << "0";
        std::cerr << nof.what();
        exit(nof.get_error_code());
    }
    catch (unknown_command uc) {
        std::cout << "1";
        std::cerr << uc.what();
        exit(uc.get_error_code());
    }
    catch (command_line_parser_error clpe) {
        std::cout << "2";
        std::cerr << clpe.what();
        exit(clpe.get_error_code());
    }
    catch (input_wav_format_exception iwfe) {
        std::cout << "3";
        std::cerr << iwfe.what();
        exit(iwfe.get_error_code());
    }
    catch (file_havent_opened fho) {
        std::cout << "4";
        std::cerr << fho.what();
        exit(fho.get_error_code());
    }
    catch (...) {
        std::cout << "ERROR\n";
    }
    std::cout << "fine";
    */
    data.mode = 'c';
    data.config_path = "config.txt";
    data.output_path = "output.txt";
    data.wav_file_path.push_back("district_four.wav");

    try {
        configparser configparser(data.config_path);
        soundproc proc;
        proc.use(configparser.next_command(data));
    }
    catch (file_havent_opened fho) {
        std::cout << "4";
        std::cerr << fho.what();
        exit(fho.get_error_code());
    }
    catch (...) {
        std::cerr << "ERROR";
    }
    

    /*
    command_info test;
    test.name = "mute";
    test.int_param.push_back(5);
    test.int_param.push_back(6);
    test.input.push_back("district_four.wav");
    test.output = "output.wav";

    proc.use(test);
    std::string test = "nan";
    int a = atoi(test.c_str());
    std::cout << a;
    */
    return 0;
}
