
#include<iostream>
#include "fileFunctions.h"

class AppStart{
public:
	AppStart(Trie& dictionary,Trie& searched);
	~AppStart();
	Trie searchedWords;
	Trie dictionaryWords;
	vector<pair<string, int>> defaultSearch(string prefix);
	vector<string> bfsSearch(string prefix);
	vector<string> dfsSearch(string prefix);
	string highlight(string word);
	void The_Most_freq_que(vector<pair<string, int>>& Words);
	static bool compare(pair<string, int> a, pair<string, int> b);
	void AddAuto(string pref);
	void trieMenu();
	void searchMenu();
	void displaySuggestions(vector<string>);

};

