#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    set<int> s;
    int ans = 0;

    while (n--) {
        int k; cin >> k;
        s.insert(k);
    }

    while (m--) {
        int k; cin >> k;
        auto it = s.lower_bound(k);
        if (it != s.end() && *it == k) s.erase(it);
        else s.insert(k);
    }

    cout << s.size() << "\n";

    return 0;
}