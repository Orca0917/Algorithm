#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<ll> v;
    while (n--) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        v.emplace_back(stoll(s));
    }
    sort(v.begin(), v.end());
    for (ll e : v) cout << e << "\n";
    return 0;
}