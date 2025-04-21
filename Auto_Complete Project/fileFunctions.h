#include<iostream>
#include "Trie.h"
class fileFunctions
{
public:
	/*static void WriteFile(string FileName, Trie diction);*/
	static  Trie ReadFile(string FileName);
	static vector<string> split(const string str);
};

