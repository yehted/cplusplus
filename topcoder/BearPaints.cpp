#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BearPaints {
    public:
    long long maxArea(int W, int H, long long M) {
        int smaller_side = min(W, H);
        int bigger_side = max(W, H);
        long long area = smaller_side * smaller_side;
        if (area < M)
        {
            long long remaining = M - area;
            long long additional = remaining / smaller_side;
            area += (additional * smaller_side);
            return area;
        }
        int i = smaller_side;
        while (i*i > M)
        {
            i--;
        }
        area = i * i;
        long long remaining = M - area;
        long long additional = remaining / i;
        area += additional;
        return area;
    }
};
