#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N, M;
vector<int> D, C;
int memo[1001][1001];

// now에서 day일째 목표지점인 N까지 이동하는 최소 피로도
int solve(int now, int day) {
    if (now == N) return 0;
    if (day > M) return 1e9;

    int &ret = memo[now][day];
    if (ret != -1) return ret;

    return ret = min(
        solve(now + 1, day + 1) + D[now + 1] * C[day], 
        solve(now, day + 1)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;
    D.resize(N + 1);
    C.resize(M + 1);

    for (int i = 1; i <= N; ++i) cin >> D[i];   // D[i] : i - 1과 i 사이의 거리
    for (int i = 1; i <= M; ++i) cin >> C[i];   // C[i] : i 번째 날의 날씨 나쁨정도

    memset(memo, -1, sizeof(memo));
    cout << solve(0, 1);
    
    return 0;
}