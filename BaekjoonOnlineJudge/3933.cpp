#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[40000][182][4];

int dp(int k, int prev, int depth) {
    if (k == 0) return 1;
    if (depth == 4 || prev == 182) return 0;

    int &ret = memo[k][prev][depth];
    if (ret != -1) return ret;

    ret = dp(k, prev + 1, depth);
    if (prev * prev <= k) ret += dp(k - prev * prev, prev, depth + 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        cout << dp(n, 1, 0) << "\n";
    }
    
    return 0;
}