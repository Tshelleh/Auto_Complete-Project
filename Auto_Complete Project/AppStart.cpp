#include "AppStart.h"
#include <sstream>
#include <stack>
#include <functional>
#include<conio.h>
using namespace std;

AppStart::AppStart(Trie& dictionary, Trie& searched) {
    dictionaryWords = dictionary;
    searchedWords = searched;
}
AppStart::~AppStart() {

}

//highlight the word
string AppStart::highlight(string word) {
    stringstream ss;
    ss << "\033[36m\033[3m" << word << "\033[0m";
    std::string str = ss.str();
    return str;
}

// search for the most frequency word (default search)
vector<pair<string, int>> AppStart::defaultSearch(string prefix) {
    vector<pair<string, int>> Most_freq;
    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
    if (!prefixNode) {
        return Most_freq;
    }
    if (prefixNode == dictionaryWords.getRoot()) //that mean the word is not found
    {
        cout << "not found\n";
        return Most_freq;
    }

    string lowerPrefix = prefix;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    queue<pair<string, int>> q;
    dictionaryWords.AllWord(prefixNode, lowerPrefix, q);
    while (!q.empty()) {
        Most_freq.push_back({ q.front().first,q.front().second });
        q.pop();
    }
    The_Most_freq_que(Most_freq);

    // Added snippet before return
    for (int i = 0; i < Most_freq.size(); i++) {
        if (Most_freq[i].first == prefix) {
            Most_freq[i].first = highlight(Most_freq[i].first);
            prefixNode->FrequencyWord++;   //increase freq when we search on the exactly word 
            break;
        }
    }

    return Most_freq;
}

// helper function for default search 
void AppStart::The_Most_freq_que(vector<pair<string, int>>& Words) {
    sort(Words.begin(), Words.end(), compare);
}

// helper function for default search 
bool AppStart::compare(pair<string, int> a, pair<string, int> b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

// short path search using bfs
vector<string> AppStart::bfsSearch(string prefix) {
    vector<string> suggestions;

    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
    if (!prefixNode) {
        return suggestions;
    }
    if (prefixNode == dictionaryWords.getRoot()) //that mean the word is not found
    {
        cout << "not found\n";
        return suggestions;
    }

    string lowerPrefix = prefix;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    queue<pair<TrieNode*, string>> q;
    q.push({ prefixNode, lowerPrefix });

    while (!q.empty()) {
        auto pair = q.front();
        TrieNode* current = pair.first;
        string word = pair.second;
        q.pop();

        if (current->endOfWord) {
            suggestions.push_back(word);

        }

        for (char c = 'a'; c <= 'z'; ++c) {
            if (current->children.find(c) != current->children.end()) {
                q.push({ current->children[c], word + c });
            }
        }
    }
    // Added snippet before return
    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i] == prefix) {
            suggestions[i] = highlight(suggestions[i]);
            prefixNode->FrequencyWord++;   //increase freq when we search on the exactly word 
            break;
        }
    }

    return suggestions;
}

/*
search using dfs

vector<string> AppStart::dfsSearch(string prefix) {
    vector<string> suggestions;
    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
    if (!prefixNode) {
        return suggestions;
    }
    if (prefixNode == dictionaryWords.getRoot()) //that mean the word is not found
    {
        cout << "not found\n";
        return suggestions;
    }
    string lowerPrefix = prefix;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    stack<char> sortedKeys;
    function<void(TrieNode*, string)> dfsHelper = [&](TrieNode* node, string currentWord) {

        if (node->endOfWord) {
            suggestions.push_back(currentWord);
            if (!sortedKeys.empty()) {
                sortedKeys.pop();
            }
        }

        for (char c = 'a'; c <= 'z'; ++c) {
            if (node->children.find(c) != node->children.end()) {
                sortedKeys.push(c);
                dfsHelper(node->children[c], currentWord + c);
            }
        }
        };

    dfsHelper(prefixNode, lowerPrefix);

    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i] == lowerPrefix) {
            suggestions[i] = highlight(suggestions[i]);
            prefixNode->FrequencyWord++;   //increase freq when we search on the exactly word 
            break;
        }
    }


    return suggestions;
}
*/

