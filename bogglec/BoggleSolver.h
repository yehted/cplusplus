#pragma once
#include "BoggleBoard.h"
#include "myTrieSET.h"
#include <Queue.h>
#include <string>
#include <vector>

class BoggleSolver
{
public:
	BoggleSolver();
	~BoggleSolver();
	BoggleSolver(std::vector<std::string>& dictionary);
	Queue<std::string> getAllValidWords(BoggleBoard& board);
	int scoreOf(std::string word);

private:
	myTrieSET tree_;
	myTrieSET validWords_;
	Queue<std::string> validQueue_;
	BoggleBoard* board_;
	bool** marked_;
	int M_;
	int N_;

	void dfs(int x, int y, std::string& prefix);

};

