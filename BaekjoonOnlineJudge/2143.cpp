#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll a[1001], psum_a[1001];
ll b[1001], psum_b[1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	// 배열 초기화
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(psum_a, 0, sizeof(psum_a));
	memset(psum_b, 0, sizeof(psum_b));
	

	// 기본적인 입력받기
	int t, n, m;
	cin >> t >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; ++i) cin >> b[i];
	
	// 누적합 계산하기
	psum_a[0] = a[0];
	for (int i = 1; i < n; ++i) psum_a[i] = psum_a[i - 1] + a[i];
		
	psum_b[0] = b[0];
	for (int i = 1; i < m; ++i) psum_b[i] = psum_b[i - 1] + b[i];
		
	// a의 가능한 부분합 계산
	vector<ll> va;
	for (int i = -1; i < n; ++i)
		for (int j = i + 1; j < n; ++j) {
			if (i == -1) va.emplace_back(psum_a[j]);
			else {
				ll temp = psum_a[j] - psum_a[i];
				va.emplace_back(temp);
			}
		}
		
	map<ll, ll> mb;
	// b의 가능한 부분합 계산
	vector<ll> vb;
	for (int i = -1; i < m; ++i)
		for (int j = i + 1; j < m; ++j) {
			if (i == -1) {
				auto it = mb.find(psum_b[j]);
				if (it == mb.end()) mb.insert(make_pair(psum_b[j], 1));
				else mb[psum_b[j]]++;

				vb.emplace_back(psum_b[j]);
			}
			else {
				ll temp = psum_b[j] - psum_b[i];
				auto it = mb.find(temp);
				if (it == mb.end()) mb.insert(make_pair(temp, 1));
				else mb[temp]++;

				vb.emplace_back(temp);
			}
		}
	
	sort(va.begin(), va.end());
	sort(vb.begin(), vb.end());
	
	ll answer = 0;
	for (int i = 0; i < (int)va.size(); ++i) {
		ll pick = va[i];
		ll target = t - pick;
		auto it = lower_bound(vb.begin(), vb.end(), target);
		
		ll stack = 0;
		if (*it == target) answer += mb[target];		
	}
	
	cout << answer << "\n";
	return 0;
}
