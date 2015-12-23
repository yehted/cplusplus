#include "BearPaints.cpp"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Missing arguments" << endl;
    }
    istringstream ss(argv[1]);
    int W;
    if (!(ss >> W)) {
        cerr << "Invalid number " << argv[1] << endl;
    }
    istringstream st(argv[2]);
    int H;
    if (!(st >> H)) {
        cerr << "Invalid number " << argv[2] << endl;
    }
    istringstream su(argv[3]);
    long long M;
    if (!(su >> M)) {
        cerr << "Invalid number " << argv[3] << endl;
    }

    long long maxArea = BearPaints::maxArea(W, H, M);
    cout << maxArea << endl;
}

