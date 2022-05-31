#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<int> arr(M);
	for (int i = 0; i < M; i++) cin >> arr[i];

	sort(arr.begin(), arr.end());

	int ans = 0, idx = 0, k = min(N, M);
	for (int i = 1; i <= k; i++) {
		if (ans <= i * arr[M - i]) ans = i * arr[M - i], idx = i;
	}

	cout << arr[M - idx] << '\n' << ans;

    return 0;
}