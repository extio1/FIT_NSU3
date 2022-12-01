#include <iostream>
#include <string>
#include <vector>
#include "audiofile.h"
#include "converter.h"
#include "convasciiint.h"

struct configs {
    std::string configpath;
    std::vector<std::string> infilepaths;
    std::string outfilepath;
};

struct parsedata {
    char option;
    struct configs;
};


int foo() {
    std::vector<int> arr(3);
    int z = -999;
    //z = arr[3];
    try {
        int z = 0;
        std::exception a;
        throw a;
    }
    catch (...) {
        std::cerr << "ERROR\n";
    }
    

    return z;
}

int main()
{
    //std::fstream a;
    //a.open("district_four.wav");

   // audiofile wav;
   // wav.read_header("district_four.wav");
    
    inaudiofile inwav("district_four.wav");
    outaudiofile outwav("output.wav");

    soundproc proc;
    proc.use(inwav, outwav);

    /*
    int a = -123;
    a = foo();

    std::cout << a;

    
    int_to_ascii_seq_le(arr, 81298312, 4);
    printf("%d\n", ascii_seq_to_int_le(arr, 4));

    for (int i = 0; i < 4; i++) {
        printf("%d ", (arr[i] < 0) ? arr[i] + 256 : arr[i]);
    }
    */
    //audiofile outwav("output.wav");

    //soundproc proc;
   // proc.use("effectname", inwav, outwav);

}
