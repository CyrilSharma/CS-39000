#include <vector>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int s,p,m,n;
    cin >> s >> p >> m >> n;
    using ll = long long;
    using vll = vector<ll>;

    vll mincost(n+1,0);
    queue<pair<int,ll>> cover;
    cover.push({m-1, 0});
    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        mincost[i] = mincost[i-1] + s;
        ll arrival = mincost[i-1];
        if (cover.size() != 0) {
            auto [end, cost] = cover.front();
            while ((mincost[i] <= cost || end < t) && cover.size() != 0) {
                cover.pop();
                tie(end, cost) = cover.front();
            }
            if (end >= t) {
                mincost[i] = min(mincost[i], cost + p);
                arrival = min(arrival, cost + p);
            }
        }
        cover.push({t+m-1, arrival});
    }
    cout << mincost[n] << "\n";
}