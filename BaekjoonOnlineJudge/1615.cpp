#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int tree[2001];
int n, m;
vector<pii> lines;

void update(int idx, int val) {
    while (idx <= n) {
        tree[idx] += val;
        idx += idx & -idx;
    }
}

int query(int idx) {
    int ret = 0;
    while (idx) {
        ret += tree[idx];
        idx -= idx & -idx;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0 ; i < m; ++i) {
        int a, b; cin >> a >> b;
        lines.push_back({a, b});
    }

    sort (lines.begin(), lines.end());

    ll answer = 0;
    for (pii line : lines) {
        answer += query(n) - query(line.second);
        update(line.second, 1);
    }
    cout << answer << "\n";

    return 0;
}