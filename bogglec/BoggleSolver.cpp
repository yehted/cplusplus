#include "BoggleSolver.h"


BoggleSolver::BoggleSolver() {

}


BoggleSolver::~BoggleSolver() {
	
}

// Initializes the data structure using the given array of strings as the dictionary.
// (You can assume each word in the dictionary contains only the uppercase letters A through Z.)
BoggleSolver::BoggleSolver(std::vector<std::string>& dictionary) {
	for (auto& i : dictionary)
		tree_.add(i);
}

// Returns the set of all valid words in the given Boggle board, as an Iterable
Queue<std::string> BoggleSolver::getAllValidWords(BoggleBoard& board) {
	board_ = &board;

	// Clear any previous board answers.
	validWords_.clearTrie();
	validQueue_.clear();

	// Cache board dimensions
	M_ = board.rows();
	N_ = board.cols();

	// Create marked matrix
	marked_ = new bool*[M_];
	for (int i = 0; i < M_; i++)
		marked_[i] = new bool[N_]();

	for (int i = 0; i < M_; i++) {
		for (int j = 0; j < N_; j++) {
			std::string word;
			word.reserve(M_ * N_ + 1);
			word += board_->getLetter(i, j);

			if (word == "Q")
				word += 'U';

			if (!tree_.isPrefix(word)) continue;
			dfs(i, j, word);
		}
	}

	// Clean up marked_ memory
	for (int i = 0; i < M_; i++)
		delete[] marked_[i];
	delete[] marked_;

	//return validWords_;
	return validQueue_;
}

void BoggleSolver::dfs(int x, int y, std::string& prefix) {
	// Checks if letter at position (x, y) has been visited.
	if (marked_[x][y]) return;
	
	marked_[x][y] = true;
	for (int i = -1; i <= 1; i++) {
		// Continue if out of bounds
		if (x + i < 0 || x + i >= M_) continue;
		
		for (int j = -1; j <= 1; j++) {
			// Continue if out of bounds
			if (y + j < 0 || y + j >= N_) continue;
			
			// Continue if letter at x + i, y + j is already used
			if (marked_[x + i][y + j]) continue;
			
			prefix.push_back(board_->getLetter(x + i, y + j));
			bool q(false);

			if (prefix.back() == 'Q') {
				prefix += 'U';
				q = true;
			}

			// Stops further path exploration if prefix is not part of any word
			if (!tree_.isPrefix(prefix)) {
				if (q) prefix.pop_back();					
				prefix.pop_back();
				continue;
			}

			if (prefix.length() > 2) { 
				if (tree_.isCurrentString()) {
					if (!validWords_.contains(prefix)) {
						validWords_.add(prefix);
						validQueue_.enqueue(prefix);
					}
				}
			}

			dfs(x + i, y + j, prefix);
			if (q) prefix.pop_back();
			prefix.pop_back();			
		}
	}
	marked_[x][y] = false;
}

int BoggleSolver::scoreOf(std::string word) {
	if (!tree_.contains(word)) return 0;
	int L = word.length();
	if (L <= 2) return 0;
	if (L <= 4) return 1;
	if (L <= 5) return 2;
	if (L <= 6) return 3;
	if (L <= 7) return 5;
	return 11;
}