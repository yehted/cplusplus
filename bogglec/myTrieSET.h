/*********************************************************************************
 * The TrieSET class represents an ordered set of strings over the
 * extended ASCII alphabet.
 * It supports the usual add, contains, and delete methods. It also provides
 * character-based methods for finding the string in the set that is the
 * longest prefix of a given prefix, finding all astrings in the set that
 * start with a given prefix, and finding all strings in the set that match
 * a given pattern.
 *
 * This implementation uses a 26-way trie. (The base class from which this
 * was derived uses a 256-way trie.)
 *
 * The add, contains, delete, and longest prefix methods take time proportional
 * to the length of the key (in the worst case). Construction takes constant time.
 *
 * For additional documentation, see http://algs4.cs.princeton.edu/52trie
 * Section 5.2 of Algorithms in Java, 4th Edition,
 * by Robert Sedgewick and Kevin Wayne
 ********************************************************************************/

#pragma once
#include <string>
#include <Bag.h>
#include <vector>
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')

class myTrieSET {

public:
	myTrieSET();								// Initializes an empty set of strings
	~myTrieSET();								// Destroys trie
	bool contains(std::string& key);			// Does the set contain the given key?
	void add(std::string& key);					// Adds the key to the set if it is not already present.
	int size();									// Returns the number of strings in the set.
	bool isEmpty();								// Is the set empty?
	Bag<std::string> keysWithPrefix(const std::string& prefix);	// Returns all of the keys in the set that start with prefix.
	std::string longestPrefixOf(const std::string& query);		// Returns the string in the set that is the longest prefix of query or null if no such string.
	Bag<std::string> keysThatMatch(const std::string& pattern);	// Returns all of the keys in the set that match pattern.
	void deleteKey(std::string& key);			// Removes the key from the set if the key is present

	// My method definitions
	bool isCurrentString();						// Is the node where the current pointer is pointing a string?
	bool isPrefix(const std::string& prefix);	// Are there any valid words that start with prefix?
	void clearTrie();							// Clears trie

	// Attempt at iterators
	typedef Bag<std::string>::Iterator TrieIterator;
	TrieIterator begin();
	TrieIterator end();

private:
	const static int R_ = 26;	// uppercase alphabet

	// R-way trie node
	struct Node {
		// default initializes to NULL
		Node() : isString_(false), next_() {}

		bool isString_;
		Node* next_[R_];
	};

	Node* root_;				// root of trie
	int N_;						// number of keys in trie
	Node* current_;				// current node

	// Helper functions
	Node* get(Node* x, const std::string& key, int d);		// Helper function for contains()
	Node* add(Node* x, std::string& key, int d);			// Helper function for add()
	void collect(Node* x, std::string prefix, Bag<std::string>& results);	// Helper function for keysWithPrefix
	void collect(Node* x, std::string& prefix, const std::string& pattern, Bag<std::string>& results);	// Helper function for keysThatMatch
	int longestPrefixOf(Node* x, std::string query, int d, int length);	// Helper function for longestPrefixOf
	Node* deleteKey(Node* x, std::string key, int d);		// Helper function for deleteKey
	void destroy(Node* x);									// Destroy trie at Node x
};
