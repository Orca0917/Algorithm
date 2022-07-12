#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n; // 수열의 길이
vector<int> A;
vector<ll> psum; // A[i] = psum[i] - psum[i - 1]

ll memo[100001][4];

ll dp(int index, int divide, ll value) {
    ll &ret = memo[index][divide];
    if (ret != -1) return ret;

    if (divide == 0) return ret = (psum[index] == value) ? 1 : 0;
    else if (index == 1) return ret = 0;


    ret = 0;
    for (int i = index - 1; i >= 1; --i) 
        if (psum[index] - psum[i] == value)
            ret += dp(i, divide - 1, value);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int zero_cnt = 0;
    ll answer = 0; 

    cin >> n;

    A.resize(n + 1, 0);
    psum.resize(n + 1, 0);
    memset(memo, -1LL, sizeof(memo));

    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
        psum[i] = psum[i - 1] + A[i];
        if (psum[i] == 0) zero_cnt += 1;
    }

    if (psum[n] == 0) answer = 1LL * (zero_cnt - 1) * (zero_cnt - 2) * (zero_cnt - 3) / 6;
    else if (psum[n] % 4 == 0) answer = dp(n, 3, psum[n] / 4);
    cout << answer << "\n";
    
    return 0;
}