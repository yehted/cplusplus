#include "Cdgame.cpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    int len_a, len_b;
    cout << "Length of a: ";
    cin >> len_a;
    vector<int> a (len_a);
    for(int i = 0; i < len_a; i++) {
        cin >> a[i];
    }

    cout << "Length of b: ";
    cin >> len_b;
    vector<int> b (len_b);
    for(int j = 0; j < len_b; j++) {
        cin >> b[j];
    }

    int unique = Cdgame::rescount(a, b);
    cout << "Result: " << unique << endl;
    return 0;
}
