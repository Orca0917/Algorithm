#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll inverse(ll a, ll b) {
    ll temp_b = b, x = 1, y = 0;
    if (b == 1) return 0;
    while (a > 1) {
        ll q = a / b;
        ll t = b;
        b = a % b, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += temp_b;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int K, C; cin >> K >> C;
        if (C == 1 & K == 1e9) cout << "IMPOSSIBLE\n";
        else if (__gcd(K, C) != 1) cout << "IMPOSSIBLE\n";
        else {
            ll res = inverse(K, C) * (C - 1) % C;
            if (C == 1) res = 1;
            cout << (K * res + 1) / C << "\n";
        }
    }
    
    return 0;
}