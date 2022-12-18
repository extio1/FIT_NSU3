#include <iostream>
#include <string>
#include <vector>

#include "excpts.h"
#include "audiofile.h"
#include "converter.h"
#include "convasciiint.h"
#include "commandlineparser.h"
#include "configfileparser.h"
#include "soundproc.h"


int main(int argc, char** argv) {
    comdata data;
    try {
        parse_command_line(argc, argv, data);
        check_correct_wav(data.input_path);
    }
    catch (wrong_num_arguments nof) { //ошибки парсера
        std::cerr << nof.how_many() << " arguments is not enoung to launch -" << nof.what_for() << '\n';
        std::cerr << "at least:\n0 for -h\n3 for -c";
        exit(nof.get_error_code());
    }
    catch (unknown_command uc) {
        std::cerr << uc.what();
        std::cerr << uc.what_mode() << " is not known.\n";
        exit(uc.get_error_code());
    }
    catch (command_line_parser_error clpe) {
        std::cerr << clpe.what();
        exit(clpe.get_error_code());
    }
    catch (file_havent_opened fho) { //ошибки сообщающие о неправильных форматах файлов
        std::cerr << "File <" << fho.what_file() << "> haven't opened.";
        exit(fho.get_error_code());
    }
    catch (wrong_header wh) {
        std::cerr << "File <" << wh.what_file() << "> have error in <" << wh.what_section() << "> section.\n";
        exit(wh.get_error_code());
    }
    catch (wav_file_error iwfe) {
        std::cerr << "Some error occurred in <" << iwfe.what_file() << "> file";
        exit(iwfe.get_error_code());
    }
    catch (...) {
        std::cerr << "Unexpected error.";
    }

    soundproc proc;
    if (data.mode == 'h') {
        proc.help();
        return 0;
    }
 
    if (data.mode == 'c') {
        configparser cnfgparser;
        try {
            cnfgparser.open(data.config_path);
        }
        catch (file_havent_opened fho) {
            std::cerr << "Error while opening config file <" << fho.what_file() << ">.\n";
            exit(fho.get_error_code());
        }

        while (!cnfgparser.end_of_config()) {
            proc.use(cnfgparser.next_command(data));
        }

        std::cout << "\n-----------==========Done!==========-----------\n";
    }

    return 0;
    
}
