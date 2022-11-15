#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;  // 바나나의 수
int K;  // 한번에 들고 갈 수 있는 최대 바나나
int C;  // 최대 바나나를 들고갈 때 걸리는 시간

vector<ll> weight;
ll memo[1'000'001];
int nxt[1'000'001];

/**
 * @brief dp(index) : [index, N] 의 바나나를 옮기는데 필요한 최소 시간
 * 
 * (1) index에 존재하는 바나나 1개를 옮기는 경우: weight[index]
 * (2) [index, index + K - 1]에 존재하는 바나나 K개를 옮기는 경우: C
 * 
 * @param index 
 * @return ll 
 */
ll dp(int index) {
    // 기저사례: 바나나를 모두 옮김
    if (index == N + 1) return 0;

    // 메모이제이션
    ll &ret = memo[index];
    if (ret != -1) return ret;

    ll ret1, ret2 = 1e13;
    ret1 = dp(index + 1) + weight[index];
    if (index + K - 1 <= N) ret2 = dp(index + K) + C;

    nxt[index] = (ret1 > ret2 ? index + K : index + 1);

    return ret = min(ret1, ret2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> K >> C;

    weight.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> weight[i];

    memset(memo, -1, sizeof(memo));
    cout << dp(1) << "\n";


    int cur = 1;
    vector<int> jumps;
    while (cur <= N) {
        if (nxt[cur] - cur == K && memo[cur] - memo[nxt[cur]] != weight[cur])
            jumps.push_back(cur);
        cur = nxt[cur];
    }

    cout << jumps.size() << "\n";

    for (int e : jumps) cout << e << "\n";

    return 0;
}