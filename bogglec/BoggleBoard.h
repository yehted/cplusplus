#pragma once	// better alternative to #ifndef...
#include <string>
#include <vector>
#include <myRandom.h>

class BoggleBoard
{
public:
	BoggleBoard();
	~BoggleBoard();
	BoggleBoard(std::string filename);
	BoggleBoard(int M, int N);
	BoggleBoard(char** a, int M, int N);
	int rows() const;
	int cols() const;
	char getLetter(int i, int j) const;
	friend std::ostream& operator<<(std::ostream& output, const BoggleBoard& board);

private:
	int M_;		// number of rows
	int N_;		// number of columns
	char** board_;	// M-by-N vector of characters

	static std::vector<std::string> boggle1992;
	static std::vector<std::string> boggle1983;
	static std::vector<std::string> boggleMaster;
	static std::vector<std::string> boggleBig;
	const static std::string alphabet;
	const static std::vector<double> frequencies;

	void shuffle(std::vector<std::string> a);
};

