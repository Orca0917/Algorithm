#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[5001][2], n;
vector<int> arr;

int dp(int index, int opt, int cur_val) {
    if (index >= n) return 0;
    if (cur_val == 0) {
        if (index + 1 < n) return dp(index + 1, 0, arr[index + 1]);
        else return 0;
    }

    int &ret = memo[index][opt];
    if (ret != -1) return ret;

    ret = dp(index + 1, 0, arr[index + 1]) + 1;

    int next_val = arr[index + 1] ^ cur_val;
    ret = min(ret, dp(index + 1, 1, next_val) + 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        arr.clear();
        cin >> n;
        arr.resize(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];

        memset(memo, -1, sizeof(memo));

        cout << dp(0, 0, arr[0]) << "\n";
    }
    
    return 0;
}