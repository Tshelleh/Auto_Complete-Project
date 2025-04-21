// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "fileFunctions.h"
using namespace std;

int main()
{
	Trie t=fileFunctions::ReadFile("Dictionary.txt");
	
	t.insert("dog", 1);
	t.insert("dog", 1);
	t.insert("cat", 1);
	t.insert("car", 1);
	t.insert("program", 1);

	t.display(t.getRoot(), "");

	/*fileFunctions::WriteFile("Dictionary.txt",t);*/
	return 0;
}

