#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    int mod = ~(0 | 1<<31);
    using ll = long long;
    vector<vector<ll>> paths(n+1, vector<ll>(n+1, 0));
    if (board[0][0] != '#') paths[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i-1][j-1] == '#') continue;
            if (i == 1 && j == 1) continue;
            paths[i][j] = (paths[i-1][j] + paths[i][j-1]) % mod;
        }

    }
    if (paths[n][n] != 0) {
        cout << paths[n][n] << "\n";
        return 0;
    }
    vector<vector<int>> visited(n, vector<int>(n));
    queue<pair<int,int>> q;
    q.push({0,0});
    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, 1, 0, -1};
    while (q.size() != 0) {
        auto [y,x] = q.front(); q.pop();
        if (y == n-1 && x == n-1) {
            cout << "THE GAME IS A LIE\n";
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int ny = y+dy[i]; int nx = x+dx[i];
            if (ny < 0 | ny >= n | nx < 0 || nx >= n) continue;
            if (board[ny][nx] == '#') continue;
            if (visited[ny][nx] != 1) {
                q.push({ny, nx});
                visited[ny][nx] = 1;
            }
        }
    }
    cout << "INCONCEIVABLE\n";
}