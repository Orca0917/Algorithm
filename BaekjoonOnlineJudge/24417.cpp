#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD ((int)1e9 + 7)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    ll a = 1, b = 1, c = 1;
    for (int i = 0; i < n - 1; ++i) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }

    cout << a << " " << (n - 2) % MOD << "\n";
    
    return 0;
}