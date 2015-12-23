#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Cdgame {
    public:
    static int rescount(vector<int> a, vector<int> b) {
        set<int> unique;
        int a_sum = 0;
        for(int i = 0; i < a.size(); i++) {
            a_sum += a[i];
        }
        int b_sum = 0;
        for(int j = 0; j < b.size(); j++) {
            b_sum += b[j];
        }

        int prod = 0;
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                int a_sum_copy = a_sum - a[i] + b[j];
                int b_sum_copy = b_sum - b[j] + a[i];
                prod = a_sum_copy * b_sum_copy;
                unique.insert(prod);
            }
        }
        return unique.size();
    }
};
