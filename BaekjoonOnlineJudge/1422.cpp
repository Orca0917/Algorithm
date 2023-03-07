#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> v(n + 1, 0);

    for (int i = 1; i <= n; ++i) cin >> v[i];

    int k; cin >> k;
    while (k--) {
        int gender, num; cin >> gender >> num;
        if (gender == 1) {
            for (int i = num; i <= n; i += num) v[i] ^= 1;
        } else {
            int s = num, e = num;
            while (s > 0 && e <= n && v[s] == v[e]) {
                --s; ++e;
            }
            for (int i = s + 1; i < e; ++i) v[i] ^= 1;
        }
    }

    for (int i = 1; i <= n; ++i) cout << v[i] << " \n"[i == n || i % 20 == 0];
    
    return 0;
}