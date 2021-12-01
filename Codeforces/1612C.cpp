#include <bits/stdc++.h>
 
#define ll long long
#define MAX 1234567890
 
using namespace std;
 
ll getSum(ll height, ll mid) {
  ll ret = height * (height + 1) / 2;;
  
  if (height > mid) {
    ll left = height - mid;
    ll under = ((mid - 1) + (mid - left)) * left / 2;
    ret = (mid * (mid + 1)) / 2 + under;
  }
  return ret;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
 
  int testcase; cin >> testcase;
  while (testcase--) {
    ll k, x; cin >> k >> x;
 
    ll lo = 1, hi = 2 * k - 1, answer = 1;
 
    while (lo + 1 < hi) {
      ll mid = (lo + hi) / 2;
      ll sum = getSum(mid, k);
 
      if (sum == x) {
        answer = mid;
        break;
      }
      if (sum < x) {
        answer = mid + 1;
        lo = mid;
      } else if (sum > x) {
        hi = mid;
      }
    }
 
    if (k >= 2 && x == 2) cout << "2\n";
    else cout << answer << "\n";
  }
 
  return 0;
}