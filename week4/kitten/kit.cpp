/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Simply go to the parent of the current node until you reach the root.
 * @date 2022-09-24
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<int> graph(100, -1);
    int a, k, b, cur;
    cin >> k >> a;
    string s;  
    while (a != -1) {
        getline(cin, s);
        stringstream iss(s);
        while (iss >> b) {
            graph[b] = a;
        }
        cin >> a;
    }
    cur = k;
    while (graph[cur] != -1) {
        cout << cur << " ";
        cur = graph[cur];
    }
    cout << cur << "\n";
}