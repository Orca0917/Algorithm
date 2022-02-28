#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    for (int i = 1; i <= testcase; ++i) {
        cout << "Case #" << i << "\n";

        vector<int> v;

        int n, k; cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            int num; cin >> num;
            if (i == 0 || v.back() < num) v.emplace_back(num);
            else {
                auto it = lower_bound(v.begin(), v.end(), num);
                *it = num;
            }
        }

        if (v.size() < k) cout << "0\n";
        else cout << "1\n";
    }
    
    return 0;
}