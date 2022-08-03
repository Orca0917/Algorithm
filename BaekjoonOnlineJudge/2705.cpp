#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int memo[1001];

int dp(int num) {
    if (num == 1) return 1;

    int &ret = memo[num];
    if (ret != -1) return ret;

    ret = 1;

    // 홀수개의 재귀적인 파티션으로 구성
    for (int i = 1; i < num; ++i) {
        int part = (num - i);
        if (part % 2) continue;

        ret += dp(part / 2);
    }

    // 짝수개의 재귀적인 파티션으로 구성
    if (num % 2 == 0) ret += dp(num / 2);

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