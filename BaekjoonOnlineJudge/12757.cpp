#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m, k;
    map<int, int> mm;

    cin >> n >> m >> k;
    for (int i = 0 ; i < n; ++i) {
        int _key, _val; cin >> _key >> _val;
        mm[_key] = _val;
    }

    auto getPosition = [&](int key) -> int {
        auto lo = mm.lower_bound(key);

        int cur = -1;
        int pre = -1;

        if (lo != mm.end()) cur = lo -> first;
        else {
            assert(lo == mm.end());
            --lo;
            cur = lo -> first;
        }
            
        if (lo != mm.begin()) pre = prev(lo) -> first;

        int ret = cur;
        if (pre != -1) {
            int dist1 = abs(cur - key);
            int dist2 = abs(pre - key);

            if (dist1 == dist2) return -2;
            if (dist1 > dist2) ret = pre;
        }

        if (abs(ret - key) > k) return -1;
        return ret;
    };

    while (m--) {
        int option; cin >> option;

        int key, value; cin >> key;
        if (option == 1) {
            cin >> value;
            mm[key] = value;
        } else if (option == 2) {
            cin >> value;
            int res = getPosition(key);

            if (res >= 0) mm[res] = value;
        } else {
            int res = getPosition(key);
            if (res == -1) cout << "-1\n";
            else if (res == -2) cout << "?\n";
            else cout << mm[res] << "\n";
        }
    }
    return 0;
}