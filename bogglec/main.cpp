#include "BoggleSolver.h"
#include "BoggleBoard.h"
#include "myTrieSET.h"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
// #include "vld.h"

// Unit test for myTrieSET
int TrieTest() {
	/*std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> distribution(0, 1);
	for (int i = 0; i < 10; i++)
		std::cout << distribution(mt) << " ";
	std::cout << std::endl;*/

	myTrieSET set;
	std::string in = "";
	std::cout << "Enter strings: " << std::endl;
	while (in != "stop") {
		std::cin >> in;
		set.add(in);
	}

	// print results
	if (set.size() < 100) {
		std::cout << "keys: ";
		for (std::string key : set) {
			std::cout << key << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "longestPrefixOf shellsort:" << std::endl;
	std::cout << set.longestPrefixOf("shellsort") << std::endl;
	std::cout << std::endl;

	std::cout << "longestPrefixOf xshellsort:" << std::endl;
	std::cout << set.longestPrefixOf("xshellsort") << std::endl;
	std::cout << std::endl;

	std::cout << "keysWithPrefix shor:" << std::endl;
	for (std::string s : set.keysWithPrefix("shor"))
		std::cout << s << std::endl;
	std::cout << std::endl;

	std::cout << "keysWithPrefix shortening:" << std::endl;
	for (std::string s : set.keysWithPrefix("shortening"))
		std::cout << s << std::endl;
	std::cout << std::endl;

	std::cout << "keysThatMatch .he.l.:" << std::endl;
	for (std::string s : set.keysThatMatch(".he.l."))
		std::cout << s << std::endl;

	return 0;
}

// Another tester for myTrieSET
int myTrieTest() {

	// Read words from file into string vector
	std::ifstream inFile;
	inFile.open("dictionary-algs4.txt");
	std::string line;
	std::vector<std::string> words;
	while (std::getline(inFile, line)) {
		words.push_back(line);
	}

	// Enter words into Trie
	myTrieSET dictionary;
	for (auto& i : words)
		dictionary.add(i);

	std::string ends("ENDS");
	std::cout << "Contains ENDS " << dictionary.contains(ends) << std::endl;

	dictionary.deleteKey(ends);
	std::cout << "Contains ENDS " << dictionary.contains(ends) << std::endl;

	std::string able("SORT");
	std::cout << "Keys that match " << able << std::endl;
	for (auto& i : dictionary.keysThatMatch(able))
		std::cout << i << std::endl;

	std::string abso("SORT");
	std::cout << "Keys that contain " << abso << std::endl;
	for (auto& i : dictionary.keysWithPrefix(abso))
		std::cout << i << std::endl;

	std::string shell("SHELLSORT");
	std::cout << "Longest prefix of " << shell << std::endl;
	std::cout << dictionary.longestPrefixOf(shell) << std::endl;

	return 0;
}

// Tester for BoggleSolver
int main() {
	std::string dictionaryFile;
	std::cout << "Enter dictionary file: ";
	std::cin >> dictionaryFile;

	// Create dictionary trie
	std::ios::sync_with_stdio(false);
	std::ifstream inFile;
	inFile.open(dictionaryFile);
	std::string line;
	std::vector<std::string> dictionary;
	while (std::getline(inFile, line)) {
		dictionary.push_back(line);
	}
	BoggleSolver solver(dictionary);

	// Solve board
	std::string boardFile;
	std::cout << "Enter board file: ";
	std::cin >> boardFile;
	while (boardFile != "quit") {
		BoggleBoard board(boardFile);
		std::cout << board << std::endl;
		int score = 0;
		for (std::string word : solver.getAllValidWords(board)) {
			std::cout << word << std::endl;
			score += solver.scoreOf(word);
		}
		std::cout << "Score: " << score << std::endl;
		std::cout << "Enter next board (quit to exit): ";
		std::cin >> boardFile;
	}
	return 0;
}
