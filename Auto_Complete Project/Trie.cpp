#include "Trie.h"
#include <sstream>
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
//void Trie::insert(string Word) {
//  transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
//	TrieNode* current = root;
//
//	for (char c : Word) {
//		if (!current->children[c])
//			current->children[c] = new TrieNode();
//
//		current = current->children[c];
//	}
//	current->endOfWord = true;
//	current->FrequencyWord++;
//}
void Trie::insert(string Word, int freq) {

    transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
    TrieNode* current = root;

    for (char c : Word) {
        if (!current->children[c])
            current->children[c] = new TrieNode();

        current = current->children[c];
    }
    current->endOfWord = true;
    current->FrequencyWord += freq;
}
void Trie::Delete(string Word) {

}
void Trie::display(TrieNode* node, string curr) {
    if (node->endOfWord) {
        string str = curr + " " + to_string(node->FrequencyWord);
        cout << str << endl;
    }
    for (auto& pair : node->children) {
        display(pair.second, curr + pair.first);
    }
}
void Trie::AllWord(TrieNode* node, string curr, queue<pair<string, int>>& que) {
    if (node->endOfWord) {
        que.push({ curr, node->FrequencyWord });
    }
    for (auto& pair : node->children) {
        AllWord(pair.second, curr + pair.first, que);
    }
}
TrieNode* Trie::getRoot() {
    return root;
}

string Trie::highlight(string word) {
    stringstream ss;
    ss << "\033[36m\033[3m" << word << "\033[0m";
    std::string str = ss.str();
    return str;
}
vector<pair<string, int>> Trie::defaultSearch(string prefix) {
    vector<pair<string, int>> Most_freq;
    TrieNode* prefixNode = getPrefixNode(prefix);
    if (!prefixNode) {
        return Most_freq;
    }
    string lowerPrefix = prefix;
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    queue<pair<string, int>> q;
    AllWord(prefixNode, lowerPrefix, q);
    while (!q.empty()) {
        Most_freq.push_back({ q.front().first,q.front().second });
        q.pop();
    }
    The_Most_freq_que(Most_freq);

    // Added snippet before return
    for (int i = 0; i < Most_freq.size(); i++) {
        if (Most_freq[i].first == prefix) {
            Most_freq[i].first = highlight(Most_freq[i].first);
            break;
        }
    }

    return Most_freq;
}TrieNode* Trie::getPrefixNode(string& prefix) {
    for (char c : prefix) {
        if (!isalpha(c)) {
            cout << "Invalid prefix: " << prefix << ". Only alphabetic characters allowed.\n";
            return nullptr;
        }
    }

    string lowerPrefix = prefix;
    //case sensetive
    transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);

    TrieNode* current = root;
    for (char c : lowerPrefix) {
        if (current->children.find(c) == current->children.end()) {
            return nullptr;
        }
        current = current->children[c];
    }
    return current;
}

void Trie::The_Most_freq_que(vector<pair<string, int>>& Words) {
    sort(Words.begin(), Words.end(), compare);
}

bool Trie::compare(pair<string, int> a, pair<string, int> b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
vector<string> Trie::bfsSearch(string prefix) {
    vector<string> suggestions;

    TrieNode* prefixNode = getPrefixNode(prefix);
    if (!prefixNode) {
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
            break;
        }
    }

    return suggestions;
}


//vector<string> Trie::bdsSearch(string prefix) {


//vector<string> Trie::defaultSearch(string prefix) {
//
//	return vector<string> v = {};
//}
//vector<string> Trie::bfsSearch(string prefix) {
//	return vector<string> v = {};
//}
//vector<string> Trie::dfsSearch(string prefix) {
//	return vector<string> v = {};
//}