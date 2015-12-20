#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

class BearSong {
    public:
    int countRareNotes(vector<int> notes) {
        unordered_map<int, int> foo;
        int count = 0;
        for (int i = 0; i < notes.size(); i++)
        {
            if (foo.find(notes[i]) == foo.end())
            {
                pair<int, int> item(notes[i], 1);
                foo.insert(item);
            }
            else
            {
                foo.at(notes[i])++;
            }
        }

        for (auto it = foo.begin(); it != foo.end(); ++it)
        {
            if (it->second == 1)
            {
                count++;
            }
        }
        return count;
    }
};
