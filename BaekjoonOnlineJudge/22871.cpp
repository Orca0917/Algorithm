#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> rock;
int memo[5001];

int dp(int i, ll k) {
    if (i == n - 1) return 1;

    int &ret = memo[i];
    if (ret != -1) return ret;

    ret = 0;
    for (int j = i + 1; j < n; ++j) {
        ll cost = 1LL * (j - i) * (1 + abs(rock[i] - rock[j]));
        if (cost <= k) ret |= dp(j, k);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    rock.resize(n);
    for (int &e : rock) cin >> e;

    ll lo = 1, hi = 1e10;
    ll answer = hi;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        memset(memo, -1, sizeof(memo));
        if (dp(0, mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer;
    
    return 0;
}