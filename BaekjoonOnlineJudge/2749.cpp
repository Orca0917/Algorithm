#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000
using namespace std;

map<ll, int> m;

ll fibo(ll n) {
    if (n <= 1) return n;    
    if (m.find(n) != m.end()) return m[n];

    ll ret = 0;
    if (n % 2) ret = fibo((n + 1) / 2) * fibo((n + 1) / 2) + fibo((n - 1) / 2) * fibo((n - 1) / 2);
    else ret = fibo(n / 2) * (fibo(n / 2) + 2 * fibo(n / 2 - 1));

    return m[n] = ret % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n; cin >> n;
    cout << fibo(n) << "\n";    
    
    return 0;
}