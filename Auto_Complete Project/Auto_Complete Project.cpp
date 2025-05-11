// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "fileFunctions.h"
using namespace std;

int main()
{
	Trie dictionaryWords = fileFunctions::ReadFile("Dictionary.txt");
	dictionaryWords.trieMenu();
	cout << endl;
	fileFunctions::WriteFile("Dictionary.txt", dictionaryWords);
	fileFunctions::WriteFile("Searched Words.txt", dictionaryWords.searchedWords);
	return 0;
}