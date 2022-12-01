#include "converter.h"
#include "audiofile.h"
#include <vector>

nothing::~nothing() {};

void soundproc::use(inaudiofile& inf, outaudiofile& outf) {
	std::vector<int> temp;
	while (!inf.eof()) {
		inf >> temp;
		outf << temp;
	}
}

/*
void nothing::launch(audiofile& f1, audiofile& f2) {
	vector<unsigned long> temp = f1.read();
	f2.write(temp);
}*/
