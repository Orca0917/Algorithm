#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int testcase; cin >> testcase;
  while (testcase--) {
    ll n, m, k; cin >> n >> m >> k;

    ll maxEdge = n * (n - 1) / 2;
    if (maxEdge < m || m < n - 1) cout << "NO\n";
    else if (n == 1) {
      if (k > 1) cout << "YES\n";
      else cout << "NO\n";
    } else if (maxEdge > m) {
      if (k > 3) cout << "YES\n";
      else cout << "NO\n";
    } else if (k > 2) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}