// #Enhanced DFS search method
vector<string> AppStart::dfsSearch(string prefix) {
    vector<string> suggestions;
    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);

    if (!prefixNode || prefixNode == dictionaryWords.getRoot()) {
        cout << "Not found\n";
        return suggestions;
    }

    string lowerPrefix = prefix;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    stack<pair<TrieNode*, string>> dfsStack;
    dfsStack.push({ prefixNode, lowerPrefix });

    while (!dfsStack.empty()) {
        auto stackTopWord = dfsStack.top(); //first =>  node , second => currentWord
        dfsStack.pop();

        if (stackTopWord.first ->endOfWord) {
            suggestions.push_back(stackTopWord.second);
        }

        for (char c = 'z'; c >= 'a'; --c) {
            if (stackTopWord.first ->children.count(c)) {
                dfsStack.push({ stackTopWord.first->children[c], stackTopWord.second + c });
            }
        }
    }

    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i] == lowerPrefix) {
            suggestions[i] = highlight(suggestions[i]);
            prefixNode->FrequencyWord++;  // Increase frequency for exact match
            break;
        }
    }

    return suggestions;
}

//this function for detail with un founding entered word 
//it count  the frequency and add word automatically to the dictionary if freq =3
void AppStart::AddAuto(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    searchedWords.insert(word, 1);

    if (searchedWords.getPrefixNode(word)->FrequencyWord == 3) {
        dictionaryWords.insert(word, 3);
        searchedWords.Delete(word);
        cout << word << "added to suggestions after 3 searches!\n";
    }
}

//main menu
void AppStart::trieMenu() {
    int choice = 0;
    while (choice != 5)
    {
        cout << "\n"
            "1: Search\n"
            "2: Display Dictionary\n"
            "3: Delete word\n"
            "4: Add word\n"
            "5: Exit"
            "\n"
            "==> ";
        cin >> choice;
        string word_prefix;
        switch (choice)
        {
        case 1:
            searchMenu();
            break;
        case 2:
            dictionaryWords.display(dictionaryWords.getRoot(), "");
            break;
        case 3:
            word_prefix = "";
            cout << "Enter a word or a prefix to delete\n=>";
            cin >> word_prefix;
            //cout << "Do you mean: " << HandleUnfoundPrefix(word_prefix);
            dictionaryWords.Delete(word_prefix);
            break;
        case 4:
            word_prefix = "";
            cout << "Enter the word\n";
            cin >> word_prefix;
            dictionaryWords.insert(word_prefix, 0);
            break;
        default:
            break;
        }
    }
}

void AppStart::searchMenu() {
    int choice;
    vector<pair<string, int>> temp;
    vector<string> temp2;
    cout << "1: Default Search\n"
        "2: BFS Search\n"
        "3: DFS Search\n";
    cin >> choice;
    string prefix;
    char c;
    cout << "Start Search:";
    while (true) {
        c = _getch();

        if (c == '\r')
            break;
        else if (c == '\b')
        {
            system("cls");
            if (!prefix.empty())
            {
                prefix.pop_back();
                cout << "\rStart Search:" << prefix;
            }
        }
        else {
            system("cls");
            prefix += c;
            cout << "\rStart Search:" << prefix;
        }
        cout << "\n";
        switch (choice)
        {
        case 1:
            temp = defaultSearch(prefix);
            for (pair<string, int> s : temp)
                cout << s.first << " " << s.second << endl;
            break;
        case 2:
            temp2 = bfsSearch(prefix);
            displaySuggestions(temp2);
            break;
        case 3:
            temp2 = dfsSearch(prefix);
            displaySuggestions(temp2);
            break;
        default:
            cout << "Enter a valid number";
        }

    }
    if (!dictionaryWords.isFind(prefix)) //that mean the word is not found
    {
        AddAuto(prefix);
    }

}

void AppStart::displaySuggestions(vector<string> Sugg) {
    for (string s : Sugg)
        cout << s << endl;
}
