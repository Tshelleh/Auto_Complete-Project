#include "search.h"
#include <sstream>
void search::performBfsSearch(const string& prefix) {
    basicResults = trie.bfsSearch(prefix);
}

void search::performDefaultSearch(const string& prefix) {
    frequencyResults = trie.defaultSearch(prefix);
}
string search::highlight(string word) {
	stringstream ss;
	ss << "\033[36m\033[3m" << word << "\033[0m";
	std::string str = ss.str();
	return str;
}
void search::highlightBfs(string prefix, vector<string> suggestions)
{
    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i] == prefix) {
            suggestions[i] = highlight(suggestions[i]);
            break;
        }
    }

}
void search::highlightDefault(string prefix, vector<pair<string, int>> suggestions) {
    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestions[i].first == prefix) {
            suggestions[i].first = highlight(suggestions[i].first);
            break;
        }
    }

}
