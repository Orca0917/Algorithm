#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int testcase; cin >> testcase;
	while (testcase--) {
		int n; cin >> n;
		vector<int> a(n), b(n), pos(2 * n + 1);
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			pos[a[i]] = i;
		}
		for (int i = 0; i < n; ++i) {
			cin >> b[i];
			pos[b[i]] = i;
		}
		int answer = 2 * n - 2;
		int mIdx = n;

		for (int i = 2 * n - 1; i > 0; i -= 2) {
			mIdx = min(mIdx, pos[i + 1]);
			answer = min(answer, pos[i] + mIdx);
		}
		cout << answer << "\n";
	}
	return 0;
}