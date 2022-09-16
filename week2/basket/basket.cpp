// Author: Cyril Sharma
// It is ok to post my anonymized solution

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;
typedef long long ll;

int n;

int dfs(int depth, int d, int prev, int weight, vector<ll> fruits) {
    int total = 0;
    if (weight >= 200) return 0;
    if (depth == d) return weight;
    // prev is the index of the previously chosen fruit.
    // start at prev+1 to ensure you choose a unique fruit.
    for (int i = prev+1; i < n; i++) {
        weight += fruits[i];
        total += dfs(depth, d+1, i, weight, fruits);
        weight -= fruits[i];
    }
    return total;
}

int main() {
    cin >> n;
    vector<ll> fruits(n);
    // each item can either be included or excluded -> 2^n total baskets.
    ll nbask = (ll) pow((double)2, (double)(n));
    ll tweight = 0;
    for (int i = 0; i < n; i++) {
        cin >> fruits[i];
        // in half of the total baskets an item is included, thus 1/2 * nback * weight 
        // summed for all the fruits is the total weight of all baskets.
        tweight += nbask/2 * fruits[i];
    }

    ll sweight = 0;
    // compute the weight of baskets with weight < 200 using 1,2,3 and 4 fruit.
    // each fruit weight >=50 hence, we only need to check how many invalid baskets exist up to 4.
    for (int i = 1; i <= 4; i++) {
        sweight += dfs(i, 0, -1, 0, fruits);
    }
    // the answer is the total number of baskets minus the number of invalid baskets.
    cout << tweight - sweight << "\n";
}