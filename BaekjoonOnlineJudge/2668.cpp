#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int adj[101];
bool vis[101];
vector<int> answer;

bool dfs(int here, int root) {
    if (vis[here] == false) {
        vis[here] = true;
        return dfs(adj[here], root);
    } else {
        if (here == root) return true;
        else return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> adj[i];
    }

    for (int i = 1; i <= n; ++i) {
        memset(vis, false, sizeof(vis));
        if(dfs(i, i)) answer.push_back(i);
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << "\n";
    for (int e : answer) cout << e << "\n";

    
    return 0;
}