#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(6);
    for (int i = 0; i < 6; ++i) cin >> a[i];
    int corner = min({a[A]+a[B]+a[C], a[A]+a[C]+a[E], a[A]+a[D]+a[E], a[A]+a[B]+a[D], a[B]+a[C]+a[F], a[C]+a[E]+a[F], a[D]+a[E]+a[F], a[B]+a[D]+a[F]});
    int edge = min({a[A]+min({a[B], a[C], a[D], a[E]}), a[B]+a[C], a[C]+a[E], a[D]+a[E], a[B]+a[D], a[F]+min({a[B], a[C], a[D], a[E]})});
    int minVal = *min_element(a.begin(), a.end());
    ll answer = 1LL * corner * 4 + 1LL * (n - 2) * (n - 2) * 5 * minVal + (n - 2) * 8 * edge + 1LL * 4 * edge + 1LL * (n - 2) * 4 * minVal;
    if (n == 1) cout << accumulate(a.begin(), a.end(), 0) - *max_element(a.begin(), a.end()) << "\n";
    else cout << answer << "\n";
    return 0;
}