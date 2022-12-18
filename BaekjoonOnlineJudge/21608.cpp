#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 20 * 20 + 1
using namespace std;

int n;
int board[21][21];
int movements[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int result[5] = {0, 1, 10, 100, 1000};
vector<int> student[MAX];
vector<int> orders;

bool check(int target, int std) {
    for (int lover : student[std]) 
        if (lover == target) 
            return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    for (int i = 1; i <= n * n; ++i) {
        int who; cin >> who;
        orders.push_back(who);
        for (int j = 0; j < 4; ++j) {
            int like; cin >> like;
            student[who].push_back(like);
        }
    } 

    memset(board, 0, sizeof(board));

    for (int std : orders) {
        
        pii stat = {0, 0}; // (love cnt, empty cnt)
        pii pos = {-1, -1};

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                if (board[i][j] != 0) continue;
                if (pos.first == -1) pos = {i, j};
                int love_cnt = 0, empty_cnt = 0;
                
                for (int k = 0; k < 4; ++k) {
                    int xx = i + movements[k][0];
                    int yy = j + movements[k][1];

                    if (xx <= 0 || xx > n || yy <= 0 || yy > n) continue;

                    if (board[xx][yy] == 0) ++empty_cnt;
                    else if (check(board[xx][yy], std)) ++love_cnt;
                }

                if (stat.first < love_cnt) {
                    stat = {love_cnt, empty_cnt};
                    pos = {i, j};
                } else if (stat.first == love_cnt && stat.second < empty_cnt) {
                    stat = {love_cnt, empty_cnt};
                    pos = {i, j};
                }
            }

        board[pos.first][pos.second] = std;
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cnt = 0;
            for (int k = 0; k < 4; ++k) {
                int xx = i + movements[k][0];
                int yy = j + movements[k][1];

                if (xx <= 0 || xx > n || yy <= 0 || yy > n) continue;

                if (check(board[xx][yy], board[i][j])) ++cnt;
            }
            answer += result[cnt];
        }
    }

    cout << answer << "\n";

    return 0;
}