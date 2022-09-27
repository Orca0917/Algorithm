#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> v(n);
    for (int &e : v) cin >> e;
    sort(v.rbegin(), v.rend());

    ll total = accumulate(v.begin(), v.end(), 0LL);

    ll answer = 0;
    for (int i = 0; i < n - 1; ++i) {
        total -= v[i];
        answer += v[i] * total;
    }

    cout << answer << "\n";

    return 0;
}