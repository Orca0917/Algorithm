#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 새의 개체 수
int C; // 매일 포획할 새의 수
int D; // 관측 기간
int M; // 최종적으로 측정기가 부작된 새의 수

ll memo[6][21];
ll memo2[21][21];
ll combination = 1;

ll comb(int n, int r) {
    if (n == r || r == 0) return 1;

    ll &ret = memo2[n][r];
    if (ret != -1) return ret;

    ret = comb(n - 1, r) + comb(n - 1, r - 1);
    return ret;
}

ll dp(int days, int bird) {
    if (days == D) {
        if (bird == M) return 1;
        else return 0;
    }

    ll &ret = memo[days][bird];
    if (ret != -1) return ret;

    ret = 0;
    for (int before = 0; before <= C; ++before) {
        ll tmp = comb(bird, C - before) * comb(N - bird, before);
        if (tmp > 0) ret += tmp * dp(days + 1, bird + before);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C >> D >> M;

    memset(memo, -1, sizeof(memo));
    memset(memo2, -1, sizeof(memo2));
    combination = comb(N, C);

    ll divisor = 1;
    for (int i = 1; i <= D; ++i) divisor *= combination;

    cout << setprecision(14) << fixed << (dp(0, 0) / (long double)divisor) << "\n";

    return 0;
}