#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int v, e;
vector<int> adj[20001];
int id[20001];

bool is_bipartite(int now) {
    queue<pii> q;
    q.push({now, 0});
    id[now] = 0;

    while (!q.empty()) {
        int here = q.front().first;
        int mask = q.front().second;
        q.pop();

        for (int there : adj[here]) {
            if (id[there] == mask) return false;

            if (id[there] == -1) {
                id[there] = mask ^ 1;
                q.push({there, mask ^ 1});
            }
        }
    }

    return true;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        for (int i = 0; i < 20001; ++i) adj[i].clear();
        memset(id, -1, sizeof(id));

        cin >> v >> e;
        while (e--) {
            int u1, u2; cin >> u1 >> u2;
            adj[u1].push_back(u2);
            adj[u2].push_back(u1);
        }


        bool flag = true;
        for (int i = 1; i <= v && flag; ++i) {
            if (id[i] == -1) {
                bool ret = is_bipartite(i);
                if (!ret) flag = false;
            }
        }
        cout << (flag ? "YES" : "NO") << "\n";

    }
    
    return 0;
}