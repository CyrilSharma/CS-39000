/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution
 * @date 2022-09-23
 * @brief This a standard knapsack problem.
 * Knapsack problems consist of trying to get the highest value sack with a bunch of nodes.
 * Each node has some cost, and some value. In this case, the cost is the number of voters to persuade,
 * the value is the number of electors we get in exchange.
 * Since we can only use each node (i.e a state) once, we iterate backwards over the array, 
 * ensuring paths cannot be made by stacking the same node.
 * Then, we find the minimum cost path that gets us at least half the electors.
 */
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> ndel(2017, 2e9);
    ndel[0] = 0;

    int tdel = 0;
    int s; cin >> s;
    while (s--) {
        int d, c, f, u;
        cin >> d >> c >> f >> u;
        tdel += d;
        int tot = f + u + c;
        int cost = (tot / 2) - c + 1;
        if (cost > u) continue;
        if (cost < 0) cost = 0;
        for (int i = ndel.size()-1; i >= d; i--) {
            if (ndel[i-d] == 2e9) continue;
            ndel[i] = min(ndel[i], ndel[i-d] + cost);
        }
    }

    int best = 2e9;
    for (int i = (tdel/2)+1; i < ndel.size(); i++) {
        best = min(best, ndel[i]);
    }
    if (best == 2e9) cout << "impossible\n";
    else cout << best << "\n";
}