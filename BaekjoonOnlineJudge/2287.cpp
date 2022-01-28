#include <bits/stdc++.h>
#include <unordered_set>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll n, a, target;
set<ll> s[9];

void doC(ll x) {

    ll iter = x;
    for (int i = 1; i <= 8; ++i) {
        s[i].insert(iter);
        iter = iter * 10 + x;
    }

    for (int i = 1; i <= 7; ++i)
        for (int j = 1; j <= 8 - i; ++j) {
            for (ll e1 : s[i])
                for (ll e2 : s[j]) {
                    s[i + j].insert(e1 + e2);
                    s[i + j].insert(abs(e1 - e2));
                    s[i + j].insert(e1 * e2);
                    s[i + j].insert(e2 / e1);
                    s[i + j].insert(e1 / e2);
                    s[i + j].erase(0);
                }
        }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> a;
    doC(n);

    while (a--) {
        cin >> target;
        
        int answer = 0;
        for (int i = 1; i <= 8; ++i) {
            auto it = s[i].find(target);
            if (it != s[i].end()) {
                answer = i;
                break;
            }
        }

        if (answer == 0) cout << "NO\n";
        else cout << answer << "\n";
    }

    return 0;
}