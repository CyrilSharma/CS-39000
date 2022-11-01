#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> dp(n+1), pd(n+1);
    for (int i=0; i<n; i++) {
        int a; cin >> a;
        dp[a] = i;
    }
    for (int i=0; i<n; i++) {
        int a; cin >> a;
        pd[a] = i;
    }

    vector<vector<int>> endpoints(n, vector<int>());
    for (int i = 1; i <= n; i++) {
        int end = max(dp[i], pd[i]);
        int begin = min(dp[i], pd[i]);
        endpoints[end].push_back(begin);
    }

    vector<int> ssq(n);
    ssq[0] = endpoints[0].size() ? 1 : 0;
    for (int i = 1; i < n; i++) {
        ssq[i] = ssq[i-1];
        for (auto start: endpoints[i]) {
            ssq[i] = max({ssq[i], ssq[i-1], ssq[start]+1});
        }
        cout << "i: " << i << " | " << ssq[i] << "\n";
    }
    cout << "2 " << ssq[n-1]+1 << "\n";
}