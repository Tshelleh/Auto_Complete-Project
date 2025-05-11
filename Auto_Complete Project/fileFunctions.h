#include<iostream>
#include<map>
#include "Trie.h"
class fileFunctions
{
public:
	static void WriteFile(string filePath, Trie diction);
	static  Trie ReadFile(string filePath);
	static vector<string> split(const string str);
	static void WriteFile(string filePath, map<string, int>);
};

