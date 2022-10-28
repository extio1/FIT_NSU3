#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

using namespace std;

class fileInfo {
public:
	fileInfo(string path) : nWords(0) { file.open(path); }
	void analyse();
	map<const string, int>* getMap() { return &info; }
	unsigned int getNumWords() { return nWords; }
	~fileInfo() { file.close(); }
private:
	map <const string, int> info;
	ifstream file;
	unsigned int nWords;

	void addPair(string);
	void addStringTokenToMap(string&);
};

class csvout {
public:
	csvout(string path) { file.open(path); }
	void write(fileInfo&);
	~csvout() { file.close(); }
private:
	ofstream file;
};

struct comparingPair {
	unsigned int freq;
	string* word;
};

int main(int argc, char** argv) {
	setlocale(LC_ALL, "rus");

	fileInfo someFile("test.txt");
	someFile.analyse();

	csvout stream("out.csv");
	stream.write(someFile);
}


void fileInfo::addStringTokenToMap(string& str) {
	string word;
	for (int i = 0; i <= str.size(); i++)
		if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || \
			str[i] >= '0' && str[i] <= '9' || str[i] >= 'а' && str[i] <= 'я') {
			word.append(1, str[i]);
		}
		else {
			if (word.length() >= 1) {
				nWords++;
				addPair(word);
			}
			word.clear();
		}
	if ((str[str.length()] == '\0') && (word.length() > 1)) {
		nWords++;
		addPair(word);
		word.clear();
	}
}

void fileInfo::addPair(string w) {
	auto emplaceInfo = info.try_emplace(w, 1);
	if (emplaceInfo.second == false)
		(emplaceInfo.first->second)++;
}

void fileInfo::analyse() {
	string buffer;
	while (getline(file, buffer))
		addStringTokenToMap(buffer);
}

void csvout::write(fileInfo& finfo) {
	map<const string, int>* infoMap = finfo.getMap();
	vector<comparingPair> outInfo;

	for (auto i = infoMap->begin(); i != infoMap->end(); i++) {
		comparingPair pair;
		pair.freq = i->second;
		pair.word = const_cast<string*>(&(i->first));
		outInfo.push_back(pair);
	}

	sort(outInfo.begin(), outInfo.end(), [](const comparingPair& p1, const comparingPair& p2) {return p1.freq > p2.freq; });
	
	file << "Word" << ',' << "Frequency" << ',' << "% from file" << '\n';
	for (auto i = outInfo.begin(); i != outInfo.end(); i++) {
		file << *(i->word) << ',' << i->freq << ',' << static_cast<double>(i->freq) / finfo.getNumWords() * 100 << '%' << '\n';
	}

}
