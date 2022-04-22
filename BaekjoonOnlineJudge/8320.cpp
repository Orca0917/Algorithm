#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll memo[10001];

ll get_divisor(int n) {
    ll cnt = 0;
    for (int i = 1; i <= sqrt(n); ++i) {
        if (n % i == 0) 
            ++cnt;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, 0, sizeof(memo));
    
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        memo[i] = memo[i - 1] + get_divisor(i);
    }

    cout << memo[n] << "\n";
    return 0;
}