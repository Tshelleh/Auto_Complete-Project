#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
class TrieNode
{  public:
	unordered_map <char,TrieNode*> children;
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
	void insert(string Word);
	void Delete(string Word);
	vector<string> defaultSearch(string prefix);
	vector<string> bfsSearch(string prefix);
	vector<string> bdsSearch(string prefix);

};

