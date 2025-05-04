// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "fileFunctions.h"
using namespace std;

int main()
{
	Trie t = fileFunctions::ReadFile("Dictionary.txt");
	
	t.trieMenu();
	cout << endl;
	fileFunctions::WriteFile("Dictionary.txt",t);
	return 0;
}