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
bool Trie::Delete(string Word) {
    if (!isFind(Word)) return false;
    stack<pair<TrieNode*, char>> wordStack;
    TrieNode* ptr = root;
    for (char c : Word) {
        wordStack.push({ ptr, c }); // push words letter in stack  
        ptr = ptr->children[c]; // move the ptr from root to the letter added until last letter
    }
    while (!wordStack.empty()) {
        TrieNode* ptr2 = wordStack.top().first; // pre last elememt as the parent
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
    return true;
}
void Trie::trieMenu() {
    int choice , freq;
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
        insert(word_prefix , freq);
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
void Trie::searchMenu() {
    string prefix;
    cout << "Start Search:....";
    cin >> prefix;
    int choice;
    cout << "1: Default Search\n"
        "2: BFS Search"
        "3: DFS Search";
    cin >> choice;
    switch (choice) 
    {
        //We have to put error hundling method here before take send the prefix as a parameter
        case 1:
            defaultSearch(prefix);
        case 2:
            bfsSearch(prefix);
        case 3:
            //dfsSearch();
        default:
            cout << "Enter a valid number";
    }
}
bool Trie::isFind(string word) {
    TrieNode* node = getPrefixNode(word);
    return node && node->endOfWord; //if the returned ptr not null & the node is an end of word
}
//vector<string> Trie::dfsSearch(string prefix) {
//	return vector<string> v = {};
//}