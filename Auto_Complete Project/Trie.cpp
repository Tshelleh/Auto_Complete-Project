#include "Trie.h"

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
	TrieNode* current = root;

	for (char c : Word) {
		if (!current->children[c])
			current->children[c] = new TrieNode();

		current = current->children[c];
	}
	current->endOfWord = true;
	current->FrequencyWord+=freq;
}
void Trie::Delete(string Word) {

}
void Trie::display(TrieNode* node, string curr) {
	if (node->endOfWord) {
		string str =curr + " " + to_string(node->FrequencyWord);
		cout << str << endl;
	}
	for (auto& pair : node->children) {
		display(pair.second, curr + pair.first);
	}
}
void Trie::AllWord(TrieNode* node, string curr, queue<string>& que) {
	if (node->endOfWord) {
		string str = curr + " " + to_string(node->FrequencyWord);
		que.push(str);
	}
	for (auto& pair : node->children) {
		AllWord(pair.second, curr + pair.first,que);
	}
}
TrieNode* Trie::getRoot() {
	return root;
}

//vector<string> Trie::defaultSearch(string prefix) {
//
//	return vector<string> v = {};
//}
//vector<string> Trie::bfsSearch(string prefix) {
//	return vector<string> v = {};
//}
//vector<string> Trie::bdsSearch(string prefix) {
//	return vector<string> v = {};
//}
