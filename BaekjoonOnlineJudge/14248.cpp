#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;


int n;
vector<int> x;
vector<int> vis(100001, 0);

int bfs(int start) {

    queue<int> q;
    q.push(start);
    vis[start] = 1;

    while (!q.empty()) {
        int now = q.front(); q.pop();

        for (int i = 0; i < 2; ++i) {
            int after = now + x[now] * pow(-1, i);
            if (after < 0 || after >= n || vis[after]) continue;
            vis[after] = 1;
            q.push(after);
        }
    }

    return accumulate(vis.begin(), vis.end(), 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    x.resize(n);
    for (int &e : x) cin >> e;

    int k; cin >> k;
    cout << bfs(--k);
    
    return 0;
}