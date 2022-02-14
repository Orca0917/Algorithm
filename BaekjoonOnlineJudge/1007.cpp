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
        vector<pair<ll, ll>> v(n);

        for (pair<ll, ll> &in : v) cin >> in.first >> in.second;

        vector<ll> perm(n, 1LL);
        fill(perm.begin(), perm.begin() + n/2, -1LL);

        ll answer = 1e11;
        do {
            pair<ll, ll> pos = {0, 0};
            for (int iter = 0; iter < n; ++iter) {
                pos.first += v[iter].first * perm[iter];
                pos.second += v[iter].second * perm[iter];
            }
            answer = min(answer, pos.first * pos.first + pos.second * pos.second);
        } while (next_permutation(perm.begin(), perm.end()));

        cout << fixed << setprecision(10) << sqrt(answer) << "\n";
    }
    
    return 0;
}