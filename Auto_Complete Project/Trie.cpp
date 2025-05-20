#include "Trie.h"
#include <sstream>
#include <stack>
#include <map>
#include <functional>
#include<conio.h>
using namespace std;

TrieNode::TrieNode() {
    children = {};
    endOfWord = false;
    FrequencyWord = 0;
}
TrieNode::~TrieNode() {

}
Trie::Trie() {
    root = new TrieNode();
}
Trie::~Trie() {
    delete root;
    root = nullptr;
}

// Add new word to the dictionary
void Trie::insert(string Word, int freq) {
    string lowerPrefix = Word;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);
    TrieNode* current = root;

    for (char c : Word) {
        if (!current->children[c])
            current->children[c] = new TrieNode();

        current = current->children[c];
    }
    current->endOfWord = true;
    current->FrequencyWord += freq;//freq must be in search also. her the freq for insert word from file in trie  and manual adding

}

//// display all word in the dictionary only
void Trie::display(TrieNode* node, string curr) { //index  => to diplay it with numbers 
    if (node->endOfWord) {
        string str = curr;
        cout << str << endl;
    }
    for (auto& pair : node->children) {
        display(pair.second, curr + pair.first);
    }
}

// collect all word in the dictionary and store it in a queue
void Trie::allWords(TrieNode* node, string curr, queue<pair<string, int>>& que) {
    if (node->endOfWord) {
        que.push({ curr, node->FrequencyWord });
    }
    for (auto& pair : node->children) {
        allWords(pair.second, curr + pair.first, que);
    }
}

//get root node
TrieNode* Trie::getRoot() {
    return root;
}

// helper function for all search methods (get the prefix node)
TrieNode* Trie::getPrefixNode(string& prefix) {
    if (prefix == "")
    {
        cout << "No matched words" << endl; //We will use it in GUI Insha'allah not here
        return nullptr;
    }
    else {
        for (char c : prefix) {
            if (!isalpha(c)) {
                cout << "Invalid prefix: " << prefix << ". Only alphabetic characters allowed.\n";
                //return nullptr;
            }
        }

        string lowerPrefix = prefix;
        //case sensetive
        transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

        TrieNode* current = root;
        for (char c : lowerPrefix) {
            if (current->children.find(c) == current->children.end()) {
                return root;
            }
            current = current->children[c];
        }
        return current;
    }
}

void Trie::Delete(string Word) {
    if (isFind(Word))
    {
        stack<pair<TrieNode*, char>> wordStack;
        TrieNode* ptr = root;
        for (char c : Word) {
            wordStack.push({ ptr, c }); // push words letter in stack  
            ptr = ptr->children[c]; // move the ptr from root to the letter added until last letter
        }

        while (!wordStack.empty()) {
            TrieNode* ptr2 = wordStack.top().first; // pre last element as the parent
            char c = wordStack.top().second; // last element as the child
            ptr = ptr2;
            ptr = ptr->children[c]; // point to last letter in stack
            wordStack.pop();
            if (ptr->children.empty() && !ptr->endOfWord) {

                ptr->children.erase(c); // delete letters child that has no children
            }
            else {
                ptr->endOfWord = false;
                break;
            }
        }
    }
}

//helper function for delete function
//it return true if the exactly word is found

bool Trie::isFind(string word) {
    TrieNode* node = getPrefixNode(word);
    return node && node->endOfWord; //if the returned ptr not null & the node is an end of word;
}