#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
const int MAX = 200007;
ll S[MAX];
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		ll N, K, s = 0, ans = 0;
		cin >> N >> K;
		for (int i = 0; i < N; ++i) cin >> S[i];
		s = accumulate(S, S + N, 0LL);
		sort(S, S + N);
		if (s <= K) {
			cout << 0 << '\n';
			continue;
		}
		ans = max(0LL, s - K);
		ll diff = 0, n = 0;
		for (int i = N - 1; i > 0; --i) {
			diff += S[i] - S[0];
			n++;
			ll need = max(0LL, ((s - diff) - K + n) / (n + 1));
			ans = min(ans, n + need);
		}
		cout << ans << '\n';
	}
	return 0;
}