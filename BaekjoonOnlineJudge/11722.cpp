#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
int memo[1001][1001];
vector<int> v;

int dp(int index, int value) {
    if (index == -1) return 0;

    int &ret = memo[index][value];
    if (ret != -1) return ret;

    ret = max(1, dp(index - 1, value));
    for (int i = 0; i < index; ++i)
        if (v[i] > value) 
            ret = max(ret, dp(i, v[i]) + 1);

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    v.resize(n);
    for (int &e : v) cin >> e;
    
    memset(memo, -1, sizeof(memo));
    cout << dp(n, 0) - 1 << "\n";

    return 0;
}