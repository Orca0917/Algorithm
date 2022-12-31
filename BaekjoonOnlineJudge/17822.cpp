#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, t;
deque<pii> dq[51];

pii get_sum() {
    pii answer = {0, 0};
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dq[i][j].second) {
                answer.first += dq[i][j].first;
                answer.second += 1;
            }
        }
    }
    return answer;
}

void update() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            dq[i][j].first *= dq[i][j].second;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> t;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int val; cin >> val;
            dq[i].push_back({val, 1});
        }
    }

    while (t--) {
        int x, d, k; cin >> x >> d >> k;
        for (int cur = x; cur <= n; cur += x) {
            for (int i = 1; i <= k; ++i) {
                if (d) {
                    dq[cur].push_back(dq[cur].front());
                    dq[cur].pop_front();
                }
                else {
                    dq[cur].push_front(dq[cur].back());
                    dq[cur].pop_back();
                }
            }
        }


        bool flag = true;

        // 원판 내에서 인접한 것 탐색
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dq[i][j].first != 0 && dq[i][j].first == dq[i][(j + 1) % m].first) {
                    dq[i][j].second = dq[i][(j + 1) % m].second = 0;
                    flag = false;
                }
            }
        }

        // 원판 끼리 인접한 것 탐색
        for (int j = 0; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                if (dq[i][j].first != 0 && dq[i][j].first == dq[i + 1][j].first) {
                    dq[i][j].second = dq[i + 1][j].second = 0;
                    flag = false;
                }
            }
        }

        update();

        if (flag) {
            pii sum = get_sum();
            double avg;
            if (sum.second == 0) avg = 0;
            else avg = sum.first / (double)sum.second;

            for (int i = 1; i <= n; ++i) {
                for (int j = 0; j < m; ++j) {
                    pii &cell = dq[i][j];
                    if (cell.first == 0) continue;
                    
                    if (cell.first < avg) cell.first += 1;
                    else if (cell.first > avg) cell.first -= 1;
                }
            }
        }
    }
    
    cout << get_sum().first << "\n";

    return 0;
}