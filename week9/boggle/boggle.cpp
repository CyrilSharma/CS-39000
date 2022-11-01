#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
struct Trie {
    int nodes = 1;
    vector<vi> trie;
    vi end;

    Trie() {
        trie = vector<vi>(1, vector<int>(26)); 
        end = vi(1);
    }

    void insert(string word) {
        int pos = 0;
        for (char ch: word) {
            if (trie[pos][ch - 'A'] == 0) {
                trie[pos][ch - 'A'] = nodes++;
                trie.push_back(vector<int>(26));
                end.push_back(0);
            }
            pos = trie[pos][ch - 'A'];
        }
        end[pos] = 1;
    }

    int findNode(string s) {
        int pos = 0;
        for (char ch: s) {
            if (trie[pos][ch - 'A'] > 0)
                pos = trie[pos][ch - 'A'];
            else return -1;
        }
        return pos;
    }

    bool beginsWith(string s) {
        return findNode(s) > -1;
    }
    
    bool hasWord(string s) {
        int ind = findNode(s);
        if (ind == -1) return false;
        return end[ind];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w; cin >> w;
    Trie t = Trie();
    for (int i = 0; i < w; i++) {
        string word; cin >> word;
        t.insert(word);
    }

    int b; cin >> b;
    while (b--) {
        vector<vector<char>> board(4, vector<char>(4));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> board[i][j];
            }
        }

        set<string> words;
        int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
        function<void(int,int,int,string)> dfs;
        dfs = [&](int x, int y, int state, string s) {
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx > 3 || ny < 0 || ny > 3) continue;

                int pos = 1 << (4 * nx + ny);
                if (!(state & pos)) continue;

                string ns = s;
                ns += board[ny][nx];
                if (!t.beginsWith(ns)) continue;
                if (t.hasWord(ns)) words.insert(ns);
                dfs(nx, ny, state & ~pos, ns);
            }
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                string s; s += board[i][j];
                dfs(j, i, (1<<16) - 1, s);
            }
        }

        int total_score = 0;
        string best_word = "";
        for (string word: words) {
            if (word.size() == 3 || word.size() == 4) 
                total_score += 1;
            else if (word.size() == 5)
                total_score += 2;
            else if (word.size() == 6)
                total_score += 3;
            else if (word.size() == 7)
                total_score += 5;
            else if (word.size() == 8)
                total_score += 11;

            if (word.size() > best_word.size())
                best_word = word;
            else if (word.size() == best_word.size())
                best_word = (word < best_word) ? word : best_word;
        }
        cout << total_score << " " << best_word << " " << words.size() << "\n";
    }
}