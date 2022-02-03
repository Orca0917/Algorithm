#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> v[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    while (n--) {
        int pos, col; cin >> pos >> col;
        v[col].push_back(pos);
    }

    ll answer = 0;
    for (int i = 0; i <= 100000; ++i) {
        if (v[i].size() <= 1) continue;
        sort(v[i].begin(), v[i].end());

        for (int j = 0; j < v[i].size(); ++j) {
            if (j == 0) answer += v[i][1] - v[i][0];
            else if (j == v[i].size() - 1) answer += v[i].back() - v[i][v[i].size() - 2];
            else {
                answer += min(v[i][j] - v[i][j - 1], v[i][j + 1] - v[i][j]);
            }
        }
    }

    cout << answer << "\n";
    return 0;
}