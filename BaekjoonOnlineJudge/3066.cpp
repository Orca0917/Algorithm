#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        int n; cin >> n;
        vector<int> v;
        for (int i = 0; i < n; ++i) {
            int k; cin >> k;
            if (v.empty() || v.back() < k) v.emplace_back(k);
            else *lower_bound(v.begin(), v.end(), k) = k;
        }       

        cout << v.size() << "\n";
    }
    
    return 0;
}