#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<pii> v;
int white_stat, black_stat;
int memo[1001][16][16];

int dp(int index, int white, int black) {
    if (white == 15 && black == 15) return 0;
    if (index == v.size()) return 0;

    int &ret = memo[index][white][black];
    if (ret != -1) return ret;

    ret = dp(index + 1, white, black);
    if (white < 15) ret = max(ret, dp(index + 1, white + 1, black) + v[index].first);
    if (black < 15) ret = max(ret, dp(index + 1, white, black + 1) + v[index].second);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (cin >> white_stat >> black_stat) v.push_back({white_stat, black_stat});

    sort(v.begin(), v.end());

    memset(memo, -1, sizeof(memo));
    cout << dp(0, 0, 0) << "\n";
    
    return 0;
}