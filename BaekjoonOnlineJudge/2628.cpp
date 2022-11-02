#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int m, n; cin >> n >> m;
	vector<int> mv = { 0,m };
	vector<int> nv = { 0,n };

	int N; cin >> N;
	while (N--) {
		bool x; int y; cin >> x >> y;
		if (x) nv.push_back(y);
		else mv.push_back(y);
	}

	sort(mv.begin(), mv.end());
	sort(nv.begin(), nv.end());

	m = (int) mv.size();
	n = (int) nv.size();
	
	int maxgaro = 0;
	int maxsero = 0;
	for (int i = 1; i < m; i++) {
		int temp = mv[i] - mv[i - 1];
		if (temp > maxgaro) maxgaro = temp;
	}
	for (int i = 1; i < n; i++) {
		int temp = nv[i] - nv[i - 1];
		if (temp > maxsero) maxsero = temp;
	}

	cout << maxgaro * maxsero;
    
    return 0;
}