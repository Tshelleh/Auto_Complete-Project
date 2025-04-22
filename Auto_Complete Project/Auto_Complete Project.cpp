// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "fileFunctions.h"
using namespace std;

int main()
{
	Trie t = fileFunctions::ReadFile("Dictionary.txt");
	t.trieMenu();
	/*vector <pair<string, int>> v;
	v = t.defaultSearch("");
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << " " << v[i].second << endl;
	}*/
	cout << endl;

	t.display(t.getRoot(), "");

	/*fileFunctions::WriteFile("Dictionary.txt",t);*/
	return 0;
}

