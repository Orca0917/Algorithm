#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[12];

int dp(int n) {
    if (n == 0) return 1;
    else if (n == 1) return 1;
    else if (n == 2) return 2;

    int &ret = memo[n];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 1; i <= 3 && n - i >= 0 ; ++i) ret += dp(n - i);

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        cout << dp(n) << "\n";    
    }
    
    return 0;
}