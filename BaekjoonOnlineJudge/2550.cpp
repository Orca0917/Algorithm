#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> bulbs;
    vector<int> index(n + 1);
    for (int i = 1; i <= n; ++i) {
        int button; cin >> button;
        index[button] = i;
    }

    for (int i = 1; i <= n; ++i) {
        int bulb; cin >> bulb;
        bulbs.push_back(bulb);
        v.push_back(index[bulb]);
    }

    vector<int> lis;
    vector<int> memo;
    lis.push_back(-1);

    for (int e : v) {
        if (lis.back() < e) {
            memo.push_back(lis.size());
            lis.push_back(e);
        } else {
            auto it = lower_bound(lis.begin(), lis.end(), e);
            *it = e;
            memo.push_back(distance(lis.begin(), it));
        }
    }

    cout << lis.size() - 1 << "\n";

    vector<int> idxs;
    int target = lis.size() - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (memo[i] == target) {
            idxs.push_back(bulbs[i]);
            --target;
        }
    }

    sort(idxs.begin(), idxs.end());
    for (int e : idxs) cout << e << " ";

    
    return 0;
}