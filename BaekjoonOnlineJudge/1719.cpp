#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n; // 집하장의 수
int m; // 경로의 수

int dist[200], previous[200];
vector<pii> adj[200];
int answer[200][200];

struct _dtype {
    int here;   // current node (집하장)
    int acc;    // accumulated cost

    _dtype(int here, int acc): here(here), acc(acc){}

    bool operator < (const _dtype a) const {
        return acc > a.acc;
    }
};

void initialize() {
    // initialize
    for (int i = 0; i < n; ++i) dist[i] = 1e9;
    for (int i = 0; i < n; ++i) previous[i] = -1;
}

int track(int src, int x) {
    if (src == x) return -1;

    if (previous[x] == src) return x;
    else return track(src, previous[x]);
}

void dijkstra(int src) {
    initialize();

    priority_queue<_dtype> pq;
    pq.push({src, 0});
    dist[src] = 0;

    while (!pq.empty()) {
        int here = pq.top().here;
        int accu = pq.top().acc;
        pq.pop();

        if (dist[here] > accu) continue;

        for (auto nxt : adj[here]) {
            int there = nxt.first;
            int cost  = nxt.second;

            if (dist[there] > dist[here] + cost) {
                dist[there] = dist[here] + cost;
                previous[there] = here;
                pq.push({there, dist[there]});
            }
        }
    }
    
    // backtrack!
    for (int i = 0; i < n; ++i) {
        answer[src][i] = track(src, i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        adj[u - 1].push_back({v - 1, c});
        adj[v - 1].push_back({u - 1, c});
    }

    for (int i = 0; i < n; ++i) dijkstra(i);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) cout << "-";
            else cout << answer[i][j] + 1;
            cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}