#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N, M;
vector<pii> adj[50001];
int cost[50001];

int dijkstra(int start, int end) {
    for (int i = 1; i <= N; ++i) cost[i] = 1e9;
    
    priority_queue<pii> pq;
    pq.push({0, start});
    cost[start] = 0;

    while (!pq.empty()) {
        int here = pq.top().second;
        int here_cost = -pq.top().first;
        pq.pop();

        if (here == end) return here_cost;

        for (pii there_info : adj[here]) {
            int there = there_info.first;

            if (cost[there] > cost[here] + there_info.second) {
                cost[there] = cost[here] + there_info.second;
                pq.push({-(cost[there]), there});
            }
        }
    }

    return 1e9;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    for (int i = 1; i <= N; ++i) {
        sort(adj[i].begin(), adj[i].end(), [](const pii &a, const pii &b) -> bool {
            return a.second < b.second;
        });
    }

    cout << dijkstra(1, N) << "\n";
    
    return 0;
}