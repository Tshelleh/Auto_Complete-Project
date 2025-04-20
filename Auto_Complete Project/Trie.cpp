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
void Trie::insert(string Word) {
	TrieNode* current = root;

	for (char c : Word) {
		if (current->children.find(c) == current->children.end())
			current->children[c] = new TrieNode();

		current = current->children[c];
	}
	current->endOfWord = true;
	current->FrequencyWord++;
}
void Trie::Delete(string Word) {

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
