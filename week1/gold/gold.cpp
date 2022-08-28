#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

#define maxLen 50
char gmp[maxLen][maxLen];
int safe[maxLen][maxLen];
int visited[maxLen][maxLen];
int queued[maxLen][maxLen];
queue<pair<int, int> > q;

int best;
int W, H;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool outOfBounds(int y, int x) {
    if (x < 0 || x > W-1 || y < 0 || y > H-1) return true;
    return false;
}

void BFS() {
    pair<int, int> pos;
    bool nearTrap;
    int x, y, tx, ty, count;
    int numIters = 0;
    while (!q.empty()) {
        numIters++;
        nearTrap = false;
        pos = q.front(); q.pop();
        // out of bounds
        if (outOfBounds(pos.first, pos.second)) continue;

        // on a wall
        if (gmp[pos.first][pos.second] == '#') continue;

        // add gold to total.
        if (gmp[pos.first][pos.second] == 'G' && !visited[pos.first][pos.second]) best++;
        visited[pos.first][pos.second] = 1;

        // adjacent to trap
        for (int i = 0; i < 4; i++) {
            x = pos.first + dx[i]; y = pos.second + dy[i];
            if (outOfBounds(x, y)) continue;
            if (gmp[x][y] == 'T') nearTrap = true;
        }

        if (nearTrap) continue;

        for (int i = 0; i < 4; i++) {
            x = pos.first + dx[i]; y = pos.second + dy[i];
            safe[x][y] = 1;
            // add to queue only if it is not already in the queue / been visited.
            if (visited[x][y] || queued[x][y]) continue;
            q.push(make_pair(x, y));
            queued[x][y] = 1;
        }
    }
    return;
}

// redo with connected components?
int main() {
    // read from std input
    pair<int,int> startPos;
    scanf("%d %d", &W, &H);
    char s[W];
    for (int i = 0; i < H; i++) {
        scanf("%s\n", s);
        for (int j = 0; j < W; j++) {
            gmp[i][j] = s[j];
            if (s[j] == 'P') startPos = make_pair(i,j);
        }
    }
    q.push(startPos);
    BFS();
    cout << best << "\n";
}