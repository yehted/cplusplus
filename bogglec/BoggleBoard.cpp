#include "BoggleBoard.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#define FOR(i, N) for (int i = 0; i < N; i++)

std::vector<std::string> BoggleBoard::boggle1992 = {
	"LRYTTE", "VTHRWE", "EGHWNE", "SEOTIS",
	"ANAEEG", "IDSYTT", "OATTOW", "MTOICU",
	"AFPKFS", "XLDERI", "HCPOAS", "ENSIEU",
	"YLDEVR", "ZNRNHL", "NMIQHU", "OBBAOJ"
};

std::vector<std::string> BoggleBoard::boggle1983 = {
	"AACIOT", "ABILTY", "ABJMOQ", "ACDEMP",
	"ACELRS", "ADENVZ", "AHMORS", "BIFORX",
	"DENOSW", "DKNOTU", "EEFHIY", "EGINTV",
	"EGKLUY", "EHINPS", "ELPSTU", "GILRUW",
};

std::vector<std::string> BoggleBoard::boggleMaster = {
	"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
	"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
	"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DHHLOR",
	"DHHNOT", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
	"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

std::vector<std::string> boggleBig = {
	"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
	"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCENST",
	"CEIILT", "CEILPT", "CEIPST", "DDHNOT", "DHHLOR",
	"DHLNOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
	"FIPRSY", "GORRVW", "IPRRRY", "NOOTUW", "OOOTTU"
};

const std::string BoggleBoard::alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::vector<double> BoggleBoard::frequencies = {
	0.08167, 0.01492, 0.02782, 0.04253, 0.12703, 0.02228,
	0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
	0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
	0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
	0.01974, 0.00074
};

// Initializes a random 4-by-4 board, by rolling the Hasbro dice
BoggleBoard::BoggleBoard() {
	M_ = 4;
	N_ = 4;
	shuffle(boggle1992);
	board_ = new char*[M_];
	FOR(i, M_)
		board_[i] = new char[N_];

	FOR(i, M_) {
		FOR(j, N_) {
			std::string letters = boggle1992[N_ * i + j];
			int r = myRandom::uniform(letters.size());
			board_[i][j] = letters[r];
		}
	}
}


BoggleBoard::~BoggleBoard() {
	FOR(i, M_)
		delete[] board_[i];
	delete[] board_;
}

// Initializes a board from the given filename.
BoggleBoard::BoggleBoard(std::string filename) {
	std::ifstream inFile;
	inFile.open(filename);
	if (!inFile.is_open()) throw std::invalid_argument("File not opened");
	inFile >> M_;
	inFile >> N_;
	board_ = new char*[M_];
	FOR(i, M_)
		board_[i] = new char[N_];

	std::string letter;
	FOR(i, M_) {
		FOR(j, N_) {
			inFile >> letter;
			if (letter == "Qu")
				board_[i][j] = 'Q';
			else if (letter.size() != 1)
				throw std::invalid_argument("invalid character");
			else if (alphabet.find(letter) == std::string::npos)
				throw std::invalid_argument("invalid character");
			else
				board_[i][j] = letter[0];
		}
	}
}

// Initializes a random M-by-N board, according to the frequency
// of letters in the English language.
BoggleBoard::BoggleBoard(int M, int N) : M_(M), N_(N) {
	board_ = new char*[M_];
	FOR(i, M_)
		board_[i] = new char[N_];

	FOR(i, M_) {
		FOR(j, N_) {
			int r = myRandom::discrete(frequencies);
			board_[i][j] = alphabet[r];
		}
	}
}

// Initializes a board from the given 2d character array,
// with 'Q' representing the two-letter sequence "Qu".
BoggleBoard::BoggleBoard(char** a, int M, int N) : M_(M), N_(N) {
	board_ = new char*[M];
	FOR(i, M)
		board_[i] = new char[N];
	FOR(i, M) {
		FOR(j, N) {
			if (alphabet.find(a[i][j]) == std::string::npos)
				throw std::invalid_argument("invalid character");
			board_[i][j] = a[i][j];
		}
	}
}

void BoggleBoard::shuffle(std::vector<std::string> a) {
	int N = a.size();
	FOR(i, N) {
		int r = i + myRandom::uniform(N - i);
		std::string temp = a[i];
		a[i] = a[r];
		a[r] = temp;
	}
}

int BoggleBoard::rows() const { return M_;  }

int BoggleBoard::cols() const { return N_; }

char BoggleBoard::getLetter(int i, int j) const {
	return board_[i][j];
}

std::ostream& operator<<(std::ostream& output, const BoggleBoard& board) {
	FOR(i, board.rows()) {
		FOR(j, board.cols()) {
			output.width(3);
			output << board.getLetter(i, j);
			if (board.getLetter(i, j) == 'Q')
				output << "u";
			else
				output << " ";
		}
		output << std::endl;
	}
	return output;
}

int boardTest() {
	using namespace std;

	// initialize a 4-by-4 board using Hasbro dice
	cout << "Hasbro board:" << endl;
	BoggleBoard board1;
	cout << board1 << endl;
	cout << endl;

	// initialize a 4-by-4 board using letter frequencies in English language
	cout << "Random 4-by-4 board:" << endl;
	BoggleBoard board2(4, 4);
	cout << board2 << endl;
	cout << endl;

	// initialize a 4-by-4 board from a 2d char array
	cout << "4-by-4 board from 2D character array:" << endl;
	char a[4][4] = {
		{ 'D', 'O', 'T', 'Y' },
		{ 'T', 'R', 'S', 'F' },
		{ 'M', 'X', 'M', 'O' },
		{ 'Z', 'A', 'B', 'W' }
	};
	char** b = new char*[4];
	FOR(i, 4)
		b[i] = new char[4];
	FOR(i, 4) {
		FOR(j, 4)
			b[i][j] = a[i][j];
	}
	BoggleBoard board3(b, 4, 4);
	cout << board3 << endl;
	cout << endl;

	// initialize a 4-by-4 board from a file
	std::string filename = "board-quinquevalencies.txt";
	cout << "4-by-4 board from file " << filename << ";" << endl;
	BoggleBoard board4(filename);
	cout << board4 << endl;
	cout << endl;
	return 0;
}
