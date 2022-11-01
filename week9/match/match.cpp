#include <bits/stdc++.h>
using namespace std;

vector<int> prefix(string s) {
    int n = s.size();
    vector<int> f(n);
    for (int i = 1; i < n; i++) {
        int j = f[i-1];
        while (s[j] != s[i] && j > 0) {
            j = f[j-1];
        }
        if (s[j] == s[i]) f[i] = j+1;
    }
    return f;
}

int main() {
    string p, t;
    while (getline(cin, p)) {
        getline(cin, t);
        vector<int> f = prefix(p + "#" + t);
        for (int i = 0; i < f.size(); i++) {
            if (f[i] == p.size()) cout << i-2*p.size() << " ";
        }
        cout << "\n";
    }
}