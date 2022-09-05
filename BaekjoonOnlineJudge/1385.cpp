#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[1'000'001];
vector<bool> vis(1'000'001, false);
vector<int> trace(1'000'001);

void link(int v1, int v2) {
    if (v1 > 1'000'000 || v2 > 1'000'000) return;

    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
}

void setup() {
    for (int room = 2; room <= 7; ++room) link(1, room); link(2, 7);

    int cnt = 0, depth = 1;

    for (int room = 2; room <= 1'000'000; ++room) {

        // 새로운 깊이의 시작
        if (cnt == depth * 6) {
            ++depth;
            cnt = 0;
        }
        
        // 현재 깊이의 벌집에 몇 번째 방?
        int pos = cnt / depth;
        link(room, room + 1);

        if (cnt % depth == depth - 1) {
            if (pos <= 4) {
                link(room, room + 6 * depth + 0 + pos);
                link(room, room + 6 * depth + 1 + pos);
                link(room, room + 6 * depth + 2 + pos);
            } else {
                link(room, room + 6 * depth + 5);
                link(room, room + 6 * depth + 6);
            } 
        }
        
        else {
            link(room, room + 6 * depth + pos);
            link(room, room + 6 * depth + pos + 1);
            if (pos == 0 && cnt == 0) link(room, room + 5 + 6 * (depth - 1));
        }

        ++cnt;
    }
}

void bfs(int dep, int des) {
    queue<pii> q;
    q.push({dep, 1});
    vis[dep] = true;
    trace[dep] = dep;

    while (!q.empty()) {
        int here = q.front().first;
        int time = q.front().second;
        q.pop();

        if (here == des) break;

        for (int there : adj[here]) {
            if (vis[there]) continue;
            vis[there] = true;
            q.push({there, time + 1});
            trace[there] = here;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    setup();

    int u1, u2; cin >> u1 >> u2;
    bfs(u1, u2);

    vector<int> path;
    path.push_back(u2);

    while (u2 != u1) {
        u2 = trace[u2];
        path.push_back(u2);
    }

    for (int i = path.size() - 1; i >= 0; --i) cout << path[i] << " \n"[i == 0];
    
    return 0;
}