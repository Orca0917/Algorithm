#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

string s1, s2;
int memo[1001][1001];

int dp(int idx1, int idx2) {
    if (idx1 < 0 || idx2 < 0) return 0;

    int &ret = memo[idx1][idx2];
    if (ret != -1) return ret;

    ret = 0;
    if (s1[idx1] == s2[idx2]) {
        ret = dp(idx1 - 1, idx2 - 1) + 1;
    } else {
        ret = max(ret, dp(idx1 - 1, idx2));
        ret = max(ret, dp(idx1, idx2 - 1));
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s1 >> s2;

    memset(memo, -1, sizeof(memo));
    int ret = dp(s1.length() - 1, s2.length() - 1);
    cout << ret << "\n";

    return 0;
}