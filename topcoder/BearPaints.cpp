#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BearPaints {
    public:
    static long long maxArea(int W, int H, long long M) {
        long long area = 0;
        long long j;
        for(int i = 1; i <= W; i++)
        {
            j = min(M/i, (long long) H);
            area = max(area, i * j);
        }
        return area;
    }
};

