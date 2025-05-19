#include "fileFunctions.h"
#include <fstream>
#include<string>
#include<sstream>




void fileFunctions::WriteFile(string FileName, Trie diction) {

	ofstream file(FileName);
	if (file.is_open()) {
		queue<pair<string, int>> que;
		diction.displayQue(diction.getRoot(), "", que);
		while (!que.empty()) {
			file << que.front().first << " " << que.front().second << endl;
			que.pop();
		}
		file.close();
	}
	else {
		cout << "Can not find file\n";
	}
}

Trie fileFunctions::ReadFile(string FileName) {
	Trie diction;


	ifstream file(FileName);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			vector<string> splitStr = split(line);
			diction.insert(splitStr[0], stoi(splitStr[1]));
		}
		file.close();
	}
	else {
		WriteFile(FileName, {});
	}
	return diction;
}
vector<string> fileFunctions::split(const string str) {
	vector<string> splitStr;
	stringstream ss(str);
	string part;
	while (ss >> part) {
		splitStr.push_back(part);
	}

	return splitStr;
}