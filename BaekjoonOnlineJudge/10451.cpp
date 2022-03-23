#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj(1001);
vector<bool> vis(1001, false);

// return permutation cycle number
int dfs(int node) {
    if (vis[node]) return 0;
    vis[node] = true;
    return dfs(adj[node]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        
        for (int i = 1; i <= n;++i) cin >> adj[i];
        fill(vis.begin(), vis.end(), false);

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            if (vis[i] == false) ++answer;
            dfs(i);
        }

        cout << answer << "\n";
    }
    
    return 0;
}