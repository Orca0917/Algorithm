#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<ll> arr;
vector<ll> psum;

map<ll, ll> m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n, k; cin >> n >> k;
    arr.resize(n);
    psum.resize(n);

    for (ll &e : arr) cin >> e;

    ll answer = 0;

    m[0] = 1;
    psum[0] = arr[0];
    if (arr[0] == k) ++answer;
    m[psum[0]] += 1;

    
    for (int i = 1; i < n; ++i) {
        psum[i] = psum[i - 1] + arr[i];

        ll total = psum[i];
        ll want = total - k;
        if (m.find(want) != m.end()) answer += m[want];

        m[psum[i]] += 1;
    }

    cout << answer << "\n";
    
    return 0;
}