#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int caves; cin >> caves;
        vector<pii> v;
        for (int i = 0; i < caves; ++i) {
            int monsters; cin >> monsters; // number of monsters in cave[i]
            int M = 0;
            for (int j = 0; j < monsters; ++j) {
                int armor; cin >> armor;
                M = max(M, armor - j);
            }
            v.push_back({M, monsters});
        }

        sort(v.begin(), v.end());
        int required = 0, st = 0;
        for (auto e : v) {
            required = max(required, e.first - st);
            st += e.second;
        }
        cout << required + 1 << "\n";
    }
    return 0;
}