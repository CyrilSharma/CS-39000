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

vector<int> results;
int i = 0;
void dfs(int res, vi nums, vc ops) {
    i++;
    if (ops.size() == 0) {
        results.push_back(res);
        return;
    }

    for (int i = 0; i < ops.size(); i++) {
        vc nops(ops); vi nnums(nums);
        int res = compute(nums[i], nums[i+1], ops[i]);
        nnums[i] = res; nnums.erase(nnums.begin() + i+1);
        nops.erase(nops.begin() + i);
        dfs(res, nnums, nops);
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
        dfs(0, nums, ops);
        sort(results.begin(), results.end());
        for (int i = 0; i < results.size(); i++) {
            if (i == 0 || results[i] != results[i-1])
                cout << results[i] << "\n";
        }
        cout << i << "\n";
        cout << "\n";
    }
}