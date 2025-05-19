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

    queue<pair<string, int>> q;
    dictionaryWords.displayQue(prefixNode, prefix, q);
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

//GEHAD BFS

//vector<string> AppStart::bfsSearch(string prefix) {
//    //Initailize elements 
//    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
//    queue<pair<TrieNode*, string>> childrenForTheNode;
//    vector<string> suggestions; 
//
//
//    //Start the BFS 
//    if (prefixNode == dictionaryWords.getRoot()) { //If the prefixNode is the same the root node this mean the word is not in the dictionary
//        cout << "Not Found\n";
//        return suggestions;
//    }
//    if (prefixNode) { //If a value reteruned from the getPrefixMethod |Which Is Not NULL|
//
//        childrenForTheNode.push({ prefixNode, prefix });
//        while (!childrenForTheNode.empty()) {
//            auto currPair = childrenForTheNode.front();
//            childrenForTheNode.pop();
//
//            if (currPair.first->endOfWord)
//                suggestions.push_back(currPair.second);
//
//            for (char c = 'a'; c <= 'z'; c++) {
//                if (currPair.first->children.find(c) != currPair.first->children.end()) {
//                    childrenForTheNode.push({ currPair.first->children[c], currPair.second + c });
//                }
//            }
//        }
//    }
//    for (int i = 0; i < suggestions.size(); i++) {
//        if (suggestions[i] == prefix) {
//            suggestions[i] = highlight(suggestions[i]);
//            prefixNode->FrequencyWord++;
//            break;
//        }
//    }
//
//    return suggestions;
//}

// Search Using DFS

//vector<string> AppStart::dfsSearch(string prefix) {
//    vector<string> suggestions;
//    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
//    if (!prefixNode) {
//        return suggestions;
//    }
//    if (prefixNode == dictionaryWords.getRoot()) //that mean the word is not found
//    {
//        cout << "not found\n";
//        return suggestions;
//    }
//    string lowerPrefix = prefix;
//    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);
//
//    stack<char> sortedKeys;
//    function<void(TrieNode*, string)> dfsHelper = [&](TrieNode* node, string currentWord) {
//
//        if (node->endOfWord) {
//            suggestions.push_back(currentWord);
//            if (!sortedKeys.empty()) {
//                sortedKeys.pop();
//            }
//        }
//
//        for (char c = 'a'; c <= 'z'; ++c) {
//            if (node->children.find(c) != node->children.end()) {
//                sortedKeys.push(c);
//                dfsHelper(node->children[c], currentWord + c);
//            }
//        }
//        };
//
//    dfsHelper(prefixNode, lowerPrefix);
//
//    for (int i = 0; i < suggestions.size(); i++) {
//        if (suggestions[i] == lowerPrefix) {
//            suggestions[i] = highlight(suggestions[i]);
//            prefixNode->FrequencyWord++;   //increase freq when we search on the exactly word 
//            break;
//        }
//    }
//
//
//    return suggestions;
//}



//vector<string> AppStart::dfsSearch(string prefix) {
//    vector<string> suggestions;
//    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);
//
//    if (!prefixNode || prefixNode == dictionaryWords.getRoot()) {
//        cout << "Not found\n";
//        return suggestions;
//    }
//
//    string lowerPrefix = prefix;
//    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);
//
//    stack<pair<TrieNode*, string>> dfsStack;
//    dfsStack.push({ prefixNode, lowerPrefix });
//
//    while (!dfsStack.empty()) {
//        auto stackTopWord = dfsStack.top();
//        dfsStack.pop();
//
//        if (stackTopWord.first ->endOfWord) {
//            suggestions.push_back(stackTopWord.second);
//        }
//
//        for (char c = 'z'; c >= 'a'; --c) {
//            if (stackTopWord.first ->children.count(c)) {
//                dfsStack.push({ stackTopWord.first->children[c], stackTopWord.second + c });
//            }
//        }
//    }
//
//    for (int i = 0; i < suggestions.size(); i++) {
//        if (suggestions[i] == lowerPrefix) {
//            suggestions[i] = highlight(suggestions[i]);
//            prefixNode->FrequencyWord++;  // Increase frequency for exact match
//            break;
//        }
//    }
//
//    return suggestions;
//}

