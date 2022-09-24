/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @date 2022-09-23
 * @brief There are two possible ways to pay for your nth vacation
 * 1. Buy a single ticket - cost is the minimum cost of the n-1th vacation + ticket price
 * 2. Have your costs covered by a period ticket
 *  - For each trip, add the date to which the period ticket (if you bought it then) would expire.
 *  - Also add the total cost of the path up to the ticket.
 *  - If the cost of your path is cheaper then what's in the queue, remove what's in the queue.
 *  - Thus, you only need to check the first element of the queue to determine the cheapest path from a     *  - period ticket.
 * 3. Repeat these steps until you reach the nth vacation.
 */
#include <bits/stdc++.h>
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