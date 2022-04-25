#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll memo[32][32];
// memo[i][j] = iCj

// n개의 자리를 l개의 비트로 표현할 수 있는 가지수
ll dp(int n, int l) {
    if (l < 0) return 0;
    if (n == 0 || l == 0) return 1;

    ll &ret = memo[n][l];
    if (ret != -1) return ret;

    return ret = dp(n - 1, l) + dp(n - 1, l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));
    int N, L; cin >> N >> L;
    ll I; cin >> I;
    string answer = "";

    if (L == 0) {
        answer = "";
        for (int i = 1; i <= N; ++i)
            answer += "0";
    }
    else {
        for (int i = N; i >= 1; --i) {
            ll sum = dp(i - 1, L);
            if (I <= sum) {
                answer += "0";
            } else {
                answer += "1";
                I -= sum;
                --L;
            }
        }
    }

    cout << answer << "\n";
    
    return 0;
}