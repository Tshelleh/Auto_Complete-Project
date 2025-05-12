// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"AppStart.h"
using namespace std;

int main()
{
	Trie dictionaryWords = fileFunctions::ReadFile("Dictionary.txt");
	Trie searchedWords= fileFunctions::ReadFile("Searched_Words.txt");
	AppStart AutoComplete(dictionaryWords, searchedWords);
	AutoComplete.trieMenu();
	cout << endl;
	fileFunctions::WriteFile("Searched_Words.txt",searchedWords);
	fileFunctions::WriteFile("Dictionary.txt", dictionaryWords);
	return 0;
}