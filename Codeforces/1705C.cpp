#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    ll left;
    ll right;
    ll diff;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        int n, c, q; cin >> n >> c >> q;
        string s; cin >> s;
        
        vector<QUERY> query(c + 1);
        query[0] = {0, n, 0};

        for (int i = 1; i <= c; ++i) {
            ll l, r; cin >> l >> r;
            --l; --r;

            query[i].left = query[i - 1].right;
            query[i].right = query[i].left + (r - l + 1);
            query[i].diff = query[i].left - l;
        }

        while (q--) {
            ll x; cin >> x; --x;
            for (int i = c; i >= 1; --i) {
                if (x < query[i].left) continue;
                else x -= query[i].diff;
            }
            cout << s[x] << "\n";
        }
    }
    
    return 0;
}