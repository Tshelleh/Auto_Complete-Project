#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<queue>
#include<stack>
using namespace std;

class TrieNode
{
public:
	unordered_map <char, TrieNode*> children;
	bool endOfWord;
	TrieNode();
	~TrieNode();
	int FrequencyWord;
};

class Trie
{
	TrieNode* root;
public:
	map<string, int > searchedWords;
	Trie();
	~Trie();
	/*void insert(string Word);*/
	void insert(string Word, int freq);
	void Delete(string Word);
	vector<pair<string, int>> defaultSearch(string prefix);
	vector<string> bfsSearch(string prefix);
	vector<string> dfsSearch(string prefix);
	void display(TrieNode* node, string curr);
	void AllWord(TrieNode* node, string curr, queue<pair<string, int>>& que);
	TrieNode* getRoot();
	string highlight(string word);
	TrieNode* getPrefixNode(string& prefix);
	void The_Most_freq_que(vector<pair<string, int>>& Words);
	static bool compare(pair<string, int> a, pair<string, int> b);
	void trieMenu();
	void searchMenu();
	bool isFind(string);
	void displaySuggestions(vector<string>);
	//string HandleUnfoundPrefix(string);
};

