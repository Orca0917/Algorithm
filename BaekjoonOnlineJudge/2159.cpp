#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;
vector<pii> v;
int movement[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
ll memo[100001][5];

ll dp(int index, int dir) {
    if (index == N) return 0;

    ll &ret = memo[index][dir];
    if (ret != -1) return ret;

    int cx = v[index].first + movement[dir][0];
    int cy = v[index].second + movement[dir][1];

    ret = 1e14;
    for (int i = 0; i < 5; ++i) {
        int nx = v[index + 1].first + movement[i][0];
        int ny = v[index + 1].second + movement[i][1];

        int diff = abs(cx - nx) + abs(cy - ny);
        ret = min(ret, dp(index + 1, i) + diff);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 손님의 수
    cin >> N;
    v.resize(N + 1);

    // 초기 위치를 포함하여 손님을 입력받는다.
    for (pii &e : v) cin >> e.first >> e.second;

    memset(memo, -1, sizeof(memo));
    cout << dp(0, 0);
    
    return 0;
}