#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<vector<int>> status;
int num_enemy, num_win;
int answer = 1e9;

void dfs(vector<int> current, int index) {
    // 이전 능력치로 이길 수 있는 사람의 수 파악
    int win_cnt = 0;
    for (int i = 0; i < num_enemy; ++i) {
        bool win = true;
        for (int j = 0; j < index; ++j) {
            if (status[i][j] > current[j]) {
                win = false;
                break;
            }
        }
        if (win) ++win_cnt;
    }

    // 이미 이전 능력치로 승리횟수를 채울 수 없음
    if (win_cnt < num_win) return;


    if (index == 3) {
        answer = min(answer, current[0] + current[1] + current[2]);
        return;
    }

    // 최소 능력치 이상인 것들에 대해서 시도
    for (int i = 0; i < num_enemy; ++i) {
        current[index] = status[i][index];
        dfs(current, index + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> num_enemy >> num_win;
    status.resize(num_enemy);

    for (int i = 0; i < num_enemy; ++i) {
        for (int j = 0; j < 3; ++j) {
            int value; cin >> value;
            status[i].push_back(value);
        }
    }

    vector<int> now_status(3, 0);
    dfs(now_status, 0);
    cout << answer << "\n";
    
    return 0;
}