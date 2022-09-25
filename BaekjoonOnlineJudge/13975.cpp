#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        priority_queue<ll> pq;

        int n; cin >> n;
        while (n--) {
            int x; cin >> x;
            pq.push(-x);
        }

        ll answer = 0;
        while (pq.size() > 1) {
            ll frag1 = -pq.top(); pq.pop();
            ll frag2 = -pq.top(); pq.pop();
            answer += (frag1 + frag2);
            pq.push(-(frag1 + frag2));
        }

        cout << answer << "\n";
    }
    
    return 0;
}