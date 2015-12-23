#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class BearCheats {
    public:
    static string eyesight(int A, int B) {
        int A_copy = A;
        int B_copy = B;
        int a_digit, b_digit;
        int count = 0;
        while (A_copy > 0) {
           a_digit = A_copy % 10;
           b_digit = B_copy % 10;
           if (a_digit != b_digit) count++;

           if (count > 1) return "glasses";
           A_copy /= 10;
           B_copy /= 10;
        }
        return "happy";
    }
};
