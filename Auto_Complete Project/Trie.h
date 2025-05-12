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
	int FrequencyWord;
	TrieNode();
	~TrieNode();
};

class Trie
{

	TrieNode* root;
public:
	Trie();
	~Trie();
	void insert(string Word, int freq);
	void Delete(string Word);
	void display(TrieNode* node, string curr);
	void AllWord(TrieNode* node, string curr, queue<pair<string, int>>& que);
	TrieNode* getRoot();
	TrieNode* getPrefixNode(string& prefix);
	bool isFind(string);
};

