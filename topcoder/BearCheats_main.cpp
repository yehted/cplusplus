#include "BearCheats.cpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    istringstream sa(argv[1]);
    int a;
    if (!(sa >> a)) cerr << "Invalid number " << argv[1] << endl;

    istringstream sb(argv[2]);
    int b;
    if (!(sb >> b)) cerr << "Invalid number " << argv[2] << endl;

    string result = BearCheats::eyesight(a, b);
    cout << result << endl;
}
