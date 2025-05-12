#include<iostream>
#include<map>
#include"Trie.h"
//#include"AppStart.h"
#include<string>

class fileFunctions
{
public:
	static void WriteFile(string filePath, Trie diction);
	static  Trie ReadFile(string filePath);
	static vector<string> split(const string str);
};