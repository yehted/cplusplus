#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class BearSlowlySorts {
    public:
    int minMoves(vector<int> w) {
        vector<int> foo = w;
        int n = w.size();
        sort(foo.begin(), foo.end());
        int w_min = foo[0];
        int w_max = foo[n-1];

        if (w[0] == w_min || w[n-1] == w_max)
        {
            if (w == foo) return 0;
            else return 1;
        }
        else if (w[0] < w[n-1])
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
};
