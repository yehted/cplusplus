#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BearPaints {
    public:
    long maxArea(int W, int H, long M) {
        long biggest = 0;
        for(int i = W; i >= 0; i--)
        {
            for(int j = H; j >= 0; j--)
            {
                long big = long(i) * j;
                if (big <= M)
                {
                    if (big > biggest) biggest = big;
                    if (big < biggest) return biggest;
                }
            }
        }
        return biggest;
    }
};
