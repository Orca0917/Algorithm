#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> v[4];
vector<ll> sum[2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            int k; cin >> k;
            v[j].push_back(k);
        }
    }

    // - sum[0] : A + B
    // - sum[1] : C + D
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                sum[k].push_back(v[k * 2][i] + v[k * 2 + 1][j]);
    
    for (int i = 0; i < 2; ++i) sort(sum[i].begin(), sum[i].end());

    int p1 = n * n - 1, p2 = 0;
    ll answer = 0;

    while (p1 >= 0 && p2 < n * n) {
        ll cnt1 = 0, cnt2 = 0;
        if (-sum[0][p1] == sum[1][p2]) {
            ll target = sum[1][p2];
            while (p1 >= 0 && -sum[0][p1] == target) --p1, ++cnt1;
            while (p2 < n * n && sum[1][p2] == target) ++p2, ++cnt2;
            answer += cnt1 * cnt2;
        }
        else if (-sum[0][p1] < sum[1][p2]) --p1;
        else ++p2;
    }

    cout << answer << "\n";
    
    return 0;
}