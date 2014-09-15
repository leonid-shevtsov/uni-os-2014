#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include "lab3_dll.h"

using namespace std;

//	14) Знайти кількість слів, які починаються і закінчуються однією і тією ж літерою.
int performCalculations(char* dataString) {
	int answer = 0;
	stringstream f((string)dataString);
	string line;
	smatch m;
	regex re("\\w+");
	while( !f.eof() ) {
		f >> line;
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		regex_search(line, m, re);
		for (smatch::iterator i = m.begin(); i!= m.end(); ++i) {
			string word = *i;
			if (word[0] == word[word.size()-1]) {
				answer++;
			}
		}
	}
	stringstream stream;
	return answer;
}
