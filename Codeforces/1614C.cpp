#include <bits/stdc++.h>
 
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define MOD 1'000'000'007
using namespace std;
 
int power(int a, int b) {
    ll ret = 1;
 
    for (int i = 1; i <= b; ++i) {
        ret *= a;
        ret %= MOD;
    }
 
    return ret;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    const ull INF = (1 << 30) - 1;
    int testcase; cin >> testcase;
 
    while (testcase--) {
        int n, m; cin >> n >> m;
        
        ll arr[200001];
        for (int i = 1; i <= n; ++i) arr[i] = INF;
 
        int bits = 0;
        for (int i = 0; i < m; ++i) {
            int start, end, val; cin >> start >> end >> val;
            bits |= val;
        }
        
        ull answer = 1ULL * bits * power(2, n - 1);
        cout << answer % MOD << "\n";
 
    }
    
    return 0;
}