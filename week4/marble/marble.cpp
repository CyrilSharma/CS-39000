/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Child First Tree Traversal.
 * The error in marbles can be determined by 1 - num_marbles.
 * If the error is positive, you have too few marbles, if it's negative you have too many.
 * If we add the total error for the children of a node, and compare it to the number of marbles
 * in the node, we can see whether the node itself has too many, or too few marbles.
 * Thus, solve the error for all the children then parents until you have all the errors.
 * Each marble of error will always require exactly one marble move to fix (regardless of sign)
 * Thus, we add the absolute value of all the errors to get the total number of marbles to move.
 * Also, they don't specify the root of the tree, so in order to explore the tree children first,
 * we must calculate the root (just keeping going to your parent until their is no parent).
 * @date 2022-09-24
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    using vi = vector<int>;
    using vvi = vector<vector<int>>;
    int n, v, m, d, c;
    string s;
    cin >> n;
    while (n != 0) {
        getline(cin, s);
        vvi tree; vi marb; vi parent(n, -1);
        v = -1;
        // FIND THE ROOT.
        while (v != n) {
            getline(cin, s);
            stringstream iss(s);
            iss >> v >> m >> d;
            tree.push_back(vi());
            marb.push_back(m);
            for (int i = 0; i < d; i++) {
                iss >> c;
                tree[v-1].push_back(c-1);
                parent[c-1] = v-1;
            }
        }
        int root = 0;
        while (parent[root] != -1) root = parent[root];

        int total = 0;
        function<int(int)> dfs;
        dfs = [&](int node) {
            if (tree[node].size() == 0) {
                total += abs(1-marb[node]);
                return 1-marb[node];
            }
            // cost of giving all children marbles.
            int sum = 0;
            for (int i = 0; i < tree[node].size(); i++) {
                sum += dfs(tree[node][i]);
            }
            total += abs(1 - (marb[node] - sum));
            return 1 - (marb[node] - sum);
        };
        dfs(root);
        cout << total << "\n";
        cin >> n;
    }
}