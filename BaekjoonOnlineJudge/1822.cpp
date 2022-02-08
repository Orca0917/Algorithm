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

    while (n--) {
        int k; cin >> k;
        s.insert(k);
    }

    while (m--) {
        int k; cin >> k;
        auto it = s.find(k);
        if (it == s.end()) continue;
        s.erase(it);
    }

    cout << s.size() << "\n";
    for (auto it = s.begin(); it != s.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    return 0;
}