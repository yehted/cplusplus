#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class SetPartialOrder {
    public:
    string compareSets(vector<int> a, vector<int> b) {
        set<int> foo(a.begin(), a.end());
        set<int> bar(b.begin(), b.end());

        if (foo == bar) return "EQUAL";
        if (foo.size() < bar.size())
        {
            for (auto it = foo.begin(); it != foo.end(); ++it)
            {
                if (bar.find(*it) == bar.end())
                {
                    return "INCOMPARABLE";
                }
            }
            return "LESS";
        }
        else
        {
            for (auto it = bar.begin(); it != bar.end(); ++it)
            {
                if (foo.find(*it) == foo.end())
                {
                    return "INCOMPARABLE";
                }
            }
            return "GREATER";
        }
    }
};
