#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
int memo[1001][1001];
vector<int> v;

int dp(int name, int row, int start) {
    if (name == n) return 0;

    int &ret = memo[name][start];
    if (ret != -1) return ret;

    // 다음 줄에 이름을 작성하는 경우
    ret = dp(name + 1, row + 1, v[name] + 1) + (m - start + 1) * (m - start + 1);
    if (start + v[name] - 1 < m) ret = min(ret, dp(name + 1, row, start + v[name] + 1));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    v.resize(n);
    for (int &e : v) cin >> e;

    memset(memo, -1, sizeof(memo));
    cout << dp(0, 0, 0) << "\n";
    return 0;
}