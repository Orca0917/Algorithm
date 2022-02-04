#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);

    for (auto &e : v) cin >> e;
    sort(v.rbegin(), v.rend());

    ll answer = accumulate(v.begin(), v.begin() + k, 0);
    answer -= k * (k - 1) / 2;

    cout << answer << "\n";

    return 0;
}