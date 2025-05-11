// Auto_Complete Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <thread>
#include <conio.h>
#include <mutex>
#include <iostream>
#include "fileFunctions.h"
#include <mutex>
using namespace std;

string prefix = "";
mutex mtx;
bool finished = false;
void suggestionsDisplay(Trie& t, int searchNumber) {
    string lastPrefix = "";

    while (!finished) {
        this_thread::sleep_for(chrono::milliseconds(100)); // Wait a little to reduce CPU load
       
        std::unique_lock<std::mutex> lock(mtx);
        if (lastPrefix != prefix) {
            lastPrefix = prefix;
            system("cls"); // Clear screen 
            cout << "you are searching for " << prefix << endl;
            cout << "suggestions :" << endl;

            if (searchNumber == 1) {
                vector<pair<string, int>> v = t.defaultSearch(prefix);
                for (const auto& p : v) {
                    cout << p.first <<endl;
                }
            }
            else if (searchNumber == 2) {
                vector<string> v = t.bfsSearch(prefix);
                for (int i = 0; i < v.size(); i++) {
                    cout << v[i] << endl;
                }
            }
            else if (searchNumber == 3) {
                //vector<string> v = t.dfsSearch(prefix);
                //for (int i = 0; i < v.size(); i++) {
                //  cout << v[i] << endl;
                //}
            }


        }
      
    }
    mtx.unlock();

}
void immediatInput() {
    while (true) {
        char ch = _getch(); // keep taking inputs from user
        std::unique_lock<std::mutex> lock(mtx);  // lock using 'prefix' variable untill

        if (ch == '\r') { // if user inputs enter then break the search process
            finished = true;
            break;

        }
        else if (ch == '\b') { // if user inputs back space then pop last char from prefix
            if (!prefix.empty())
                prefix.pop_back();
        }
        else { // else add entered char into prefix and search 
            prefix += ch;
            
        }
    }
}
void joining(Trie& t, int searchnumber) {

    thread t1(immediatInput);
    thread t2(suggestionsDisplay, ref(t), searchnumber); 

    t1.join();
    t2.join();
}
void Trie::searchMenu() {
    int choice;
    cout << 
        "1: Default Search\n"
        "2: BFS Search"
        "3: DFS Search";
    cin >> choice;
        //We have to put error hundling method here before take send the prefix as a parameter
    prefix = "";
    finished = false;
    joining(*this, choice);
}
void Trie::trieMenu() {
    int choice, freq;
    char again;
    cout << "1: Search\n"
        "2: Display Dectionary\n"
        "3: Delete word\n"
        "4: Add word\n"
        "5: Exit\n"
        "==> ";
    cin >> choice;
    string word_prefix;
    switch (choice)
    {
    case 1:
        searchMenu();
        break;
    case 2:
        //display();
    case 3:
        word_prefix = "";
        cout << "Enter a word or a prefix to delete\n=>";
        cin >> word_prefix;
        if (Delete(word_prefix)) cout << "word deleted successfully";
        else cout << "deletetion failed word dosent exictes";
        break;
    case 4:
        word_prefix = "";
        cout << "Enter the word\n";
        cin >> word_prefix;
        cout << "Enter the frequency\n";
        cin >> freq;
        insert(word_prefix, freq);
        break;
    default:
        break;
    }
    cout << endl << "Do you want to continue? Write 'y' or 'Y' if yes" << endl;
    cin >> again;
    if (again == 'y' || again == 'Y')
    {
        trieMenu();
    }
}
int main()
{
	Trie t = fileFunctions::ReadFile("Dictionary.txt");
	t.trieMenu();
	vector <pair<string, int>> v;
	v = t.defaultSearch("");
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << " " << v[i].second << endl;
	}
	cout << endl;

	t.display(t.getRoot(), "");

	/*fileFunctions::WriteFile("Dictionary.txt",t);*/
	return 0;
}

