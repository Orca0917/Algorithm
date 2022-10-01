#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000'007
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        priority_queue<ll> pq;
        while (n--) {
            ll x; cin >> x;
            pq.push(-x);
        }

        ll answer = 1;
        while (pq.size() > 1) {
            ll x = -pq.top(); pq.pop();
            ll y = -pq.top(); pq.pop();
            ll res = x * y;

            pq.push(-res);
            res = res % MOD;

            answer *= res;
            answer %= MOD;
            
        }

        cout << answer << "\n";
    }
    
    return 0;
}