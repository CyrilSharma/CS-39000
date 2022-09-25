/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Greedy + Child First Tree Traversal.
 * The first step to solving this is to realize that the more skilled the player, the more games they should
 * play to maximize the total appeal. 
 * This allows us to make a greedy algorithm, find the longest streak of games the best player can win, 
 * multiply the length of the streak with the players skill to get the total amount of appeal he
 * contributes.
 * Then find the longest streak the second best player can win (knowing the best streak the first player
 * can win), rinse and repeat.
 * To make this efficient, we dynamically compute the path length for each leaf.
 * Essentially, each streak is associated with a particular player or leaf. Since better players get assigned
 * to longer streaks, each node (or game) will choose whatever player has the longest streak. 
 * Once we have the streak lengths, we multiply the largest streak lengths with the largest skill
 * values, and sum to get our answer.
 * @date 2022-09-24
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, p;
    cin >> n >> k;
    using vi = vector<int>;
    using vvi = vector<vi>;
    using ll = long long;
    vi skills(k); vvi child(n);
    for (int i = 0; i < k; i++) {
        cin >> skills[i];
    }
    sort(skills.begin(), skills.end());
    for (int i = 1; i <= n-1; i++) {
        cin >> p;
        child[p].push_back(i);
    }

    vi nume(k);
    int childid = 0;
    pair<int,int> ret;
    function<pair<int,int>(int)> calc;
    calc = [&](int node) {
        if (child[node].size() == 0) {
            ret = {childid, 1};
            nume[childid]++; 
            childid++;
            return ret;
        }
        int bigi = -1; int big = -1;
        for (int i = 0; i < child[node].size(); i++) {
            auto [id, edges] = calc(child[node][i]);
            if (edges > big) {
                bigi = id;
                big = edges;
            }
        }
        if (node != 0) nume[bigi]++;
        return make_pair(bigi, big+1);
    };
    calc(0);
    sort(nume.begin(), nume.end());

    ll total = 0;
    for (int i = 0; i < k; i++) {
        total += (ll)nume[i] * (ll)skills[i];
    }
    cout << total << "\n";
}