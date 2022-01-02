#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;
 
const ll MAX = 5007, MOD = 998244353;
string S;
ll one[MAX], zero[MAX], F[MAX] = { 1, 1 };
vector<pii> seg;
 
ll Pow(ll num, ll exp) {
	if (exp <= 1) return (!exp ? 1 : num);
	ll half = Pow(num, exp >> 1);
	ll ret = half * half % MOD;
	return ((exp & 1) ? (ret * num) % MOD : ret);
}
 
ll Comb(ll N, ll K) {
	if (K == 0 || K == N) return 1;
	ll a = F[N], b = F[K] * F[N - K] % MOD;
	ll ret = a * (Pow(b, MOD - 2)) % MOD;
	return ret;
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	F[1] = 1;
	for (int i = 2; i < MAX; ++i) F[i] = F[i - 1] * i % MOD;
	ll N, K, ans = 0;
	cin >> N >> K >> S;
	S = '_' + S;
	for (int i = 1; i <= N; ++i) (S[i] == '0' ? zero[i] : one[i])++;
	for (int i = 1; i <= N; ++i) {
		one[i] += one[i - 1];
		zero[i] += zero[i - 1];
	}
	if (K == 0) {
		cout << 1;
		return 0;
	}
	if (one[N] < K) {
		cout << 1; 
		return 0;
	}
	int L = 1, R = 1, ones = S[1] == '1';
	while (R <= N) {
		if (S[++R] == '1') ones++;
		if (ones > K) {
			seg.emplace_back(L, R - 1);
			while (ones > K) {
				if (S[L] == '1') ones--;
				L++;
			}
		}
		if (R == N) {
			if (ones == K) seg.emplace_back(L, R);
			break;
		}
	}
	int pvL = 0, pvR = 0;
	for (pii k : seg) {
		ans += Comb(k.second - k.first + 1, K) - 1;
		if (k.first <= pvR) ans -= Comb(pvR - k.first + 1, K - 1) - 1;
		pvL = k.first, pvR = k.second;
		ans %= MOD;
	}
	cout << (ans + 1 + MOD * 2LL) % MOD;
	return 0;
}