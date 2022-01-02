#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[2001];
bool visited[2001];


int dfs(int here) {
    visited[here] = true;

    int ret = 1;
    for (int there : adj[here])
        if (!visited[there]) {
            ret = max(ret, dfs(there) + 1);
            if (ret >= 5) break;
        }
    visited[here] = false;
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, M; cin >> N >> M;

    memset(adj, 0, sizeof(adj));

    while (M--) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bool answer = false;
    for (int i = 0; i < N; ++i) {
        memset(visited, false, sizeof(visited));
        int result = dfs(i);
        if (result >= 5) {
            answer = true;
            break;
        }
    }
    cout << answer << "\n";

    return 0;
}