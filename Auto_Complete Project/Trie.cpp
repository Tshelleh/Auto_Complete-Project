#include "Trie.h"

TrieNode::TrieNode() {
	children = {};
	endOfWord = false;
	FrequencyWord = 0;
}
TrieNode::TrieNode(char c) {
	children[c] = NULL;
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

}
void Trie::Delete(string Word) {

}
vector<string> Trie::defaultSearch(string prefix) {

}
vector<string> Trie::bfsSearch(string prefix) {

}
vector<string> Trie::bdsSearch(string prefix) {

}
