#pragma once
#include "Trie.h"
#include<vector>
class search
{
	Trie trie;
	vector<string> basicResults;
	vector<pair<string, int>> frequencyResults;

	void performBfsSearch(const string& prefix);
	void performDefaultSearch(const string& prefix);
	string highlight(string word);
	vector<string> highlightprefix(string prefix, vector<string> suggestions);
	////////////////////////////////////////
	//after entering full prefix
	//if (node->endOfWord)
	//{
	//	string currCopy = curr;
	//	curr = highlightWord(curr);
	//	resultvector.push_back(curr);
	//	//then we continue search with the copy 
	//	//replace dfssearch with the type of search you are making
	//	dfssearch(pair.second, currCopy + pair.first)
	//}
	//////////////////////////////////////////
};

