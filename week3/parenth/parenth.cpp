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

set<int> results;
void dfs(int flags, int index, vi nums, vc ops) {
    i++;
    /* cout << "flags: ";
    for (int i = 0; i < ops.size(); i++) {
        if (flags & (1<<i)) cout << "1";
        else cout << "0";
    }
    cout << "\n"; */
    // apply parenthesis
    vc nops(ops); vi nnums(nums);
    for (int i = nops.size()-1; i >= 0; i--) {
        if (!(flags&(1<<i))) continue;
        int res = compute(nnums[i], nnums[i+1], nops[i]);
        nnums[i] = res; 
        nnums.erase(nnums.begin() + i+1);
        nops.erase(nops.begin() + i);
    }

    // compute
    int res = nnums[0];
    for (int i = 0; i < nops.size(); i++) {
        cout << res << " " << nops[i] << " " << nnums[i+1] << " -> ";
        res = compute(res, nnums[i+1], nops[i]);
    }
    cout << res << "\n";
    results.insert(res);

    for (int i = index+1; i < ops.size(); i++) {
        int nflags = flags;
        int b = 1 << i;
        // turn ith bit on.
        nflags |= b;
        dfs(nflags, i, nums, ops);
    }
}



int main() {
    string s;
    while (getline(cin, s)) {
        stringstream iss(s);
        vi nums; vc ops; int x; char op;
        while (iss >> x) {
            nums.push_back(x);
            if (iss >> op) 
                ops.push_back(op);
        }
        results.clear();
        dfs(0, -1, nums, ops);
        for (int res: results) cout << res << "\n";
        cout << "\n";
    }
}