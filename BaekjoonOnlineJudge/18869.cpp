#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int m, n; cin >> m >> n;
    vector<int> spaces[101];

    auto compress = [n](vector<int> &x) -> void {
        vector<int> v(x);
        sort(v.begin(), v.end());
        auto last = unique(v.begin(), v.end());
        v.resize(last - v.begin());

        for (int iter = 0; iter < n; ++iter) {
            auto it = lower_bound(v.begin(), v.end(), x[iter]);
            x[iter] = it - v.begin();
        }
    };

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int sz; cin >> sz;
            spaces[i].push_back(sz);
        }
        compress(spaces[i]);
    }

    auto cmp = [n](const vector<int> &a, const vector<int> &b) -> bool {
        for (int i = 0; i < n; ++i)
            if (a[i] != b[i]) return false;
        return true;
    };

    ll answer = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (cmp(spaces[i], spaces[j])) ++answer;
        }
    }

    cout << answer << "\n";
    return 0;
}