//Gehad DFS

vector<string> AppStart::dfsSearch(string prefix) {
    vector<string> suggestions;
    stack<pair<TrieNode*, string>> dfsStack;

    TrieNode* prefixNode = dictionaryWords.getPrefixNode(prefix);

    if (!prefixNode || prefixNode == dictionaryWords.getRoot())
    {
        cout << "No wards has been found!\n";
        return suggestions;
    }
    else {
        dfsStack.push({ prefixNode, prefix });
        while (!dfsStack.empty()) {
            auto currPair = dfsStack.top();
            dfsStack.pop();
            if (currPair.first->endOfWord)
                suggestions.push_back(currPair.second);


            for (char c = 'z'; c >= 'a'; c--) {
                if (currPair.first->children.find(c) != currPair.first->children.end())
                    dfsStack.push({ currPair.first->children[c], currPair.second + c });
            }
        }
    }
    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i] == prefix) {
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
    string word_prefix;
    while (choice != 5) {
        cout << "\n"
            "1: Search\n"
            "2: Display Dictionary\n"
            "3: Delete word\n"
            "4: Add word\n"
            "5: Exit"
            "\n"
            "==> ";

        while (!(cin >> choice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input 
            cout << "Invalid input! Please enter a number between 1 and 5.\n==> ";
        }

        if (choice > 0 && choice < 6) {
            switch (choice) {
            case 1:
                searchMenu();
                break;
            case 2:
                dictionaryWords.display(dictionaryWords.getRoot(), "");
                break;
            case 3:
                word_prefix = "";
                handelDelete(word_prefix);
                break;
            case 4:
                word_prefix = "";
                cout << "Enter the word\n";
                cin >> word_prefix;
                transform(word_prefix.begin(), word_prefix.end(), word_prefix.begin(), ::tolower);
                dictionaryWords.insert(word_prefix, 0);
                cout << "Word Added Successfully!";
                break;
            default:
                break;
            }
        }
        else {
            cout << "Invalid number! Please choose between 1 and 5.\n";
        }
    }
}
void AppStart::searchMenu() {
    int choice, index;
    vector<pair<string, int>> temp;
    vector<string> temp2;
    cout << "1: Default Search\n"
        << "2: BFS Search\n"
        << "3: DFS Search\n"
        << "==> ";

    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number between 1 and 3.\n==> ";
    }

    string prefix;
    char c;
    cout << "Start Search:";
    while (true) {
        c = _getch();

        if (c == '\r')
            break;
        else if (c == '\b') {
            system("cls");
            if (!prefix.empty()) {
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
        switch (choice) {
        case 1:
            temp = defaultSearch(prefix);
            index = 1;
            for (pair<string, int> s : temp) {
                cout << index << ". " << s.first << endl;
                index++;
            }
            break;
        case 2:
            temp2 = bfsSearch(prefix);
            displaySuggestions(temp2);
            break;
        case 3:
            temp2 = dfsSearch(prefix);
            displaySuggestions(temp2);
            break;
        }
    }
    if (!dictionaryWords.isFind(prefix)) {
        AddAuto(prefix);
    }
}
void AppStart::handelDelete(string word_prefix) {
    vector<string> wordsForDelete;
    int deleteIndex;
    cout << "Enter a word or a prefix to delete\n=>";
    cin >> word_prefix;
    if (dictionaryWords.isFind(word_prefix)) {
        dictionaryWords.Delete(word_prefix);
    }
    else {

        wordsForDelete = bfsSearch(word_prefix);
        //cout << "Do you mean: " << HandleUnfoundPrefix(word_prefix);
        displaySuggestions(wordsForDelete);
        cout << "Choose which word you want to delete:";
        cin >> deleteIndex;
        if (deleteIndex > 0 && deleteIndex <= wordsForDelete.size())
            dictionaryWords.Delete(wordsForDelete[--deleteIndex]);
        else
            cout << "Invalid choise.\nPlease, enter a number between 1 and " << wordsForDelete.size() << endl;
    }
    cout << "Word has been deleted successfully!";
}

void AppStart::displaySuggestions(vector<string> Sugg) {
    int i = 1;
    for (string s : Sugg)
    {
        cout << i << ". " << s << endl;
        i++;
    }
}

