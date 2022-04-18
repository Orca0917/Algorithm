#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll exEuclid(ll a, ll p, ll &s, ll &t) {
    if (p == 0) {
        s = 1;
        t = 0;
        return a;
    }

    ll gcd = exEuclid(p, a % p, s, t);
    ll temp = t;
    t = s - (a / p) * t;
    s = temp;

    if (s <= 0) {
        s += p;
        t -= a;
    }

    return gcd;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll a, n, c, k; cin >> n >> a;
    // ax + ny = 1

    cout << n - a << " ";

    if (__gcd(a, n) != 1) cout << "-1\n";
    else {
        exEuclid(a, n, c, k);
        cout << c << "\n";
    }
    return 0;
}