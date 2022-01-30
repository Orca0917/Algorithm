#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct tri {
    int idx, val, sort_idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<tri> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].val;
        a[i].idx = i;
    }
    
    sort(a.begin(), a.end(), [](const tri &a, const tri &b) {
        if (a.val == b.val) return a.idx < b.idx;
        return a.val < b.val;
    });

    for (int i = 0; i < n; ++i) {
        a[i].sort_idx = i;
    }

    sort(a.begin(), a.end(), [](const tri &a, const tri &b) {
        return a.idx < b.idx;
    });

    for (auto &e : a)
        cout << e.sort_idx << " ";
    return 0;
}