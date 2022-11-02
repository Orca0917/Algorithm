#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int c;  // 주식의 개수
int d;  // 매입 및 매각 기간
int m;  // 초기 자금

vector<int> cost[51];   // cost[i] = 주식 i 의 미래 정보
int memo[500'001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> c >> d >> m;
    for (int stock = 0; stock < c; ++stock) {
        for (int day = 0; day < d; ++day) {
            int value; cin >> value;
            cost[stock].push_back(value);
        }
    }    

    for (int day = 1; day < d; ++day) {
        memset(memo, 0, sizeof(memo));
        for (int stock = 0; stock < c; ++stock) {
            for (int k = cost[stock][day - 1]; k <= m; ++k) {
                int new_balance = k - cost[stock][day - 1];
                int benefit = cost[stock][day] - cost[stock][day - 1];
                memo[k] = max(memo[k], memo[new_balance] + benefit);
            }
        }
        m += memo[m];
    }
    
    cout << m << "\n";
    return 0;
}