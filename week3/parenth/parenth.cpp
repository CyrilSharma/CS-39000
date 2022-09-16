// Author: Cyril Sharma
// It is ok to post my anonymized solution

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;

#define maxVal 1e9
int compute(int n1, int n2, char c) {
    if (c == '+') return n1 + n2;
    if (c == '*') return n1 * n2;
    if (c == '-') return n1 - n2;
    return maxVal;
}


set<int> dfs(int start, int stop, vi nums, vc ops) {
    set<int> s;
    // if there is only one item, return that item.
    if (stop - start == 0) {
        s.insert(nums[start]);
        return s;
    }

    int res;
    for (int i = start; i < stop; i++) {
        // The core idea is to split the equation into two pieces:
        // All the results possible using symbols start to i
        // All the results possible using symbols i+1 to stop.
        // then use whatever operator joins the two halves to combine the two intervals.
        // These subcomputations essentially act as parenthesis, 
        // they allow computing any operation before any other.
        // How do I analyze complexity?
        set<int> r1 = dfs(start, i, nums, ops); 
        set<int> r2 = dfs(i+1, stop, nums, ops);
        for (int a: r1) {
            for (int b: r2) {
                res = compute(a, b, ops[i]);
                s.insert(res);
            }
        }
    }
    return s;
}



int main() {
    string s;
    while (getline(cin, s)) {
        stringstream iss(s);
        vi nums; vc ops; int x; char op;
        // read in equation into line
        while (iss >> x) {
            // read number, op alternating
            nums.push_back(x);
            if (iss >> op) 
                ops.push_back(op);
        }
        // find all values.
        set<int> results = dfs(0, nums.size()-1, nums, ops);
        for (int res: results) cout << res << "\n";
        cout << "\n";
    }
}