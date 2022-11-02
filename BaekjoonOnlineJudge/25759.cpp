#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

ll memo[100'001][101];
vector<ll> arr;
int N;
ll answer = 0;


ll dp(int index, int prev) {
    // base condition
    if (index == N) return 0;

    // memoization
    ll &ret = memo[index][prev];
    if (ret != -1) return ret;

    // [1] 현재 꽃을 선택하는 경우 : dp(index + 1, arr[index]) + benefit
    // [2] 현재 꽃을 선택하지 않는 경우 : dp(index + 1, arr[index])
    ll benefit = (arr[index] - prev) * (arr[index] - prev);
    ret = max(dp(index + 1, prev), dp(index + 1, arr[index]) + benefit);

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;
    arr.resize(N);
    for (ll &e : arr) cin >> e;

    memset(memo, -1, sizeof(memo));

    // 가능한 모든 시작점에서 시도
    for (int i = 0; i < N; ++i) answer = max(answer, dp(i, arr[i]));

    cout << answer << "\n";
    
    return 0;
}