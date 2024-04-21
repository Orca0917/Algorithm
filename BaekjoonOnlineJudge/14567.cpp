#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
int indeg[1001];
vector<int> adj[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        indeg[b] += 1;
        adj[a].push_back(b);
    }

    queue<pii> q;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0)
            q.push({i, 1});
    }

    vector<int> answer(1001);
    while (!q.empty()) {
        pii x = q.front(); q.pop();
        answer[x.first] = x.second;
        
        for (int xx : adj[x.first]) {
            if (indeg[xx] == 0) continue;
            indeg[xx] -= 1;
            if (indeg[xx] == 0) {
                q.push({xx, x.second + 1});
            }
        }
    }

    for (int i = 1; i <= n; ++i) cout << answer[i] << " ";
    
    return 0;
}