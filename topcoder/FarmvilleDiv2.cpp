#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FarmvilleDiv2 {
    public:
    int minTime(vector<int> time, vector<int> cost, int budget) {
        int n = cost.size();
        int count = 0;
        vector<pair<int, int> > vp;
        for(int i = 0; i < n; i++) {
            vp.push_back(make_pair(cost[i], time[i]));
        }
        sort(vp.begin(), vp.end());
        for(int i = 0; i < n; i++)
        {
            if (vp[i].first <= budget)
            {
                if (vp[i].second > (budget/vp[i].first))
                {
                    vp[i].second -= (budget/vp[i].first);
                    budget %= vp[i].first;
                }
                else if (vp[i].second > 0)
                {
                    budget -= (vp[i].first * vp[i].second);
                    vp[i].second = 0;
                }
            }
            count += vp[i].second;
        }
        return count;
    }
};
