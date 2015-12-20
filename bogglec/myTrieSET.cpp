#include "myTrieSET.h"

// Initializes an empty set of strings.
myTrieSET::myTrieSET() : N_(0), root_(NULL), current_(NULL) {
}

// Destroys trie
myTrieSET::~myTrieSET() {
	destroy(root_);
}

// Does the set contain the given key?
bool myTrieSET::contains(std::string& key) {
	Node* x = get(root_, key, 0);
	if (x == NULL) return false;
	return x->isString_;
}

// Helper function for contains()
myTrieSET::Node* myTrieSET::get(Node* x, const std::string& key, int d) {
	if (x == NULL) return NULL;
	if (d == key.size()) return x;
	char c = key[d];
	return get(x->next_[CHAR_TO_INDEX(c)], key, d + 1);
}

// Adds the key to the set if it is not already present.
void myTrieSET::add(std::string& key) {
	root_ = add(root_, key, 0);
}

// Helper function for add()
myTrieSET::Node* myTrieSET::add(Node* x, std::string& key, int d) {
	if (x == NULL) x = new Node();
	if (d == key.size()) {
		if (!x->isString_) N_++;
		x->isString_ = true;
	}
	else {
		char c = key[d];
		x->next_[CHAR_TO_INDEX(c)] = add(x->next_[CHAR_TO_INDEX(c)], key, d + 1);
	}
	return x;
}

// Returns the number of strings in the set.
int myTrieSET::size() { return N_; }

// Is the set empty?
bool myTrieSET::isEmpty() { return N_ == 0; }

// Returns all of the keys in the set that start with prefix.
Bag<std::string> myTrieSET::keysWithPrefix(const std::string& prefix) {
	Bag<std::string> results;
	Node* x = get(root_, prefix, 0);
	collect(x, prefix, results);
	return results;
}

// Helper function for keysWithPrefix
void myTrieSET::collect(Node* x, std::string prefix, Bag<std::string>& results) {
	if (x == NULL) return;
	if (x->isString_) results.add(prefix);
	for (char c = 0 + 'A'; c < R_ + 'A'; c++) {
		prefix += c;
		collect(x->next_[CHAR_TO_INDEX(c)], prefix, results);
		prefix.pop_back();
	}
}

// Returns the string in the set that is the longest prefix of query
// or null if no such string.
std::string myTrieSET::longestPrefixOf(const std::string& query) {
	int length = longestPrefixOf(root_, query, 0, -1);
	if (length == -1) return NULL;
	return query.substr(0, length);
}


// Helper function for longestPrefixOf
// Returns the length of the longest string key in the subtrie rooted
// at x that is a prefix of the query string, assuming the first d 
// characters match and we have already found a prefix match of length length
int myTrieSET::longestPrefixOf(Node* x, std::string query, int d, int length) {
	if (x == NULL) return length;
	if (x->isString_) length = d;
	if (d == query.size()) return length;
	char c = query[d];
	return longestPrefixOf(x->next_[CHAR_TO_INDEX(c)], query, d + 1, length);
}

// Returns all of the keys in the set that match pattern,
// where . symbol is treated as a wildcard character.
Bag<std::string> myTrieSET::keysThatMatch(const std::string& pattern) {
	Bag<std::string> results;
	std::string prefix;
	collect(root_, prefix, pattern, results);
	return results;
}

// Helper function for keysThatMatch
void myTrieSET::collect(Node* x, std::string& prefix, const std::string& pattern, Bag<std::string>& results) {
	if (x == NULL) return;
	int d = prefix.size();
	if (d == pattern.size() && x->isString_)
		results.add(prefix);
	if (d == pattern.size())
		return;
	char c = pattern[d];
	if (c == '.') {
		for (char ch = 0 + 'A'; ch < R_ + 'A'; ch++) {
			prefix += ch;
			collect(x->next_[CHAR_TO_INDEX(ch)], prefix, pattern, results);
			prefix.pop_back();
		}
	}
	else {
		prefix += c;
		collect(x->next_[CHAR_TO_INDEX(c)], prefix, pattern, results);
		prefix.pop_back();
	}
}

// Removes the key from the set if the key is present
void myTrieSET::deleteKey(std::string& key) {
	root_ = deleteKey(root_, key, 0);
}

// Helper function for deleteKey
myTrieSET::Node* myTrieSET::deleteKey(Node* x, std::string key, int d) {
	if (x == NULL) return NULL;
	if (d == key.size()) {
		if (x->isString_) N_--;
		x->isString_ = false;
	}
	else {
		char c = key[d];
		x->next_[CHAR_TO_INDEX(c)] = deleteKey(x->next_[CHAR_TO_INDEX(c)], key, d + 1);
	}

	// remove subtrie rooted at x if it is completely empty
	if (x->isString_) return x;
	for (int c = 0 + 'A'; c < R_ + 'A'; c++) {
		if (x->next_[CHAR_TO_INDEX(c)] != NULL)
			return x;
	}
	return NULL;
}

// My method definitions

// Is the node where the current pointer is pointing a string?
bool myTrieSET::isCurrentString() {
	if (current_ == NULL) return false;
	return current_->isString_;
}

// Are there any valid words that start with prefix?
bool myTrieSET::isPrefix(const std::string& prefix) {
	current_ = get(root_, prefix, 0);
	return (current_ != NULL);
}

// Clears trie
void myTrieSET::clearTrie() {
	if (root_ != NULL)
		destroy(root_);
	root_ = NULL;
}

// Destroy trie at Node x
void myTrieSET::destroy(Node* x) {
	for (int c = 0 + 'A'; c < R_ + 'A'; c++) {
		if (x->next_[CHAR_TO_INDEX(c)] != NULL)
			destroy(x->next_[CHAR_TO_INDEX(c)]);
	}
	delete x;
}

// Attempt at iterators
typedef Bag<std::string>::Iterator TrieIterator;
TrieIterator myTrieSET::begin() {
	return keysThatMatch("").begin();
}

TrieIterator myTrieSET::end() {
	return NULL;
}