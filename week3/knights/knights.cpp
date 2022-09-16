// Author: Cyril Sharma
// It is ok to post my anonymized solution

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

#define maxVal 1e9

typedef vector<char> vc; 
typedef vector<vector<char>> vvc;

// Easiest way I could think to validate a solution.
vvc sol = {
    {'1', '1', '1', '1', '1'},
    {'0', '1', '1', '1', '1'},
    {'0', '0', ' ', '1', '1'},
    {'0', '0', '0', '0', '1'},
    {'0', '0', '0', '0', '0'},
};
int solved(vvc board) {
    int wrongs = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // counts number of blacks and whites in the wrong position.
            if (board[i][j] != sol[i][j] && board[i][j] != ' ') wrongs++;
        }
    }
    return wrongs;
}

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool DFS(int depth, int d, pair<int,int> empty, vvc board) {
    int wrongs = solved(board);
    if (wrongs == 0) return true;
    // you can fix at most one incorrectly placed black or white position per move.
    // thus, if the number of positions to fix is too large, you can return false far in advance.
    // THIS IS VERY IMPORTANT. Without this pruning, the code will not pass.
    if (wrongs > depth - d) return false;
    if (depth == d) return false;
    int y = empty.first; int x = empty.second;
    int nx, ny;
    bool solved = false;
    for (int i = 0; i < 8; i++) {
        nx = x + dx[i]; ny = y + dy[i];
        // Out of bounds.
        if (nx < 0 | nx > 4) continue;
        if (ny < 0 | ny > 4) continue;
        
        // Mutate board.
        board[y][x] = board[ny][nx];
        board[ny][nx] = ' ';

        // Perform DFS with mutated board.
        if (DFS(depth, d+1, make_pair(ny, nx), board)) {
            solved = true;
            break;
        }

        // Unmutate board.
        board[ny][nx] = board[y][x];
        board[y][x] = ' ';
    }
    return solved;
}

int main() {
    int ntests;
    cin >> ntests;
    string s; getline(cin, s);
    while (ntests--) {
        vvc board(5, vc(5));
        pair<int,int> start;

        int w = 0; int b = 0;
        for (int i = 0; i < 5; i++) {
            getline(cin, s);
            for (int j = 0; j < 5; j++) {
                board[i][j] = s[j];
                if (s[j] == ' ') start = make_pair(i, j);
                if (s[j] == '1') b++;
                if (s[j] == '0') w++;
            }
        }

        // the problem is impossible, there aren't enough knights for it to be solvable.
        if (w != 12 || b != 12) {
            cout << "Unsolvable in less than 11 move(s).\n";
            continue;
        }

        // Iterative deepening! We perform a DFS with max depth i until we find a solution.
        // This allows us to just mutate one board state, (BFS would require keeping track of all the moves)
        bool solvable = false;
        for (int i = 0; i <= 10; i++) {
            if (DFS(i, 0, start, board)) {
                cout << "Solvable in " << i << " move(s).\n";
                solvable = true;
                break;
            }
        }
        if (!solvable) cout << "Unsolvable in less than 11 move(s).\n";
    }
}