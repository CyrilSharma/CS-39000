/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Topological Traversal.
 * The tricky part of this problem is working with the data.
 * I used maps to allow me to make a graph directly on the page numbers.
 * Then, I performed a topological traversal of the tree starting from the end nodes
 * Denoted with pages -1, 0. 
 * The number of ways to reach a node is the sum of the number of ways the children
 * of the node can be reached.
 * @date 2022-10-21
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    using ll = long long;
    int t; cin >> t;
    for (int it = 0; it < t; it++) {
        int s; cin >> s;
        string line;
        getline(cin, line);
        map<int,vector<int>> children, parent;
        for (int i = 0; i < s; i++) {
            getline(cin, line);
            stringstream ss1(line);
            int p1, p2, p3, p4;
            if (ss1 >> p1 >> p2 >> p3 >> p4) {
                children[p1] = {p2,p3,p4};
            } else {
                stringstream ss2(line);
                string outcome;
                ss2 >> p1 >> outcome;
                if (outcome == "favourably") children[p1] = {0};
                else children[p1] = {-1};
            }
        }

        for (auto const& [key, val]: children) {
            for (auto child: val) {
                parent[child].push_back(key);
            }
        }

        map<int,ll> paths;
        map<int,int> updates;
        queue<int> q;
        paths[0] = 1; q.push(0); q.push(-1);
        while (q.size() != 0) {
            int node = q.front(); q.pop();
            for (auto parent: parent[node]) {
                updates[parent]++;
                paths[parent] += paths[node];
                if ((int)children[parent].size() != updates[parent]) continue;
                q.push(parent);
            }
        }
        cout << paths[1] << "\n";
    }
}